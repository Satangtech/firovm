#ifndef FIROVM_NODE_COINLIST_H
#define FIROVM_NODE_COINLIST_H

#include <wallet/wallet.h>
#include <qtum/fvmpoa.h>

class CoinListUpdater
{
private:
    wallet::CWallet *pwallet = 0;
    FVMPoA fvmMinerList;
    std::set<COutPoint> minerList;
    std::set<COutPoint> cacheMinerList;
    int cacheHeight = 0;

public:
    CoinListUpdater(wallet::CWallet *pwallet);

    void Update();

private:
    void CreateUpdateCoinListTransaction(int height, CScript script, const COutPoint &in, const COutPoint &out);
};

#endif // FIROVM_NODE_COINLIST_H