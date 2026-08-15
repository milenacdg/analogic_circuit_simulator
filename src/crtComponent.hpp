#pragma once
#include <array>
#include <cstddef>
#include <crtDefs.hpp>
#include <string>

namespace crt
{
    struct Component // 2 sort
    {
        virtual void compute_i() const = 0;
        virtual std::string name(int i) const = 0;
        virtual void symbol(std::ostream &os, int i) const = 0;
        virtual ~Component() = default;
        virtual double d(Wire_ref, Pin_ref) const = 0;
    };

    template <std::size_t NB_PINS> // typename COMP
    struct Comp : public Component
    {
        std::array<Pin_ref, NB_PINS> pins;

        Comp()
        {
            for (auto &p : pins)
            {
                p = std::make_shared<Pin>();
            }
        };

        void connect_pins(Component_ref comp)
        {
            for (auto &p : pins)
                p->component = comp;
        }

        virtual void compute_i() const = 0;
        // fonction check to find unused pin
        virtual std::string name(int i) const = 0;
        virtual void symbol(std::ostream &os, int i) const = 0;
        virtual ~Comp() {};

        template <std::size_t ID>
        Pin_ref pin()
        {
            static_assert(ID < NB_PINS, "Wrong number of pin");
            return pins[ID];
        }
    };
}