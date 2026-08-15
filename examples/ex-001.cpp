#include <iostream>
#include <crt.hpp>
#include <fstream>

int main(int argc, char **argv)
{
    crt::Circuit circuit;
    std::cout << "Circuit made" << std::endl;

    auto r1{circuit += crt::make::resistor(2)};
    std::cout << "Resistor 1 made" << std::endl;
    
    auto r2{circuit += crt::make::resistor(2)};
    std::cout << "Resistor 2 made" << std::endl; 

    auto w1 = circuit.wire();
    std::cout << "Wire 1 made" << std::endl;
    
    w1 == r1->pin<1>();
    std::cout << "First connection established" << std::endl;
    w1 == r2->pin<0>();

    std::cout << "The wire is connected" << std::endl;

    std::ofstream file("circuit_ex1.dot");
    file << circuit;
    //std::cout << circuit << std::endl;
    
    return 0;
}