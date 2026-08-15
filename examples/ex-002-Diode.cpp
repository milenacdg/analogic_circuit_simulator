#include <iostream>
#include <crt.hpp>

int main(int argc, char **argv)
{
    crt::Circuit circuit;
    auto d{circuit += crt::make::diode()};

    std::cout << "diode made" << std::endl;
    return 0;
}