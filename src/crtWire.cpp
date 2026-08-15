#include <crtWire.hpp>
#include <string>
#include <crt.hpp>

namespace crt
{
    double Wire::compute_error() const
    {
        double sum_I = 0;
        for (auto p : pins)
        {
            if (p)
                sum_I += p->intensity;
        }
        return sum_I;
    }
    bool Wire::is_fixed() const { return false; }
    void Wire::set_potential(double v) { potential = v; }
    double Wire::get_potential() const { return potential; }

    bool Const_Wire::is_fixed() const { return true; }
    void Const_Wire::set_potential(double v) { throw std::logic_error("can not change the potential of Const_Wire"); }
    double Const_Wire::get_potential() const { return potential; }

    /*bool TGenerator::is_fixed() const { return true; }
    void TGenerator::set_potential(double v) { throw std::logic_error("can not change the potential of Const_Wire"); }
    bool TGenerator::is_generator() const { return true; }*/

    std::string Wire::name(int i) const
    {
        return "Wire" + std::to_string(i);
    }

    void crt::Wire::symbol(std::ostream &os, int i) const
    {
        os << "Wire" << i << " " << "[label =\"" << "Wire with V = " << potential;
        os << "\"" << ", color=black, style=bold];" << std::endl;
    }
}