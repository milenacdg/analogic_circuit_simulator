#include <iostream>
#include <crt.hpp>

int main(int argc, char **argv)
{
    crt::Circuit circuit;
    auto t{circuit += crt::make::transistor()};

    std::cout << "transistor made " << std::endl;
    return 0;
}