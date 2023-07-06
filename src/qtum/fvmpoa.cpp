#include <qtum/fvmpoa.h>
#include <validation.h>
#include <qtum/qtumDGP.h>
#include <vector>
#include <chainparams.h>

const std::string strPoAABI = "[{\"anonymous\":false,\"inputs\":[{\"indexed\":false,\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"}],\"name\":\"AddMinerProposal\",\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":true,\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"},{\"indexed\":false,\"internalType\":\"address\",\"name\":\"voter\",\"type\":\"address\"},{\"indexed\":false,\"internalType\":\"enumPOAGovernance.VoteType\",\"name\":\"voteType\",\"type\":\"uint8\"},{\"indexed\":false,\"internalType\":\"uint256\",\"name\":\"timestamp\",\"type\":\"uint256\"}],\"name\":\"CastMinerVote\",\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":true,\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"},{\"indexed\":false,\"internalType\":\"address\",\"name\":\"rejectedMinerAddress\",\"type\":\"address\"},{\"indexed\":false,\"internalType\":\"uint256\",\"name\":\"timestamp\",\"type\":\"uint256\"}],\"name\":\"MinerVoteFailed\",\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":true,\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"},{\"indexed\":false,\"internalType\":\"address\",\"name\":\"addedMinerAddress\",\"type\":\"address\"},{\"indexed\":false,\"internalType\":\"uint256\",\"name\":\"timestamp\",\"type\":\"uint256\"}],\"name\":\"MinerVoteSucceeded\",\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":true,\"internalType\":\"bytes32\",\"name\":\"role\",\"type\":\"bytes32\"},{\"indexed\":true,\"internalType\":\"bytes32\",\"name\":\"previousAdminRole\",\"type\":\"bytes32\"},{\"indexed\":true,\"internalType\":\"bytes32\",\"name\":\"newAdminRole\",\"type\":\"bytes32\"}],\"name\":\"RoleAdminChanged\",\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":true,\"internalType\":\"bytes32\",\"name\":\"role\",\"type\":\"bytes32\"},{\"indexed\":true,\"internalType\":\"address\",\"name\":\"account\",\"type\":\"address\"},{\"indexed\":true,\"internalType\":\"address\",\"name\":\"sender\",\"type\":\"address\"}],\"name\":\"RoleGranted\",\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":true,\"internalType\":\"bytes32\",\"name\":\"role\",\"type\":\"bytes32\"},{\"indexed\":true,\"internalType\":\"address\",\"name\":\"account\",\"type\":\"address\"},{\"indexed\":true,\"internalType\":\"address\",\"name\":\"sender\",\"type\":\"address\"}],\"name\":\"RoleRevoked\",\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":false,\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"}],\"name\":\"VotingPeriodOver\",\"type\":\"event\"},{\"inputs\":[],\"name\":\"ADMIN_ROLE\",\"outputs\":[{\"internalType\":\"bytes32\",\"name\":\"\",\"type\":\"bytes32\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"name\":\"DEFAULT_ADMIN_ROLE\",\"outputs\":[{\"internalType\":\"bytes32\",\"name\":\"\",\"type\":\"bytes32\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"name\":\"GOV_ROLE\",\"outputs\":[{\"internalType\":\"bytes32\",\"name\":\"\",\"type\":\"bytes32\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"name\":\"MINER_ROLE\",\"outputs\":[{\"internalType\":\"bytes32\",\"name\":\"\",\"type\":\"bytes32\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"newAdmin\",\"type\":\"address\"}],\"name\":\"addAdminAddress\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"newGov\",\"type\":\"address\"}],\"name\":\"addGovAddress\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"minerAddress\",\"type\":\"address\"},{\"components\":[{\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"txId\",\"type\":\"uint256\"}],\"internalType\":\"structPOAGovernance.UTXO\",\"name\":\"utxo\",\"type\":\"tuple\"}],\"name\":\"addMiner\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"}],\"name\":\"cancelVote\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[],\"name\":\"checkHasAdminRole\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"name\":\"checkHasGovRole\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"}],\"name\":\"checkIfMinerProposalIdExist\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"proposalID\",\"type\":\"uint256\"}],\"name\":\"checkOverHalfVoted\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"components\":[{\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"txId\",\"type\":\"uint256\"}],\"internalType\":\"structPOAGovernance.UTXO\",\"name\":\"utxo1\",\"type\":\"tuple\"},{\"components\":[{\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"txId\",\"type\":\"uint256\"}],\"internalType\":\"structPOAGovernance.UTXO\",\"name\":\"utxo2\",\"type\":\"tuple\"}],\"name\":\"checkTwoUTXOEquality\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"pure\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"}],\"name\":\"deleteProposal\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[],\"name\":\"enabled\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"}],\"name\":\"endVotingPeriod\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"}],\"name\":\"executeVote\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"}],\"name\":\"getMinerProposalDetails\",\"outputs\":[{\"internalType\":\"address\",\"name\":\"proposer\",\"type\":\"address\"},{\"internalType\":\"uint256\",\"name\":\"startTime\",\"type\":\"uint256\"},{\"internalType\":\"enumPOAGovernance.Status\",\"name\":\"status\",\"type\":\"uint8\"},{\"internalType\":\"uint256\",\"name\":\"againstVotes\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"forVotes\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"abstainVotes\",\"type\":\"uint256\"},{\"internalType\":\"address\",\"name\":\"minerAddress\",\"type\":\"address\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"bytes32\",\"name\":\"role\",\"type\":\"bytes32\"}],\"name\":\"getRoleAdmin\",\"outputs\":[{\"internalType\":\"bytes32\",\"name\":\"\",\"type\":\"bytes32\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"bytes32\",\"name\":\"role\",\"type\":\"bytes32\"},{\"internalType\":\"address\",\"name\":\"account\",\"type\":\"address\"}],\"name\":\"grantRole\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"bytes32\",\"name\":\"role\",\"type\":\"bytes32\"},{\"internalType\":\"address\",\"name\":\"account\",\"type\":\"address\"}],\"name\":\"hasRole\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"addressToCheck\",\"type\":\"address\"}],\"name\":\"isGovAndAdminAddress\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"addressToCheck\",\"type\":\"address\"}],\"name\":\"isMiner\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"name\":\"minUTXOs\",\"outputs\":[{\"internalType\":\"uint256\",\"name\":\"\",\"type\":\"uint256\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"_minerAddress\",\"type\":\"address\"},{\"components\":[{\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"txId\",\"type\":\"uint256\"}],\"internalType\":\"structPOAGovernance.UTXO[]\",\"name\":\"_newUTXOs\",\"type\":\"tuple[]\"},{\"internalType\":\"bool\",\"name\":\"forVote\",\"type\":\"bool\"}],\"name\":\"proposeMiner\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"adminToBeRemoved\",\"type\":\"address\"}],\"name\":\"removeAdminAddress\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"govToBeRemoved\",\"type\":\"address\"}],\"name\":\"removeGovAddress\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"components\":[{\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"txId\",\"type\":\"uint256\"}],\"internalType\":\"structPOAGovernance.UTXO[]\",\"name\":\"utxos\",\"type\":\"tuple[]\"}],\"name\":\"removeUTXOs\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"bytes32\",\"name\":\"role\",\"type\":\"bytes32\"},{\"internalType\":\"address\",\"name\":\"account\",\"type\":\"address\"}],\"name\":\"renounceRole\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"bytes32\",\"name\":\"role\",\"type\":\"bytes32\"},{\"internalType\":\"address\",\"name\":\"account\",\"type\":\"address\"}],\"name\":\"revokeRole\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"_qtumContractAddress\",\"type\":\"address\"}],\"name\":\"setDGPContract\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"bytes4\",\"name\":\"interfaceId\",\"type\":\"bytes4\"}],\"name\":\"supportsInterface\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"minerAddress\",\"type\":\"address\"},{\"components\":[{\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"txId\",\"type\":\"uint256\"}],\"internalType\":\"structPOAGovernance.UTXO\",\"name\":\"utxoToReplace\",\"type\":\"tuple\"},{\"components\":[{\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"txId\",\"type\":\"uint256\"}],\"internalType\":\"structPOAGovernance.UTXO\",\"name\":\"newUTXO\",\"type\":\"tuple\"}],\"name\":\"update\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"newMinUTXOs\",\"type\":\"uint256\"}],\"name\":\"updateMinUTXOs\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"minerAddress\",\"type\":\"address\"},{\"components\":[{\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"txId\",\"type\":\"uint256\"}],\"internalType\":\"structPOAGovernance.UTXO\",\"name\":\"utxoToReplace\",\"type\":\"tuple\"},{\"components\":[{\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"txId\",\"type\":\"uint256\"}],\"internalType\":\"structPOAGovernance.UTXO\",\"name\":\"newUTXO\",\"type\":\"tuple\"}],\"name\":\"updateWithAddress\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"minerAddress\",\"type\":\"address\"},{\"internalType\":\"uint256\",\"name\":\"txId\",\"type\":\"uint256\"},{\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"}],\"name\":\"usable\",\"outputs\":[{\"internalType\":\"bool\",\"name\":\"\",\"type\":\"bool\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"minerProposalID\",\"type\":\"uint256\"},{\"internalType\":\"uint8\",\"name\":\"voteCasted\",\"type\":\"uint8\"}],\"name\":\"vote\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"}]";
const ContractABI contractPoAABI = strPoAABI;

FVMPoA::FVMPoA() {
    minerLimitAddress = uintToh160(Params().GetConsensus().minerListAddress);
}

bool FVMPoA::Usable(const uint160& address, const COutPoint& utxo, bool& usable, CChainState& chain) const {
    const static std::string method = "usable";
    const auto abi = contractPoAABI[method];
    
    //  setup input and execute
    std::vector<std::vector<std::string>> inputValues = {
        {address.GetReverseHex()},
        {"0x"+utxo.hash.GetReverseHex()},
        {uint256(utxo.n).GetHex()}
    };

    std::vector<ParameterABI::ErrorType> inputErrors;
    std::string inputData;

    if (!abi.abiIn(inputValues, inputData, inputErrors)) {
        return error("Fail to constuct input data");
    }

    std::vector<ResultExecute> execResults;
    {
        LOCK(cs_main);
        execResults = CallContract(minerLimitAddress, ParseHex(inputData), chain);
    }
    
    if (execResults.size() < 1) {
        return error("Failed to CallContract to get poa address status");
    }

    // Deserialize
    std::string outputData = HexStr(execResults[0].execRes.output);
    std::vector<std::vector<std::string>> outputValues;
    std::vector<ParameterABI::ErrorType> outputErrors;
    if (!abi.abiOut(outputData, outputValues, outputErrors)) {
        return error("Failed to deserialize get delegation output parameters");
    }

    if (outputValues.size() != abi.outputs.size()) {
        return error("Failed to deserialize get poa output, size doesn't match");
    }

    try {
        for (std::size_t i = 0; i < outputValues.size(); i++) {
            auto const& value = outputValues[i];
            if (value.size() < 1) {
                return error("Failed to get poa output value");
            }

            auto& name = abi.outputs[i].name;
            if (name == "") {
                if (value[0] == "true") {
                    usable = true;
                } else if (value[0] == "false") {
                    usable = false;
                } else {
                    return error("Failed to parse poa output");
                }
            } else {
                return error("Invalid get usable status");
            }
        }
    } catch(...) {
        return error("Invalid get poa usable output");
    }

    return true;
}

bool FVMPoA::Enabled(CChainState& chain) const {
    const static std::string method = "enabled";
    const auto abi = contractPoAABI[method];
    
    //  setup input and execute
    std::vector<std::vector<std::string>> inputValues;

    std::vector<ParameterABI::ErrorType> inputErrors;
    std::string inputData;

    if (!abi.abiIn(inputValues, inputData, inputErrors)) {
        return error("Fail to constuct input data");
    }

    std::vector<ResultExecute> execResults;
    {
        LOCK(cs_main);
        execResults = CallContract(minerLimitAddress, ParseHex(inputData), chain);
    }
    
    if (execResults.size() < 1) {
        return error("Failed to CallContract to get poa address status");
    }

    // Deserialize
    std::string outputData = HexStr(execResults[0].execRes.output);
    std::vector<std::vector<std::string>> outputValues;
    std::vector<ParameterABI::ErrorType> outputErrors;
    if (!abi.abiOut(outputData, outputValues, outputErrors)) {
        return error("Failed to deserialize get delegation output parameters");
    }

    if (outputValues.size() != abi.outputs.size()) {
        return error("Failed to deserialize get poa output, size doesn't match");
    }

    try {
        for (std::size_t i = 0; i < outputValues.size(); i++) {
            auto const& value = outputValues[i];
            if (value.size() < 1) {
                return error("Failed to get poa output value");
            }

            auto& name = abi.outputs[i].name;
            if (name == "") {
                std::cout << "Enabled value[0] = " << value[0] << std::endl;
            } else {
                return error("Invalid get usable status");
            }
        }
    } catch(...) {
        return error("Invalid get poa usable output");
    }

    return true;
}

bool FVMPoA::Update(const uint160& address, const COutPoint& old, const COutPoint& _new,  CChainState& chain) {
    const static std::string method = "updateWithAddress";
    const auto abi = contractPoAABI[method];
    
    //  setup input and execute
    std::vector<std::vector<std::string>> inputValues;
    {
        std::vector<std::string> paramAddress;
        paramAddress.push_back(address.GetHex());
        inputValues.push_back(paramAddress);
    }
    {
        std::vector<std::string> paramUtxo;
        paramUtxo.push_back(uint256(old.n).GetHex());
        paramUtxo.push_back(old.hash.GetHex());
        inputValues.push_back(paramUtxo);
    }
    {
        std::vector<std::string> paramUtxo;
        paramUtxo.push_back(uint256(_new.n).GetHex());
        paramUtxo.push_back(_new.hash.GetHex());
        inputValues.push_back(paramUtxo);
    }

    std::vector<ParameterABI::ErrorType> inputErrors;
    std::string inputData;

    if (!abi.abiIn(inputValues, inputData, inputErrors)) {
        return error("Fail to constuct input data");
    }

    std::vector<ResultExecute> execResults;
    {
        LOCK(cs_main);
        execResults = ExecContract(MinerListDGP, ParseHex(inputData), chain);
    }
    
    if (execResults.size() < 1) {
        return error("Failed to ExecContract to update utxo");
    }

    // Deserialize
    std::string outputData = HexStr(execResults[0].execRes.output);
    std::vector<std::vector<std::string>> outputValues;
    std::vector<ParameterABI::ErrorType> outputErrors;
    if (!abi.abiOut(outputData, outputValues, outputErrors)) {
        return error("Failed to deserialize get delegation output parameters");
    }

    if (outputValues.size() != abi.outputs.size()) {
        return error("Failed to deserialize get poa output, size doesn't match");
    }

    try {
        for (std::size_t i = 0; i < outputValues.size(); i++) {
            auto const& value = outputValues[i];
            if (value.size() < 1) {
                return error("Failed to get poa output value");
            }

            auto& name = abi.outputs[i].name;
            if (name == "") {
                std::cout << "Enabled value[0] = " << value[0] << std::endl;
            } else {
                return error("Invalid get usable status");
            }
        }
    } catch(...) {
        return error("Invalid get poa usable output");
    }

    return true;
}