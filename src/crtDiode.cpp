#include <crt.hpp>
#include <cmath>
#include <string>
void crt::Diode::compute_i() const
{
    Pin_ref pin_in = pins[0];
    Pin_ref pin_out = pins[1];
    if (!pin_in || !pin_out || !pin_in->wire || !pin_out->wire)
        return;

    double U = pin_in->wire->potential - pin_out->wire->potential;
   // std::cout << "U_diode=" << U << " exp(U/Vt)=" << std::exp(U/Vt) << std::endl;

    //double U_clamp = std::min(U, 0.5);  // jamais plus de 0.5V dans l'exp
    double Id = Is * (std::exp(U / Vt) - 1);// (exp-1 ≈ exp pour U>>Vt)

   // std::cout << "Id=" << Id << std::endl;
    //if (std::abs(U) >= Vseuil)
    //{
        if(U > 0.0)
        {
            pin_in->intensity = -Id;
            pin_out->intensity = Id;
        }
        else
        {
            pin_in->intensity = Id ;
            pin_out->intensity = - Id;
        }
    //}
    //else 
    //{
       // pin_in->intensity = 0.0; //Id;
       // pin_out->intensity = 0.0; //- Id;
    //}
}

std::string crt::Diode::name(int i) const
{
    return "Diode" + std::to_string(i);
}

void crt::Diode::symbol(std::ostream &os, int i) const
{
    os << "Diode" << i << " " << "[label =\"" << "diode" << i;
    os << "\"" << ", shape=box, color=green, style=bold];" << std::endl;
}

double crt::Diode::d(Wire_ref w, Pin_ref p) const
{
    Pin_ref pin_in = pins[0];
    Pin_ref pin_out = pins[1];

    Wire_ref wire_in = pin_in->wire;
    Wire_ref wire_out = pin_out->wire;

    double V1 = wire_in->potential;
    double V2 = wire_out->potential;

    double U = V1 - V2;
    //double U_clamp = std::min(U, 0.5);
    double di = (Is / Vt) * std::exp(U / Vt);

    if (wire_in == w && pin_in == p) 
    {
        return  - di;
    }
    else if (wire_out == w && pin_in == p)
    {
        return di;
    }
    else if (wire_in == w && pin_out == p)
    {
        return di;
    }
    else if (wire_out == w && pin_out == p)
    {
        return - di;
    }
    else
        return 0.0;
}