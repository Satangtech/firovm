#ifndef FVMSUPPLYCONTROL_H
#define FVMSUPPLYCONTROL_H

#include <validation.h>
#include <util/contractabi.h>

extern const std::string strSupplyControlABI;

struct Mint {
    std::string scriptType;
    CScript script;
    CAmount amount;

    Mint(std::string _scriptType, CScript _script, CAmount _amount): 
        scriptType(_scriptType), script(_script), amount(_amount)
    {}
};

class FVMSupplyControl {

public:
    FVMSupplyControl();

    bool getMint(int block, std::vector<Mint> &out, CChainState &chain);
};

#endif // FVMSUPPLYCONTROL_H