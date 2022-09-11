#include <nil/crypto3/algebra/curves/bls12.hpp>
#include <nil/crypto3/algebra/fields/bls12/base_field.hpp>
#include <nil/crypto3/algebra/fields/bls12/scalar_field.hpp>
#include <nil/crypto3/algebra/fields/arithmetic_params/bls12.hpp>
#include <nil/crypto3/algebra/curves/params/multiexp/bls12.hpp>
#include <nil/crypto3/algebra/curves/params/wnaf/bls12.hpp>
#include <nil/crypto3/algebra/pairing/bls12.hpp>
#include <nil/crypto3/algebra/pairing/mnt4.hpp>
#include <nil/crypto3/algebra/pairing/mnt6.hpp>

#include <nil/crypto3/zk/snark/relations/constraint_satisfaction_problems/r1cs.hpp>

#include <nil/marshalling/status_type.hpp>
#include <nil/crypto3/marshalling/types/zk/r1cs_gg_ppzksnark/primary_input.hpp>

#include <nil/crypto3/zk/components/blueprint.hpp>
#include <nil/crypto3/zk/components/blueprint_variable.hpp>

#include <nil/crypto3/marshalling/types/zk/r1cs_gg_ppzksnark/primary_input.hpp>
#include <nil/crypto3/marshalling/types/zk/r1cs_gg_ppzksnark/auxiliary_input.hpp>
#include <nil/marshalling/endianness.hpp>

using namespace nil::crypto3;
using namespace nil::crypto3::marshalling;

using namespace nil::crypto3::zk;
using namespace nil::crypto3::zk::components;

typedef algebra::curves::bls12<381> curve_type;
typedef typename curve_type::scalar_field_type field_type;

using Endianness = nil::marshalling::option::big_endian;

using primary_input_marshalling_type =
    types::r1cs_gg_ppzksnark_primary_input<nil::marshalling::field_type<Endianness>,
                                           typename snark::r1cs_primary_input<field_type>>;

using auxiliary_input_marshalling_type =
    types::r1cs_gg_ppzksnark_auxiliary_input<nil::marshalling::field_type<Endianness>,
                                             typename snark::r1cs_auxiliary_input<field_type>>;

// Proving x^3=a
__always_inline blueprint<field_type> generate_witness(unsigned a_val, unsigned x_val) {

    blueprint<field_type> bp;
    blueprint_variable<field_type> a;
    a.allocate(bp);
    bp.set_input_sizes(1);
    blueprint_variable<field_type> x;
    x.allocate(bp);
    blueprint_variable<field_type> x_sqr;
    x_sqr.allocate(bp);

    bp.add_r1cs_constraint(snark::r1cs_constraint<field_type>(x, x, x_sqr));
    bp.add_r1cs_constraint(snark::r1cs_constraint<field_type>(x, x_sqr, a));

    bp.val(a) = a_val;
    bp.val(x) = x_val;
    bp.val(x_sqr) = x_val * x_val;

    return bp;
}

__always_inline primary_input_marshalling_type primary_input_writer(const blueprint<field_type> &bp) {
    return types::fill_r1cs_gg_ppzksnark_primary_input<typename snark::r1cs_primary_input<field_type>, Endianness>(
        bp.primary_input());
}

__always_inline auxiliary_input_marshalling_type auxiliary_input_writer(const blueprint<field_type> &bp) {
    return types::fill_r1cs_gg_ppzksnark_auxiliary_input<typename snark::r1cs_auxiliary_input<field_type>, Endianness>(
        bp.auxiliary_input());
}
