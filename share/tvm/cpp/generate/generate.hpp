#pragma once

#define TVM
#define BOOST_NO_CXX17_HDR_STRING_VIEW
#define BOOST_NO_IOSTREAM

#include <tvm/schema/message.hpp>
#include <tvm/smart_switcher.hpp>
#include <tvm/contract_handle.hpp>

namespace tvm {
    inline namespace schema {

        struct Witness {
            bytes primary_input;
            bytes auxiliary_input;
        };

        __interface ICircuitUtil {

            [[external, dyn_chain_parse]] void constructor() = 1;

            [[getter]] Witness generateWitness(uint32 a, uint32 b) = 2;
        };

        struct DCircuitUtil { };

        __interface ECircuitUtil {};

    }    // namespace schema
}    // namespace tvm
