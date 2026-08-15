#include <iostream>
#include <crt.hpp>
#include <fstream>
#include <unistd.h>

int main(int argc, char **argv)
{
    crt::GradCircuit circuit;
    auto r1{circuit += crt::make::resistor(10)};
    auto r2{circuit += crt::make::resistor(5)};
    auto d{circuit += crt::make::diode()};
    auto [w1, w2] = circuit.make_generator(10);

    w1 == r1->pin<0>();
    w2 == r2->pin<1>();

    auto w3 = circuit.wire();
    w3 == d->pin<0>();
    w3 == r1->pin<1>();

    auto w4 = circuit.wire();
    w4 == d->pin<1>();
    w4 == r2->pin<0>();

    w3->set_potential(3.5);
    w4->set_potential(3.0);

    std::cout << "Résolution avec la descente du gradient\n"
              << std::endl;
    solve<Grad_Desc>(circuit);
    {
        std::cout << "solve : " << circuit << std::endl;
        std::ofstream file_bfsolve("circuit_ex8_grad-solved.dot");
        file_bfsolve << circuit;
        crt::utilities::show("circuit_ex8_grad-solved.dot");
    }

    std::cout << "Résolution avec la résolution naïve\n"
              << std::endl;

    crt::Circuit circuit2;
    auto r3{circuit2 += crt::make::resistor(10)};
    auto r4{circuit2 += crt::make::resistor(5)};
    auto d2{circuit2 += crt::make::diode()};
    auto [w5, w6] = circuit2.make_generator(10);

    w5 == r3->pin<0>();
    w6 == r4->pin<1>();

    auto w7 = circuit2.wire();
    w7 == d2->pin<0>();
    w7 == r3->pin<1>();

    auto w8 = circuit2.wire();
    w8 == d2->pin<1>();
    w8 == r4->pin<0>();

    w7->set_potential(3.5);
    w8->set_potential(3.0);

    solve<NaiveSolve>(circuit2);
    {
        std::cout << "solve : " << circuit2 << std::endl;
        std::ofstream file_bfsolve("circuit_ex8_naive-solved.dot");
        file_bfsolve << circuit2;
        crt::utilities::show("circuit_ex8_naive-solved.dot");
    }

    return 0;
}