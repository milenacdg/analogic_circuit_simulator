#include <iostream>
#include <crt.hpp>
#include <fstream>
#include <unistd.h>

int main(int argc, char **argv)
{
    crt::Circuit circuit;
    auto r1{circuit += crt::make::resistor(1)};
    auto r2{circuit += crt::make::resistor(1)};
    auto [w1, w2] = circuit.make_generator(10);

    w1 == r1->pin<0>();
    w2 == r2->pin<1>();
    auto w3 = circuit.wire();
    w3 == r2->pin<0>();
    w3 == r1->pin<1>();

    solve<NaiveSolve>(circuit, 1e-12);
    {
        std::cout << "solve : " << circuit << std::endl;
        std::ofstream file_bfsolve("circuit_ex6_series_naive-solved.dot");
        file_bfsolve << circuit;
        crt::utilities::show("circuit_ex6_series_naive-solved.dot");
    }

    return 0;
}