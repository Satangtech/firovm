#ifndef FVMSUPPLYCONTROL_H
#define FVMSUPPLYCONTROL_H

#include <validation.h>
#include <util/contractabi.h>

extern const std::string supplyControlABI;
extern const std::string supplyControlCode;

struct Mint {
    std::string scriptType;
    CScript script;
    CAmount amount;

    Mint(std::string _scriptType, CScript _script, CAmount _amount): 
        scriptType(_scriptType), script(_script), amount(_amount)
    {}
};

class FVMSupplyControl {
private:
    dev::Address supplyControlAddress;

public:
    FVMSupplyControl();

    bool GetMint(int block, std::vector<Mint> &out, CChainState &chain);
};

#endif // FVMSUPPLYCONTROL_H