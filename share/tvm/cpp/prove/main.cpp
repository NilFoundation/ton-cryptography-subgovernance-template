#include <iostream>
#include <vector>

#include "circuit.hpp"

int main() {
    auto bp = generate_witness(27, 3);

    std::cout << bp.is_satisfied() << std::endl;

    std::vector<std::uint8_t> pi_bb;
    auto pi_writer = primary_input_writer(bp);
    pi_bb.resize(pi_writer.length(), 0x00);
    auto pi_write_iter = pi_bb.begin();
    pi_writer.write(pi_write_iter, pi_writer.length());

    std::cout << pi_bb.size() << std::endl;

    std::vector<std::uint8_t> ai_bb;
    auto ai_writer = auxiliary_input_writer(bp);
    ai_bb.resize(ai_writer.length(), 0x00);
    auto ai_write_iter = ai_bb.begin();
    ai_writer.write(ai_write_iter, ai_writer.length());

    std::cout << ai_bb.size() << std::endl;

    return 0;
}