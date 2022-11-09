#ifndef FVMPOA_H
#define FVMPOA_H

#include <validation.h>
#include <util/contractabi.h>

extern const std::string strPoAABI;

class FVMPoA {

public:
    FVMPoA();

    bool IsUsable(const uint160& address, const COutPoint& utxo, bool& usable, CChainState& chain) const;

private:
};


#endif // FVMPOA_H