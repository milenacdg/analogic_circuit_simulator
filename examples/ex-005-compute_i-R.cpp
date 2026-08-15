
#include <iostream>
#include <crt.hpp>
#include <fstream>

// Dans crtComponent.hpp
//  virtual void compute_i();
//  virtual ~Component() {};

// Dans crtResistor.hpp
//  virtual void compute_i() override;
//  virtual ~Resistor() override {};

int main(int argc, char *argv[])
{
    crt::Circuit circuit;
    std::cout << "Circuit made" << std::endl;
    auto r1{circuit += crt::make::resistor(100)};
    std::cout << "First resistance" << std::endl;
    auto r2{circuit += crt::make::resistor(300)};
    std::cout << " Second resistance" << std::endl;

    auto w1 = circuit.wire(3);
    auto w2 = circuit.wire(6);
    std::cout << "first wire set" << std::endl;

    w1 == r1->pin<1>();
    w2 == r1->pin<0>();

    std::cout << "first connections made" << std::endl;

    auto w3 = circuit.wire(8);
    auto w4 = circuit.wire(10);
    std::cout << "second wire set" << std::endl;
    w3 == r2->pin<0>();
    w4 == r2->pin<1>();
    std::cout << "second connections made" << std::endl;

    std::ofstream file("circuit_ex5_R_base.dot");
    file << circuit;
    crt::utilities::show("circuit_ex5_R_base.dot");

    r2->crt::Resistor::compute_i();
    std::cout << "first i computed" << std::endl;
    r1->crt::Resistor::compute_i();
    std::cout << "second i computed" << std::endl;

    std::ofstream file1("circuit_ex5_R_computed.dot");
    file1 << circuit;
    crt::utilities::show("circuit_ex5_R_computed.dot");

    return 0;
}