#pragma once
#include <vector>
#include <crtDefs.hpp>
#include <crtComponent.hpp>
#include <stdexcept>
#include <string>

namespace crt
{
    struct Wire
    {
        double potential;
        std::vector<Pin_ref> pins;

        Wire() = default;
        // Wire(bool is_ground) : potential(), pins() {}
        Wire(double potential) : potential(potential), pins() {}

        double compute_error() const;

        virtual ~Wire() = default;
        virtual bool is_fixed() const;
        virtual void set_potential(double v);
        std::string name(int i) const;
        void symbol(std::ostream &os, int i) const;

        virtual double get_potential() const;
    };

    inline void operator==(Wire_ref w, Pin_ref p)
    {
        w->pins.push_back(p);
        p->wire = w;
    }

    struct Const_Wire : public Wire
    {
        Const_Wire() = delete;
        Const_Wire(double potential) : Wire(potential) {};

        bool is_fixed() const override;
        void set_potential(double v) override;
        double get_potential() const override;
    };

    /*struct TGenerator : public Wire
    {
        TGenerator() = delete;
        TGenerator(double E) : Wire(E) {};

        bool is_fixed() const override;
        void set_potential(double v) override;
        bool is_generator() const override;

    };*/
}