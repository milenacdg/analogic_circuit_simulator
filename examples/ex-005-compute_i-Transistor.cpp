#include <iostream>
#include <crt.hpp>
#include <fstream>
#include <unistd.h>

int main(int argc, char **argv)
{
    crt::Circuit circuit;
    auto t1{circuit += crt::make::transistor()};

    auto w1 = circuit.wire(10);
    auto w2 = circuit.wire(0);
    auto w3 = circuit.wire(5);

    w1 == t1->pin<0>();
    w2 == t1->pin<1>();
    w3 == t1->pin<2>();

    t1->compute_i();

    {
        std::ofstream file("circuit_ex5_transistor_computed.dot");
        file << circuit;
        crt::utilities::show("circuit_ex5_transistor_computed.dot");
    }
    return 0;
}