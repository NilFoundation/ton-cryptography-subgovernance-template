#define TVM
#define BOOST_NO_CXX17_HDR_STRING_VIEW
#define BOOST_NO_IOSTREAM

#include <tvm/schema/message.hpp>
#include <tvm/smart_switcher.hpp>
#include <tvm/contract_handle.hpp>

namespace tvm {
    inline namespace schema {

        __interface ICircuitUtil {

            [[external, dyn_chain_parse]] void constructor() = 1;

            [[getter]] void prove(bytes keypair, bytes primary_input, bytes auxiliary_input) = 2;
        };

        struct DCircuitUtil { };

        __interface ECircuitUtil {};

    }    // namespace schema
}    // namespace tvm
