#pragma once
#include <cstddef>
#include <array>
#include <crtComponent.hpp>
#include <string>

namespace crt
{

    struct Resistor : public Comp<2>
    {
        double R;

        Resistor() = delete;
        Resistor(double R) : Comp<2>(), R(R) {};
        virtual void compute_i() const override;
        // virtual void print_symbol(std::ostream& os) const override;
        virtual std::string name(int i) const override;
        virtual void symbol(std::ostream &os, int i) const override;
        virtual ~Resistor() override {};

        virtual double d(Wire_ref, Pin_ref) const override;
    };

    namespace make
    {
        inline auto resistor(double R)
        {
            auto r = std::make_shared<Resistor>(R);
            r->connect_pins(r); // to avoid segmentation error
            return r;
        };
    }
}