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
    auto t{circuit += crt::make::transistor()};
    auto [w1, w2] = circuit.make_generator(10);

    w1 == r1->pin<0>();
    w2 == r2->pin<1>();
    w2 == r3->pin<1>();

    auto w3 = circuit.wire();
    w3 == t->pin<0>();
    w3 == r1->pin<1>();

    auto w4 = circuit.wire();
    w4 == t->pin<2>();
    w4 == r2->pin<0>();

    auto w5 = circuit.wire();
    w5 == t->pin<1>();
    w5 == r3->pin<0>();

    std::cout << "Résolution naïve\n"
              << std::endl;
    solve<NaiveSolve>(circuit);
    {
        std::cout << "solve : " << circuit << std::endl;
        std::ofstream file_bfsolve("circuit_ex9_naif_solved.dot");
        file_bfsolve << circuit;
        crt::utilities::show("circuit_ex9_naif_solved.dot");
    }

    crt::GradCircuit circuit2;
    auto r4{circuit2 += crt::make::resistor(2)};
    auto r5{circuit2 += crt::make::resistor(2)};
    auto r6{circuit2 += crt::make::resistor(2)};
    auto t2{circuit2 += crt::make::transistor()};
    auto [w6, w7] = circuit2.make_generator(10);

    w6 == r4->pin<0>();
    w7 == r5->pin<1>();
    w7 == r6->pin<1>();

    auto w8 = circuit2.wire();
    w8 == t2->pin<0>();
    w8 == r4->pin<1>();

    auto w9 = circuit2.wire();
    w9 == t2->pin<2>();
    w9 == r5->pin<0>();

    auto w10 = circuit2.wire();
    w10 == t2->pin<1>();
    w10 == r6->pin<0>();

    std::cout << "Résolution avec la descente du gradient\n"
              << std::endl;
    solve<Grad_Desc>(circuit2);
    {
        std::cout << "solve : " << circuit2 << std::endl;
        std::ofstream file_bfsolve("circuit_ex9_grad-solved.dot");
        file_bfsolve << circuit2;
        crt::utilities::show("circuit_ex9_grad-solved.dot");
    }

    return 0;
}