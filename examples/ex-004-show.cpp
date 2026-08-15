#include <iostream>
#include <crt.hpp>
#include <fstream>
#include <unistd.h>

int main(int argc, char **argv)
{
    crt::Circuit circuit;
    auto r1{circuit += crt::make::resistor(2)};
    auto r2{circuit += crt::make::resistor(2)};
    auto r3{circuit += crt::make::resistor(2)};
    auto w1 = circuit.wire(5);
    w1 == r1->pin<1>();
    w1 == r2->pin<1>();
    w1 == r3->pin<0>();

    auto t1{circuit += crt::make::transistor()};
    auto w2 = circuit.wire();
    auto w3 = circuit.wire();
    auto w4 = circuit.wire();
    w2 == r3->pin<1>();
    w2 == t1->pin<0>();
    w3 == t1->pin<1>();
    w4 == t1->pin<2>();

    auto d1{circuit += crt::make::diode()};
    w3 == d1->pin<0>();
    w4 == d1->pin<1>();

    {
        std::ofstream file("circuit_ex4_show.dot");
        file << circuit;
        crt::utilities::show("circuit_ex4_show.dot");
    }

    return 0;
}