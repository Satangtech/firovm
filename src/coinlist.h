#ifndef FIROVM_NODE_COINLIST_H
#define FIROVM_NODE_COINLIST_H

#include <qtum/fvmpoa.h>

class ChainstateManager;

class CoinList
{
private:
    FVMPoA fvmMinerList;

    std::unordered_map<COutPoint, std::pair<COutPoint, uint160>, COutPointHasher> utxoMap;

    int height = 0;

public:
    CoinList();
    
    void clear();

    void Update(ChainstateManager& chainman);

    bool GetRoot(const COutPoint& child, const uint160 &address, COutPoint &root);

    bool GetRoot(const COutPoint& child, COutPoint &root);

    const std::unordered_map<COutPoint, std::pair<COutPoint, uint160>, COutPointHasher>& getUtxoMap() const;
};

#endif // FIROVM_NODE_COINLIST_H
