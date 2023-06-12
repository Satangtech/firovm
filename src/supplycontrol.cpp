#include <supplycontrol.h>

bool AddSupplyControlOutputs(int nHeight, CMutableTransaction &tx, CChainState &state, bool fProofOfStake) {    
    FVMSupplyControl c;
    std::vector<Mint> mints;
    if (!c.getMint(nHeight, mints, state)) {
        return false;
    }

    for (auto const &m: mints) {
        auto &out = tx.vout.emplace_back();
        out.scriptPubKey = m.script;
        out.nValue = m.amount;
    }

    return true;
}

CAmount GetSupplyControlOutputs(int nHeight, std::vector<CTxOut> &outputs, CChainState &state) {
    CAmount val;

    FVMSupplyControl c;
    std::vector<Mint> mints;
    if (!c.getMint(nHeight, mints, state)) {
        return false;
    }

    for (auto const &m: mints) {
        outputs.emplace_back(m.amount, m.script);
        val += m.amount;
    }

    return val;
}