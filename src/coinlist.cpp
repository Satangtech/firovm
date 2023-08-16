#include <coinlist.h>
#include <wallet/receive.h>
#include <wallet/coincontrol.h>
#include <wallet/spend.h>

CoinList::CoinList() : height(-1) {}

void CoinList::clear() {
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

    for (int _height = height + 1; _height <= cur; _height++) {
        fvmMinerList.UpdateUTXOMapFromBlocks(utxoMap, chainman, _height, _height);
        std::vector<UTXOUpdateEvent> events;
        fvmMinerList.FilterUTXOUpdateEvents(events, chainman, _height, _height);
        fvmMinerList.UpdateUTXOListFromEvents(events, utxoMap);
    }

    height = cur;

    LogPrintf("Update(): utxoMap=%d\n", utxoMap.size());
}

bool CoinList::GetRoot(const COutPoint& child, const uint160 &address, COutPoint &root) {
    auto mapItr = utxoMap.find(child);

    auto rootItr = utxoMap.find(child);
    if (rootItr == utxoMap.end()) {
        return false;
    }

    if (rootItr->second.second != address) {
        return false;
    }

    root = rootItr->second.first;
    return true;
}

bool CoinList::GetRoot(const COutPoint& child, COutPoint &root) {
    auto mapItr = utxoMap.find(child);

    // if not found in map then it should be root it safe
    auto rootItr = utxoMap.find(child);
    if (rootItr == utxoMap.end()) {
        return false;
    }

    root = rootItr->second.first;
    return true;
}
