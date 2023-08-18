#ifndef FVMPOA_H
#define FVMPOA_H

#include <util/contractabi.h>
#include <primitives/transaction.h>
#include <eth_client/libdevcore/Address.h>
#include <eth_client/libethcore/LogEntry.h>

class CChainState;
class ChainstateManager;

struct COutPointHasher {
    std::size_t operator()(COutPoint const& s) const noexcept {
        return std::hash<uint64_t>{}(s.hash.GetUint64(0)) 
            ^ std::hash<uint64_t>{}(s.hash.GetUint64(1))
            ^ std::hash<uint64_t>{}(s.hash.GetUint64(2)) 
            ^ std::hash<uint64_t>{}(s.hash.GetUint64(3)) 
            ^ std::hash<uint32_t>{}(s.n);
    }
};

using UTXOMap = std::unordered_map<COutPoint, std::pair<COutPoint, uint160>, COutPointHasher>;

extern const std::string strPoAABI;

enum UTXOUpdateType
{
    UTXOUPDATE_NONE = 0,
    UTXOUPDATE_ADDED = 1,
    UTXOUPDATE_REMOVED = 2,
};

struct UTXOUpdateEvent
{
    UTXOUpdateType type;
    uint160 address;
    int blockHeight;
    COutPoint output;

    UTXOUpdateEvent() : type(UTXOUpdateType::UTXOUPDATE_NONE) {}
};

struct UTXOUsed
{
    CScript scriptPubKey;
    CTxIn input;
    COutPoint output;
};

class FVMPoA {
private:
    dev::Address minerListAddress;

public:
    FVMPoA();

    bool Usable(const uint160& address, const COutPoint& utxo, bool& usable, CChainState& chain) const;

    bool Enabled(CChainState& chain) const;

    bool ExistMinerListContract() const;

    bool GetUTXOUpdateEvent(const dev::eth::LogEntry &log, UTXOUpdateEvent &event) const;

    bool GetUTXOUpdateEvent(const std::vector<std::string> &topics, const std::string &data, UTXOUpdateEvent &event) const;

    bool FilterUTXOUpdateEvents(std::vector<UTXOUpdateEvent> &events, ChainstateManager &chainmain, int fromBlock = 0, int toBlock = -1);

    UTXOMap UTXOListFromEvents(const std::vector<UTXOUpdateEvent> &events);

    void UpdateUTXOListFromEvents(const std::vector<UTXOUpdateEvent> &events, UTXOMap &utxos);

    UTXOMap UTXOMapFromBlocks(ChainstateManager &chainmain, int fromBlock = 0, int toBlock = -1);

    void UpdateUTXOMapFromBlocks(UTXOMap &utxoMap, ChainstateManager &chainmain, int fromBlock = 0, int toBlock = -1);

    static std::string UpdatePayload(const uint160& address, const COutPoint& old, const COutPoint& _new);

private:
};


#endif // FVMPOA_H