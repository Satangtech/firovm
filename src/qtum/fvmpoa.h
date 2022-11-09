#ifndef FVMPOA_H
#define FVMPOA_H

#include <validation.h>
#include <util/contractabi.h>

extern const std::string strPoAABI;

class FVMPoA {

public:
    FVMPoA();

    bool Usable(const uint160& address, const COutPoint& utxo, bool& usable, CChainState& chain) const;

    bool Enabled(CChainState& chain) const;

    bool Update(const uint160& address, const COutPoint& old, const COutPoint& _new, CChainState& chain);

private:
};


#endif // FVMPOA_H