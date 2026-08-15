#include <crt.hpp>
#include <cmath>
#include <string>

void crt::Transistor::compute_i() const
{
    Pin_ref pin_b = pins[0];  // Base current 
    Pin_ref pin_c = pins[1]; //  Collector current
    Pin_ref pin_e = pins[2]; // Emitter current
    // elt is a pin_ref so *elt is a pin and pins[0] is a pin_ref
    if (pin_b == nullptr || pin_c == nullptr || pin_e == nullptr)
    {
        std::cout << "Invalid connection in component : nullptr pointer" << std::endl;
    }
    else
    {
        Wire_ref wire_b = pin_b->wire;
        Wire_ref wire_c = pin_c->wire;
        Wire_ref wire_e = pin_e->wire;

        double Vbe = wire_b->potential - wire_e->potential;
        double expo = std::exp(Vbe / Vt);
        double Ie = Ies * (expo - 1);

        pin_e->intensity = Ie;
        pin_c->intensity =  alpha_f * Ie;
        pin_b->intensity = (1 - alpha_f) * Ie;
        
    }
}
std::string crt::Transistor::name(int i) const
{
    return "transistor" + std::to_string(i);
}

void crt::Transistor::symbol(std::ostream &os, int i) const
{
    os << "transistor" << i << " " << "[label =\"" << "transistor" << i << "\"" << ", shape=box, color=blue, style=bold];" << std::endl;
}


double crt::Transistor::d(Wire_ref w, Pin_ref p) const 
{ 
    Pin_ref pin_b = pins[0];  // Base current 
    Pin_ref pin_c = pins[1]; //  Collector current
    Pin_ref pin_e = pins[2]; // Emitter current

    Wire_ref wire_b = pin_b->wire;
    Wire_ref wire_c = pin_c->wire;
    Wire_ref wire_e = pin_e->wire;

    double Vbe = wire_b->potential - wire_e->potential;

    double expo = std::exp(Vbe / Vt);

    double Ie = Ies * (expo - 1);

    double dIe_Vb = Ies * (1 / Vt) * expo ;

    double dIe_Ve = - Ies * (1 / Vt) * expo ;
    
    
    if (wire_b == w && pin_b == p) return (1 - alpha_f) * dIe_Vb;// dIb/dVb
    else if (wire_b == w && pin_c == p) return alpha_f * dIe_Vb; // dIc/dVb
    else if (wire_b == w && pin_e == p) return dIe_Vb;// dIe/dVb

    else if (wire_c == w && pin_b == p) return 0.0;// dIb/dVc
    else if (wire_c == w && pin_c == p) return 0.0;// dIc/dVc
    else if (wire_c == w && pin_e == p) return 0.0;// dIe/dVc

    else if (wire_e == w && pin_b == p) return (1 - alpha_f) * dIe_Ve;// dIb/dVe
    else if (wire_e == w && pin_c == p) return alpha_f * dIe_Ve;// dIc/dVe
    else if (wire_e == w && pin_e == p) return dIe_Ve;// dIe/dVe

    else return 0.0;
     
}
