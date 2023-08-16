#include <coinlist.h>
#include <wallet/receive.h>
#include <wallet/coincontrol.h>
#include <wallet/spend.h>

CoinList::CoinList() : height(-1) {}

void CoinList::clear() {
    minerList.clear();
    utxoMap.clear();
    height = -1;
}

void CoinList::Update(ChainstateManager& chainman)
{
    if (!fLogEvents) {
        throw std::runtime_error("Events log is required for miner list");
    }
    int cur = chainman.ActiveHeight();

    LogPrintf("Update(): from = %d, to = %d\n", height + 1, cur);

    // Update the wallet delegations
    std::vector<UTXOUpdateEvent> events;
    fvmMinerList.FilterUTXOUpdateEvents(events, chainman, height + 1, cur);
    fvmMinerList.UpdateUTXOListFromEvents(events, minerList);
    fvmMinerList.UpdateUTXOMapFromBlocks(utxoMap, chainman, height + 1, cur);

    height = cur;

    LogPrintf("Update(): minerList=%d\n", minerList.size());
    LogPrintf("Update(): utxoMap=%d\n", utxoMap.size());
}

bool CoinList::GetRoot(const COutPoint& child, const uint160 &address, COutPoint &root) {
    auto mapItr = utxoMap.find(child);

    // if not found in map then it should be root it safe
    COutPoint tmpRoot = mapItr == utxoMap.end() ? child : mapItr->second;

    auto minerItr = minerList.find(tmpRoot);
    if (minerItr == minerList.end()) {
        return false;
    }

    if (minerItr->second != address) {
        return false;
    }

    root = tmpRoot;
    return true;
}

bool CoinList::GetRoot(const COutPoint& child, COutPoint &root) {
    auto mapItr = utxoMap.find(child);

    // if not found in map then it should be root it safe
    COutPoint tmpRoot = mapItr == utxoMap.end() ? child : mapItr->second;
    auto minerItr = minerList.find(tmpRoot);
    if (minerItr == minerList.end()) {
        return false;
    }

    root = tmpRoot;
    return true;
}
