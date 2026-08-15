#pragma once
#include <cstddef>
#include <array>
#include <crtComponent.hpp>
#include <string>
#include <cmath>

namespace crt
{

    struct Transistor : public Comp<3>
    {
        double Vt = 0.026;
        double alpha_f = 0.98;
        double Ies = pow(10, -12);

        Transistor() : Comp<3>() {};
        virtual void compute_i() const override;
        virtual std::string name(int i) const override;
        virtual void symbol(std::ostream &os, int i) const override;
        virtual ~Transistor() override {};
        virtual double d(Wire_ref, Pin_ref) const override;
    };

    namespace make
    {
        inline auto transistor()
        {
            auto v = std::make_shared<Transistor>();
            v->connect_pins(v); // to avoid segmentation error
            return v;
        };
    }
}