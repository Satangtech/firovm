#ifndef FVMPOA_H
#define FVMPOA_H

#include <validation.h>
#include <util/contractabi.h>

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

class FVMPoA {
private:
    dev::Address minerListAddress;

public:
    FVMPoA();

    bool Usable(const uint160& address, const COutPoint& utxo, bool& usable, CChainState& chain) const;

    bool Enabled(CChainState& chain) const;

    bool Update(const uint160& address, const COutPoint& old, const COutPoint& _new, CChainState& chain);

    bool ExistMinerListContract() const;

    bool GetUTXOUpdateEvent(const dev::eth::LogEntry &log, UTXOUpdateEvent &event) const;

    bool GetUTXOUpdateEvent(const std::vector<std::string> &topics, const std::string &data, UTXOUpdateEvent &event) const;

    bool FilterUTXOUpdateEvents(std::vector<UTXOUpdateEvent> &events, ChainstateManager &chainmain, int fromBlock = 0, int toBlock = -1);

    std::set<COutPoint> UTXOListFromEvents(const std::vector<UTXOUpdateEvent> &events);

    void UpdateUTXOListFromEvents(const std::vector<UTXOUpdateEvent> &events, std::set<COutPoint> &utxos);

private:
};


#endif // FVMPOA_H