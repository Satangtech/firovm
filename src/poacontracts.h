#ifndef __POA_CONTRACTS_H
#define __POA_CONTRACTS_H

#include <uint256.h>
#include <vector>
#include <map>
#include <string>
#include <utility>

#include <eth_client/libethereum/Account.h>
#include <eth_client/libethereum/State.h>

class POAContractState {
private:
    const dev::eth::State &ethState;

    // offsets in QtumGov
    static constexpr uint32_t adminAddressesOffset = 1;
    static constexpr uint32_t governanceAddressesOffset = 2;

    // offsets in POAGovernance
    static constexpr uint32_t minersMapOffset = 2;
    static constexpr uint32_t minerArrayOffset = 5;

public:
    static constexpr uint32_t maxNumberOfAddressesInList = 1<<16;
    static constexpr uint32_t maxTxidLength = 1024;

    POAContractState(const dev::eth::State &_ethState) : ethState(_ethState) {}

    // Get list of addresses
    std::vector<dev::Address> GetAdminAddresses();
    std::vector<dev::Address> GetGovernanceAddresses();
    std::vector<dev::Address> GetMinerAddresses();

    // Get the pair (index and txid) associated with a miner's address. Returns false if not found
    bool GetMinerInformation(const dev::Address &minerAddress, dev::u256 &index, std::string &txid);

private:
    std::vector<dev::Address> GetArrayAtLocation(const dev::Address &address, int offset);
};

#endif
