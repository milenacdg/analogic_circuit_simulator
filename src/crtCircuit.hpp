#pragma once
#include <vector>
#include <crtDefs.hpp>
#include <iostream>
#include <string>
#include <tuple>

namespace crt
{
    struct Circuit // template <typename COMP>
    {
        std::vector<Wire_ref> wires;
        std::vector<Component_ref> components;
        std::vector<Wire_ref> const_wires;

        Circuit() = default;
        Circuit(const Circuit &) = delete;
        Circuit &operator=(const Circuit &) = delete;

        template <typename COMPONENT>
        auto operator+=(COMPONENT c)
        {
            components.push_back(c);
            return c;
        }

        void AddEdge(std::ostream &os, std::string component_name, std::string wire_name, double intensity) const;
        friend std::ostream &operator<<(std::ostream &os, const Circuit &c);

        Wire_ref wire();
        Wire_ref wire(double);
        Wire_ref const_wire(double);

        double compute_total_error() const;

        auto make_generator(double v)
        {
            return std::make_tuple(const_wire(v), const_wire(0.));
        }

        // std::vector<double> compute_grad() const;
    };

}