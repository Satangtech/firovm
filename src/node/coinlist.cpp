#include <node/coinlist.h>
#include <wallet/receive.h>
#include <wallet/coincontrol.h>
#include <wallet/spend.h>

void getDgpData(uint64_t& blockGasLimit, uint64_t& minGasPrice, CAmount& nGasPrice, int& pHeight, ChainstateManager& chainman)
{
    static uint64_t BlockGasLimit = DEFAULT_BLOCK_GAS_LIMIT_DGP;
    static uint64_t MinGasPrice = DEFAULT_MIN_GAS_PRICE_DGP;
    blockGasLimit = BlockGasLimit;
    minGasPrice = MinGasPrice;
    if(globalState.get())
    {
        LOCK(cs_main);
        QtumDGP qtumDGP(globalState.get(), chainman.ActiveChainstate(), fGettingValuesDGP);
        int height = chainman.ActiveChain().Height();
        blockGasLimit = qtumDGP.getBlockGasLimit(height);
        minGasPrice = CAmount(qtumDGP.getMinGasPrice(height));
        if(pHeight) pHeight = height;
        BlockGasLimit = blockGasLimit;
        MinGasPrice = minGasPrice;
    }
    nGasPrice = (minGasPrice>DEFAULT_GAS_PRICE)?minGasPrice:DEFAULT_GAS_PRICE;
}

CoinListUpdater::CoinListUpdater(wallet::CWallet *_pwallet) : pwallet(_pwallet) {}

void CoinListUpdater::Update()
{
    if (!fLogEvents) {
        throw std::runtime_error("Events log is required for miner list");
    }
    int nHeight = pwallet->chain().getHeight().value_or(0);
    
    int checkpointSpan = Params().GetConsensus().CheckpointSpan(nHeight);
    std::vector<UTXOUsed> readdList;
    if(nHeight <= checkpointSpan)
    {
        // Get delegations from events
        std::vector<UTXOUpdateEvent> events;
        fvmMinerList.FilterUTXOUpdateEvents(events, pwallet->chain().chainman());
        minerList = fvmMinerList.UTXOListFromEvents(events);

        // Get used from blocks
        std::vector<UTXOUsed> _usedList;
        fvmMinerList.UpdateUsedListFromBlocks(_usedList, pwallet->chain().chainman());
        newCoinList.clear();
        for (const auto &u: _usedList) {
            newCoinList.emplace(u.output);
        }
    }
    else
    {
        // Update the cached delegations for the staker, older then the sync checkpoint (500 blocks)
        int cpsHeight = nHeight - checkpointSpan;
        if(cacheHeight < cpsHeight)
        {
            std::vector<UTXOUpdateEvent> events;
            fvmMinerList.FilterUTXOUpdateEvents(events, pwallet->chain().chainman(), cacheHeight, cpsHeight);
            fvmMinerList.UpdateUTXOListFromEvents(events, cacheMinerList);

            std::vector<UTXOUsed> _usedList;
            fvmMinerList.UpdateUsedListFromBlocks(_usedList, pwallet->chain().chainman(), cacheHeight, cpsHeight);
            for (const auto &u: _usedList) {
                cacheNewCoinList.emplace(u.output);
            }
            readdList = _usedList;
            cacheHeight = cpsHeight;
        }

        // Update the wallet delegations
        std::vector<UTXOUpdateEvent> events;
        fvmMinerList.FilterUTXOUpdateEvents(events, pwallet->chain().chainman(), cacheHeight + 1);
        minerList = cacheMinerList;
        fvmMinerList.UpdateUTXOListFromEvents(events, minerList);

        std::vector<UTXOUsed> _usedList;
        fvmMinerList.UpdateUsedListFromBlocks(_usedList, pwallet->chain().chainman(), cacheHeight + 1);
        newCoinList = cacheNewCoinList;
        for (const auto &u: _usedList) {
            newCoinList.emplace(u.output);
        }
    }

    // filter in wallet
    for (auto const &u : readdList) {
        LOCK(pwallet->cs_wallet);
        auto isMine = wallet::InputIsMine(*pwallet, u.input);
        bool usable = false;

        // if fail to query or un-usable then skip
        if (!fvmMinerList.Usable(uint160(ExtractPublicKeyHash(u.scriptPubKey)), u.input.prevout, usable, pwallet->chain().chainman().ActiveChainstate())) {
            continue;
        }
        if (!usable) {
            continue;
        }

        if (isMine & (wallet::isminetype::ISMINE_SPENDABLE | wallet::isminetype::ISMINE_USED)) {
            CreateUpdateCoinListTransaction(nHeight, u.scriptPubKey, u.input.prevout, u.output, newCoinList);
        }
    }
}

bool CoinListUpdater::CreateUpdateCoinListTransaction(int height, CScript scriptPubKey, const COutPoint &in, const COutPoint &out, const std::set<COutPoint> &newCoins) {
    auto calldata = FVMPoA::UpdatePayload(uint160(ExtractPublicKeyHash(scriptPubKey)), in, out);
    bool fPsbt = pwallet->IsWalletFlagSet(wallet::WalletFlags::WALLET_FLAG_DISABLE_PRIVATE_KEYS);
    uint64_t nGasLimit = 52579;
    uint64_t blockGasLimit = 0, minGasPrice = 0;
    CAmount nGasPrice = 0;
    int _height = 0;
    auto &chainman = pwallet->chain().chainman();
    getDgpData(blockGasLimit, minGasPrice, nGasPrice, _height, chainman);

    CAmount nGasFee = nGasPrice * nGasLimit;

    wallet::CCoinControl coinControl;
    if(fPsbt) coinControl.fAllowWatchOnly = true;
    coinControl.fAllowOtherInputs = true;
    coinControl.m_add_inputs = true;

    CTxDestination senderAddress = ExtractPublicKeyHash(scriptPubKey);

    CScript script = CScript() << CScriptNum(VersionVM::GetEVMDefault().toRaw())
        << CScriptNum(nGasLimit)
        << CScriptNum(nGasPrice)
        << ParseHex(calldata)
        << ParseHex(Params().GetConsensus().minerListAddress.GetReverseHex())
        << OP_CALL;

    if(height >= Params().GetConsensus().QIP5Height)
    {
        if(IsValidDestination(senderAddress))
        {
            if (!pwallet->HasPrivateKey(senderAddress, coinControl.fAllowWatchOnly)) {
                throw std::runtime_error("Private key not available");
            }
            CKeyID key_id = pwallet->GetKeyForDestination(senderAddress);
            std::vector<unsigned char> scriptSig;
            script = (CScript() << CScriptNum(addresstype::PUBKEYHASH) << ToByteVector(key_id) << ToByteVector(scriptSig) << OP_SENDER) + script;
        }
        else
        {
            // OP_SENDER will always be used when QIP5Height is active
            throw std::runtime_error("Sender address fail to set for OP_SENDER.");
        }
    }

    // Try to create tx from available coins
    std::vector<wallet::COutput> vecOutputs;
    wallet::AvailableCoins(*pwallet, vecOutputs);
    for (const auto &out : vecOutputs) {
        COutPoint outpoint(out.tx->GetHash(), out.i);
        CTxDestination destAddress;
        const CScript& scriptPubKey = out.tx->tx->vout[out.i].scriptPubKey;
        bool fValidAddress = out.fSpendable && ExtractDestination(scriptPubKey, destAddress);

        if (!fValidAddress || minerList.find(outpoint) != minerList.end() || newCoins.find(outpoint) != newCoins.end())
            continue;

        LogPrintf("CreateUpdateCoinListTransaction(): chosen  outpoint=%s, nValue=%d\n", outpoint.ToString(), out.tx->tx->vout[out.i].nValue);
        if (height >= Params().GetConsensus().QIP5Height) {
            coinControl.Select(outpoint);
            coinControl.destChange = destAddress;
        } else {
            if (senderAddress == destAddress) {
                coinControl.Select(outpoint);
                coinControl.destChange = destAddress;
            }
        }
        
        // Create and send the transaction
        CAmount nFeeRequired;
        bilingual_str error;
        std::vector<wallet::CRecipient> vecSend = {{script, 0, false}};
        int nChangePosRet = -1;

        bool sign = !fPsbt;
        CTransactionRef tx;
        FeeCalculation fee_calc_out;
        bool result = CreateTransaction(*pwallet, vecSend, tx, nFeeRequired, nChangePosRet, error, coinControl, fee_calc_out, sign, nGasFee, true, senderAddress);
        if (!result) {
            continue;
        }

        pwallet->CommitTransaction(tx, {}, {});
        LogPrintf("CreateUpdateCoinListTransaction(): txid=%s\n", tx->GetHash().GetHex());

        return true;
    }

    return false;
}