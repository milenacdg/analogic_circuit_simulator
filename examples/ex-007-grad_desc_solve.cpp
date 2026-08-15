#include <iostream>
#include <crt.hpp>
#include <fstream>
#include <unistd.h>

int main(int argc, char **argv)
{
    crt::GradCircuit circuit;
    auto r1{circuit += crt::make::resistor(1)};
    auto r2{circuit += crt::make::resistor(1)};
    auto [w1, w2] = circuit.make_generator(10);

    w1 == r1->pin<0>();
    w2 == r2->pin<1>();
    auto w3 = circuit.wire();
    w3 == r2->pin<0>();
    w3 == r1->pin<1>();

    solve<Grad_Desc>(circuit);
    {
        std::cout << "solve : " << circuit << std::endl;
        std::ofstream file_bfsolve("circuit_ex7_grad-solved.dot");
        file_bfsolve << circuit;
        crt::utilities::show("circuit_ex7_grad-solved.dot");
    }

    return 0;
}