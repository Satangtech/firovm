#include "poacontracts.h"
#include <eth_client/libethereum/ExtVM.h>

using namespace dev;

Address const GOVAddress{"0x0000000000000000000000000000000000000880"};

static h256 keccak1(const h256 &data)
{
    return h256(ethash_keccak256(data.data(), 32).bytes, h256::ConstructFromPointer);
}

static h256 keccak2(const h256 &data1, const h256 &data2)
{
    dev::byte buffer[64];
    memcpy(buffer, data1.data(), 32);
    memcpy(buffer+32, data2.data(), 32);
    h256 result(ethash_keccak256(buffer, 64).bytes, h256::ConstructFromPointer);
    memset(buffer, 0, sizeof(buffer));
    return result;
}

std::vector<Address> POAContractState::GetArrayAtLocation(const Address &address, int offset)
{
    u256 length = ethState.storage(address, u256(offset));

    // Check for sanity
    if (length.is_zero() || length > u256(maxNumberOfAddressesInList))
        return std::vector<Address>();

    size_t arrayLength = length.convert_to<size_t>();

    u256 arrayOffset = keccak1(u256(offset));
    std::vector<Address> result;
    result.reserve(arrayLength);

    for (u256 p=arrayOffset; p!=arrayOffset+arrayLength; ++p)
        result.emplace_back(h256(ethState.storage(address, p)));

    return result;
}

std::vector<Address> POAContractState::GetAdminAddresses()
{
    return GetArrayAtLocation(GOVAddress, adminAddressesOffset);
}

std::vector<Address> POAContractState::GetGovernanceAddresses()
{
    return GetArrayAtLocation(GOVAddress, governanceAddressesOffset);
}

bool POAContractState::GetMinerInformation(const Address &minerAddress, u256 &index, std::string &txid)
{
    u256 itemOffset = keccak2(h256(minerAddress), u256(minersOffset));
    index = ethState.storage(GOVAddress, itemOffset);

    u256 txidLength = ethState.storage(GOVAddress, itemOffset+1);
    if (txidLength & 1) {
        // string is more than 31 characters long, test length for sanity
        if (txidLength >= u256(maxTxidLength*2))
            return false;
        uint32_t length = txidLength.convert_to<uint32_t>()/2;

        txid.clear();
        txid.reserve(length);
        u256 p = keccak1(itemOffset+1);
        while (length > 0) {
            uint32_t l = std::min(length, 32u);
            txid.append((const char *)h256(ethState.storage(GOVAddress, p)).data(), l);
            length -= l;
            p++;
        }
    }
    else {
        // string is stored inside main slot
        uint32_t length = (txidLength & u256(0xFF)).convert_to<uint32_t>()/2;
        if (length > 31)
            return false;
        txid.assign((const char *)h256(txidLength).data(), length);
    }

    return true;
}
