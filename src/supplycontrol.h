#ifndef SUPPLY_CONTROL_H
#define SUPPLY_CONTROL_H

#include <qtum/fvmsupplycontrol.h>

bool AddSupplyControlOutputs(int nHeight, CMutableTransaction &tx, CChainState &state, bool fProofOfStake);

CAmount GetSupplyControlOutputs(int nHeight, std::vector<CTxOut> &outputs, CChainState &state);

#endif // SUPPLY_CONTROL_H