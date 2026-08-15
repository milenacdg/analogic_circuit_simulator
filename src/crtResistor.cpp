#include <crt.hpp>
#include <string>

void crt::Resistor::compute_i() const
{

    Pin_ref pin_in = pins[0];
    Pin_ref pin_out = pins[1];
    // elt is a pin_ref so *elt is a pin and pins[0] is a pin_ref
    if (pin_in == nullptr || pin_out == nullptr || !pin_in->wire || !pin_out->wire)
    {
        std::cout << "Invalid connection in component : nullptr pointer" << std::endl; // throw
        return;
    }
    else
    {
        double U = pin_in->wire->potential - pin_out->wire->potential;
        double I = U / R;
        pin_in->intensity = -I;
        pin_out->intensity = I;
    }
}

std::string crt::Resistor::name(int i) const
{
    return "resistor" + std::to_string(i);
}

void crt::Resistor::symbol(std::ostream &os, int i) const
{
    os << "resistor" << i << " " << "[label =\"" << "resistor" << i << "=" << R;
    os << "\"" << ", shape=box, color=red, style=bold];" << std::endl;
}

double crt::Resistor::d(Wire_ref w, Pin_ref p) const
{
    Pin_ref pin_in = pins[0];
    Pin_ref pin_out = pins[1];

    Wire_ref wire_in = pin_in->wire;
    Wire_ref wire_out = pin_out->wire;

    double V1 = wire_in->potential;
    double V2 = wire_out->potential;

    if (wire_in == w && pin_in == p) 
    {// We verify if are on the right wire and that we have the right potential
        return - (1 / R);
    }
    else if (wire_out == w && pin_in == p)
    {
        return  (1 / R);
    }
    else if (wire_in == w && pin_out == p)
    {
        return (1 / R);
    }
    else if (wire_out == w && pin_out == p)
    {
        return - (1 / R);
    }
    else
        return 0;
}