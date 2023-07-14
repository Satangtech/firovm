#include <qtum/fvmpoa.h>
#include <validation.h>
#include <qtum/qtumDGP.h>
#include <vector>
#include <chainparams.h>
#include <node/blockstorage.h>

const std::string strPoAABI = "[{\"anonymous\":false,\"inputs\":[{\"indexed\":false,\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"}],\"name\":\"AddMinerProposal\",\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":true,\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"},{\"indexed\":false,\"internalType\":\"address\",\"name\":\"voter\",\"type\":\"address\"},{\"indexed\":false,\"internalType\":\"enumPOAGovernance.VoteType\",\"name\":\"voteType\",\"type\":\"uint8\"},{\"indexed\":false,\"internalType\":\"uint256\",\"name\":\"timestamp\",\"type\":\"uint256\"}],\"name\":\"CastMinerVote\",\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":true,\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"},{\"indexed\":false,\"internalType\":\"address\",\"name\":\"rejectedMinerAddress\",\"type\":\"address\"},{\"indexed\":false,\"internalType\":\"uint256\",\"name\":\"timestamp\",\"type\":\"uint256\"}],\"name\":\"MinerVoteFailed\",\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":true,\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"},{\"indexed\":false,\"internalType\":\"address\",\"name\":\"addedMinerAddress\",\"type\":\"address\"},{\"indexed\":false,\"internalType\":\"uint256\",\"name\":\"timestamp\",\"type\":\"uint256\"}],\"name\":\"MinerVoteSucceeded\",\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":true,\"internalType\":\"bytes32\",\"name\":\"role\",\"type\":\"bytes32\"},{\"indexed\":true,\"internalType\":\"bytes32\",\"name\":\"previousAdminRole\",\"type\":\"bytes32\"},{\"indexed\":true,\"internalType\":\"bytes32\",\"name\":\"newAdminRole\",\"type\":\"bytes32\"}],\"name\":\"RoleAdminChanged\",\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":true,\"internalType\":\"bytes32\",\"name\":\"role\",\"type\":\"bytes32\"},{\"indexed\":true,\"internalType\":\"address\",\"name\":\"account\",\"type\":\"address\"},{\"indexed\":true,\"internalType\":\"address\",\"name\":\"sender\",\"type\":\"address\"}],\"name\":\"RoleGranted\",\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":true,\"internalType\":\"bytes32\",\"name\":\"role\",\"type\":\"bytes32\"},{\"indexed\":true,\"internalType\":\"address\",\"name\":\"account\",\"type\":\"address\"},{\"indexed\":true,\"internalType\":\"address\",\"name\":\"sender\",\"type\":\"address\"}],\"name\":\"RoleRevoked\",\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":true,\"internalType\":\"address\",\"name\":\"minerAddress\",\"type\":\"address\"},{\"indexed\":false,\"internalType\":\"uint256\",\"name\":\"blockHeight\",\"type\":\"uint256\"},{\"indexed\":false,\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"},{\"indexed\":false,\"internalType\":\"uint256\",\"name\":\"txId\",\"type\":\"uint256\"}],\"name\":\"UTXOAdded\",\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":true,\"internalType\":\"address\",\"name\":\"minerAddress\",\"type\":\"address\"},{\"indexed\":false,\"internalType\":\"uint256\",\"name\":\"blockHeight\",\"type\":\"uint256\"},{\"indexed\":false,\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"},{\"indexed\":false,\"internalType\":\"uint256\",\"name\":\"txId\",\"type\":\"uint256\"}],\"name\":\"UTXORemoved\",\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":false,\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"}],\"name\":\"VotingPeriodOver\",\"type\":\"event\"},{\"inputs\":[],\"name\":\"ADMIN_ROLE\",\"outputs\":[{\"internalType\":\"bytes32\",\"name\":\"\",\"type\":\"bytes32\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"name\":\"DEFAULT_ADMIN_ROLE\",\"outputs\":[{\"internalType\":\"bytes32\",\"name\":\"\",\"type\":\"bytes32\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"name\":\"GOV_ROLE\",\"outputs\":[{\"internalType\":\"bytes32\",\"name\":\"\",\"type\":\"bytes32\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"name\":\"MINER_ROLE\",\"outputs\":[{\"internalType\":\"bytes32\",\"name\":\"\",\"type\":\"bytes32\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"newAdmin\",\"type\":\"address\"}],\"name\":\"addAdminAddress\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"newGov\",\"type\":\"address\"}],\"name\":\"addGovAddress\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"}],\"name\":\"cancelVote\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[],\"name\":\"checkHasAdminRole\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"name\":\"checkHasGovRole\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"}],\"name\":\"checkIfMinerProposalIdExist\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"proposalID\",\"type\":\"uint256\"}],\"name\":\"checkOverHalfVoted\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"components\":[{\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"txId\",\"type\":\"uint256\"}],\"internalType\":\"structPOAGovernance.UTXO\",\"name\":\"utxo1\",\"type\":\"tuple\"},{\"components\":[{\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"txId\",\"type\":\"uint256\"}],\"internalType\":\"structPOAGovernance.UTXO\",\"name\":\"utxo2\",\"type\":\"tuple\"}],\"name\":\"checkTwoUTXOEquality\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"pure\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"}],\"name\":\"deleteProposal\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[],\"name\":\"enabled\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"}],\"name\":\"endVotingPeriod\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"}],\"name\":\"executeVote\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"}],\"name\":\"getMinerProposalDetails\",\"outputs\":[{\"internalType\":\"address\",\"name\":\"proposer\",\"type\":\"address\"},{\"internalType\":\"uint256\",\"name\":\"startTime\",\"type\":\"uint256\"},{\"internalType\":\"enumPOAGovernance.Status\",\"name\":\"status\",\"type\":\"uint8\"},{\"internalType\":\"uint256\",\"name\":\"againstVotes\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"forVotes\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"abstainVotes\",\"type\":\"uint256\"},{\"internalType\":\"address\",\"name\":\"minerAddress\",\"type\":\"address\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"bytes32\",\"name\":\"role\",\"type\":\"bytes32\"}],\"name\":\"getRoleAdmin\",\"outputs\":[{\"internalType\":\"bytes32\",\"name\":\"\",\"type\":\"bytes32\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"bytes32\",\"name\":\"role\",\"type\":\"bytes32\"},{\"internalType\":\"address\",\"name\":\"account\",\"type\":\"address\"}],\"name\":\"grantRole\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"bytes32\",\"name\":\"role\",\"type\":\"bytes32\"},{\"internalType\":\"address\",\"name\":\"account\",\"type\":\"address\"}],\"name\":\"hasRole\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"addressToCheck\",\"type\":\"address\"}],\"name\":\"isGovAndAdminAddress\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"addressToCheck\",\"type\":\"address\"}],\"name\":\"isMiner\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"name\":\"minUTXOs\",\"outputs\":[{\"internalType\":\"uint256\",\"name\":\"\",\"type\":\"uint256\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"_minerAddress\",\"type\":\"address\"},{\"components\":[{\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"txId\",\"type\":\"uint256\"}],\"internalType\":\"structPOAGovernance.UTXO[]\",\"name\":\"_newUTXOs\",\"type\":\"tuple[]\"},{\"internalType\":\"bool\",\"name\":\"forVote\",\"type\":\"bool\"}],\"name\":\"proposeMiner\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"adminToBeRemoved\",\"type\":\"address\"}],\"name\":\"removeAdminAddress\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"govToBeRemoved\",\"type\":\"address\"}],\"name\":\"removeGovAddress\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"components\":[{\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"txId\",\"type\":\"uint256\"}],\"internalType\":\"structPOAGovernance.UTXO[]\",\"name\":\"utxos\",\"type\":\"tuple[]\"}],\"name\":\"removeUTXOs\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"bytes32\",\"name\":\"role\",\"type\":\"bytes32\"},{\"internalType\":\"address\",\"name\":\"account\",\"type\":\"address\"}],\"name\":\"renounceRole\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"bytes32\",\"name\":\"role\",\"type\":\"bytes32\"},{\"internalType\":\"address\",\"name\":\"account\",\"type\":\"address\"}],\"name\":\"revokeRole\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"_qtumContractAddress\",\"type\":\"address\"}],\"name\":\"setDGPContract\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"bytes4\",\"name\":\"interfaceId\",\"type\":\"bytes4\"}],\"name\":\"supportsInterface\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"minerAddress\",\"type\":\"address\"},{\"internalType\":\"uint256\",\"name\":\"oldHash\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"oldIdx\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"newHash\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"newIdx\",\"type\":\"uint256\"}],\"name\":\"update\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"newMinUTXOs\",\"type\":\"uint256\"}],\"name\":\"updateMinUTXOs\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"minerAddress\",\"type\":\"address\"},{\"internalType\":\"uint256\",\"name\":\"oldHash\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"oldIdx\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"newHash\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"newIdx\",\"type\":\"uint256\"}],\"name\":\"updateWithAddress\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"minerAddress\",\"type\":\"address\"},{\"internalType\":\"uint256\",\"name\":\"txId\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"}],\"name\":\"usable\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"},{\"internalType\":\"uint8\",\"name\":\"voteCasted\",\"type\":\"uint8\"}],\"name\":\"vote\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"}]";
const ContractABI contractPoAABI = strPoAABI;

bool AbiOutEvent(const FunctionABI &func, const std::vector<std::string>& topics, const std::string& data, std::vector<std::vector<std::string>>& values)
{
    std::vector<ParameterABI::ErrorType> errors;
    values.clear();
    return func.abiOut(topics, data, values, errors);
}

FVMPoA::FVMPoA() {
    minerListAddress = uintToh160(Params().GetConsensus().minerListAddress);
}

bool FVMPoA::Usable(const uint160& address, const COutPoint& utxo, bool& usable, CChainState& chain) const {
    const static std::string method = "usable";
    const auto abi = contractPoAABI[method];
    
    //  setup input and execute
    std::vector<std::vector<std::string>> inputValues = {
        {address.GetReverseHex()},
        {"0x"+utxo.hash.GetHex()},
        {uint256(utxo.n).GetHex()}
    };

    std::vector<ParameterABI::ErrorType> inputErrors;
    std::string inputData;

    if (!abi.abiIn(inputValues, inputData, inputErrors)) {
        return error("Fail to constuct input data");
    }

    std::vector<ResultExecute> execResults;
    {
        LOCK(cs_main);
        execResults = CallContract(minerListAddress, ParseHex(inputData), chain);
    }
    
    if (execResults.size() < 1) {
        return error("Failed to CallContract to get poa address status");
    }

    // Deserialize
    std::string outputData = HexStr(execResults[0].execRes.output);
    std::vector<std::vector<std::string>> outputValues;
    std::vector<ParameterABI::ErrorType> outputErrors;
    if (!abi.abiOut(outputData, outputValues, outputErrors)) {
        return error("Failed to deserialize get delegation output parameters");
    }

    if (outputValues.size() != abi.outputs.size()) {
        return error("Failed to deserialize get poa output, size doesn't match");
    }

    try {
        for (std::size_t i = 0; i < outputValues.size(); i++) {
            auto const& value = outputValues[i];
            if (value.size() < 1) {
                return error("Failed to get poa output value");
            }

            auto& name = abi.outputs[i].name;
            if (name == "") {
                if (value[0] == "true") {
                    usable = true;
                } else if (value[0] == "false") {
                    usable = false;
                } else {
                    return error("Failed to parse poa output");
                }
            } else {
                return error("Invalid get usable status");
            }
        }
    } catch(...) {
        return error("Invalid get poa usable output");
    }

    return true;
}

bool FVMPoA::Enabled(CChainState& chain) const {
    const static std::string method = "enabled";
    const auto abi = contractPoAABI[method];
    
    //  setup input and execute
    std::vector<std::vector<std::string>> inputValues;

    std::vector<ParameterABI::ErrorType> inputErrors;
    std::string inputData;

    if (!abi.abiIn(inputValues, inputData, inputErrors)) {
        return error("Fail to constuct input data");
    }

    std::vector<ResultExecute> execResults;
    {
        LOCK(cs_main);
        execResults = CallContract(minerListAddress, ParseHex(inputData), chain);
    }
    
    if (execResults.size() < 1) {
        return error("Failed to CallContract to get poa address status");
    }

    // Deserialize
    std::string outputData = HexStr(execResults[0].execRes.output);
    std::vector<std::vector<std::string>> outputValues;
    std::vector<ParameterABI::ErrorType> outputErrors;
    if (!abi.abiOut(outputData, outputValues, outputErrors)) {
        return error("Failed to deserialize get delegation output parameters");
    }

    if (outputValues.size() != abi.outputs.size()) {
        return error("Failed to deserialize get poa output, size doesn't match");
    }

    try {
        for (std::size_t i = 0; i < outputValues.size(); i++) {
            auto const& value = outputValues[i];
            if (value.size() < 1) {
                return error("Failed to get poa output value");
            }

            auto& name = abi.outputs[i].name;
            if (name == "") {
                std::cout << "Enabled value[0] = " << value[0] << std::endl;
            } else {
                return error("Invalid get usable status");
            }
        }
    } catch(...) {
        return error("Invalid get poa usable output");
    }

    return true;
}

bool FVMPoA::ExistMinerListContract() const {
    LOCK(cs_main);
    return globalState && globalState->addressInUse(minerListAddress);
}

bool FVMPoA::GetUTXOUpdateEvent(const dev::eth::LogEntry &log, UTXOUpdateEvent &event) const {
    if (log.address != minerListAddress) {
        return false;
    }

    std::vector<std::string> topics;
    for(dev::h256 topic : log.topics)
        topics.push_back(dev::toHex(topic));

    std::string data = dev::toHex(log.data);

    return GetUTXOUpdateEvent(topics, data, event);
}

bool FVMPoA::GetUTXOUpdateEvent(const std::vector<std::string> &topics, const std::string &data, UTXOUpdateEvent &event) const {
    const static std::string addedMethod = "UTXOAdded";
    const auto addedAbi = contractPoAABI[addedMethod];

    const static std::string removedMethod = "UTXORemoved";
    const auto removedAbi = contractPoAABI[removedMethod];

    std::vector<std::vector<std::string>> values;
    FunctionABI func = removedAbi;
    UTXOUpdateType type = UTXOUpdateType::UTXOUPDATE_REMOVED;
    bool ret = AbiOutEvent(func, topics, data, values);
    if (!ret) {
        func = addedAbi;
        type = UTXOUpdateType::UTXOUPDATE_ADDED;
        ret = AbiOutEvent(func, topics, data, values);
    }
    if (!ret) {
        return false;
    }

    try {
        for (size_t i = 0; i < values.size(); i++) {
            auto value = values[i];
            if (value.size() < 1)
                return error("Failed to get utxo update output value");
            
            auto name = func.inputs[i].name;

            if (name == "minerAddress") {
                event.address = uint160(ParseHex(value[0]));
            } else if (name == "blockHeight") {
                event.blockHeight = (int)atoi64(value[0]);
            } else if (name == "index") {
                event.output.n = (uint32_t)atoi64(value[0]);
            } else if (name == "txId") {
                auto const id = u256Touint(dev::u256(value[0])).GetReverseHex();
                event.output.hash = uint256S(id);
            }else {
                return error("Invalid utxo update event input name");
            }
        }
    } catch (...) {
        return error("Parsing failed for utxo update event");
    }
    event.type = type;

    return true;
}

bool FVMPoA::FilterUTXOUpdateEvents(std::vector<UTXOUpdateEvent> &events, ChainstateManager &chainman, int fromBlock, int toBlock) {
    // Check if log events are enabled
    if(!fLogEvents)
        return error("Events indexing disabled");

    // Contract exist check
    if(!ExistMinerListContract())
        return error("miner list contract address does not exist");

    LOCK(cs_main);
    int curheight = 0;
    std::vector<std::vector<uint256>> hashesToBlock;
    curheight = chainman.m_blockman.m_block_tree_db->ReadHeightIndex(fromBlock, toBlock, 0, hashesToBlock, {minerListAddress}, chainman);

    if (curheight == -1) {
        return error("Incorrect params");
    }

    std::set<uint256> dupes;
    for (auto const &hashesTx: hashesToBlock) {
        for (auto const &e: hashesTx) {
            if (dupes.find(e) != dupes.end()) {
                continue;
            }
            dupes.insert(e);

            std::vector<TransactionReceiptInfo> receipts = pstorageresult->getResult(uintToh256(e));
            for(const auto& receipt : receipts) {
                if(receipt.logs.empty()) {
                    continue;
                }

                for(const dev::eth::LogEntry& log : receipt.logs)
                {
                    UTXOUpdateEvent event;
                    if(GetUTXOUpdateEvent(log, event))
                    {
                        events.push_back(event);
                    }
                }
            }
        }
    }

    return true;
}

std::set<COutPoint> FVMPoA::UTXOListFromEvents(const std::vector<UTXOUpdateEvent> &events) {
    std::set<COutPoint> utxos;
    UpdateUTXOListFromEvents(events, utxos);
    return utxos;
}

void FVMPoA::UpdateUTXOListFromEvents(const std::vector<UTXOUpdateEvent> &events, std::set<COutPoint> &utxos) {
    for (auto const &event: events) {
        switch (event.type) {
        case UTXOUpdateType::UTXOUPDATE_ADDED:
        {
            utxos.insert(event.output);
            break;
        }
        case UTXOUpdateType::UTXOUPDATE_REMOVED:
        {
            auto it = utxos.find(event.output);
            if (it != utxos.end()) {
                utxos.erase(it);
            }
            break;
        }
        default:
            break;
        }
    }
}


void FVMPoA::UpdateUsedListFromBlocks(std::vector<UTXOUsed> &used, ChainstateManager &chainman, int fromBlock, int toBlock) {

    LOCK(cs_main);
    const CChain& active_chain = chainman.ActiveChain();
    for (auto height = fromBlock; (toBlock == -1 && height <= active_chain.Height()) || height <= toBlock; height++) {
        auto const pblockindex = active_chain[height];
        CBlock block;
        if (!node::ReadBlockFromDisk(block, pblockindex, Params().GetConsensus())) {
            // Block not found on disk. This could be because we have the block
            // header in our index but not yet have the block or did not accept the
            // block.
            throw std::runtime_error("Block not found on disk");
        }

        if (!block.IsProofOfStake()) {
            continue;
        }

        auto tx = block.vtx[1];
        used.push_back({tx->vout[1].scriptPubKey, tx->vin[0], {tx->GetHash(), 1}});
    }
}

std::string FVMPoA::UpdatePayload(const uint160& address, const COutPoint& old, const COutPoint& _new) {
    const static std::string method = "update";
    const auto abi = contractPoAABI[method];
    
    //  setup input and execute
    std::vector<std::vector<std::string>> inputValues = {
        {address.GetReverseHex()},
        {"0x"+old.hash.GetHex()},
        {uint256(old.n).GetHex()},
        {"0x"+_new.hash.GetHex()},
        {uint256(_new.n).GetHex()},
    };

    std::vector<ParameterABI::ErrorType> inputErrors;
    std::string inputData;

    if (!abi.abiIn(inputValues, inputData, inputErrors)) {
        throw std::runtime_error("fail to serialize abi");
    }

    return inputData;
}