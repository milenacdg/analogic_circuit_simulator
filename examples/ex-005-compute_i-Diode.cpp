#include <iostream>
#include <crt.hpp>
#include <fstream>
int main(int argc, char **argv)
{
    crt::Circuit circuit;
    auto d1{circuit += crt::make::diode()};
    auto [w1, w2] = circuit.make_generator(10);
    w1 == d1->pin<1>();
    w2 == d1->pin<0>();

    // Compute the intensity
    d1->compute_i();

    {
        std::ofstream file("circuit_ex5_diode_computed.dot");
        file << circuit;
        crt::utilities::show("circuit_ex5_diode_computed.dot");
    }
    return 0;
}