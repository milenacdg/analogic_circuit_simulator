#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <tuple>

#include <crt.hpp>

namespace crt
{
    struct GradCircuit : public Circuit // template <typename COMP>
    {
        GradCircuit() = default;
        GradCircuit(const Circuit &) = delete;
        GradCircuit &operator=(const GradCircuit &) = delete;

        std::vector<double> compute_grad() const;
    };

}