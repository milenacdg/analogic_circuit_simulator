#include <vector>

#include <crtCircuitGrad.hpp>

std::vector<double> crt::GradCircuit::compute_grad() const
    {   
        // Rassembler tous les fils (libres et fixes)
        std::vector<crt::Wire_ref> all_wires = wires;
        all_wires.insert(all_wires.end(), const_wires.begin(), const_wires.end());

        // On construit le gradient uniquement pour les fils libres
        std::vector<double> grad(all_wires.size(), 0.0);

        // Recalculer les courants pour être certain de leur fraîcheur
        for (auto &c : components)
            c->compute_i();

        for (size_t i = 0; i < all_wires.size(); ++i)
        {
            crt::Wire_ref w_i = all_wires[i];
            double d_total = 0.0;
            double V_i = w_i->get_potential();

            // Contribution de tous les fils (libres ou fixes) à la dérivée de l'erreur
            for (auto &w : all_wires)
            {
                
                double err = w->compute_error();
                
                double d_err = 0.0 ;

                // d(err_w) / d(V_w_i) = somme sur les pins de w de d(I_pin)/d(V_w_i)
                for (auto p : w->pins)
                    d_err += p->component->d(w_i, p);

                //std::cout << "i = " << i << "d_err = " << d_err << std::endl;

                d_total += err * d_err;

                //std::cout << "d_total = " << d_total << std::endl;
                
            }
            grad[i] = 2.0 * d_total;
            //i++;
        //}
        }
        return grad;
    }