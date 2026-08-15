#pragma once
#include <cstddef>
#include <array>
#include <crtComponent.hpp>
#include <string>

namespace crt
{

    struct Diode : public Comp<2>
    {
        double Is = 1e-12;            // reverse-bias saturation current
        double Vt = 0.025852; // Thermal voltage for 27°C
        double Vseuil = 0.7; // For diodes in silicium

        Diode() : Comp<2>() {};
        virtual void compute_i() const override;
        virtual std::string name(int i) const override;
        virtual void symbol(std::ostream &os, int i) const override;
        virtual ~Diode() override {};
        virtual double d(Wire_ref, Pin_ref) const override;
    };

    namespace make
    {
        inline auto diode()
        {
            auto d = std::make_shared<Diode>();
            d->connect_pins(d); // to avoid segmentation error
            return d;
        };
    }
}