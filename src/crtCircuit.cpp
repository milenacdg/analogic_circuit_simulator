#include <crt.hpp>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>

namespace crt
{
    Wire_ref Circuit::wire()
    {
        auto w = std::make_shared<Wire>();
        wires.push_back(w);
        return w;
    }

    Wire_ref Circuit::wire(double potential)
    {
        auto w = std::make_shared<Wire>(potential);
        wires.push_back(w);
        return w;
    }

    Wire_ref Circuit::const_wire(double potential)
    {
        auto w = std::make_shared<Const_Wire>(potential);
        const_wires.push_back(w);
        return w;
    }

    void Circuit::AddEdge(std::ostream &os, std::string component_name, std::string wire_name, double intensity) const
    {
        os << wire_name << " -- " << component_name << " [label= \"" << intensity << "\"];" << std::endl;
    }

    std::ostream &operator<<(std::ostream &os, const Circuit &c)
    {
        os << "graph Circuit {" << std::endl;
        os << "overlap=scale" << std::endl;

        int i = 1;

        std::vector<std::pair<std::string, Wire_ref>> wire_names;
        std::vector<std::pair<std::string, Component_ref>> comp_names;

        /* wires nodes */
        for (auto &wires : {c.wires, c.const_wires})
            for (auto w : wires)
            {
                w->symbol(os, i);
                wire_names.push_back({w->name(i), w});
                i++;
            }

        int j = 1;

        /* component nodes */
        for (auto compo : c.components)
        {
            compo->symbol(os, j);
            comp_names.push_back({compo->name(j), compo});
            j++;
        }

        /* edges */
        for (auto w : wire_names)
        {
            for (auto p : (w.second)->pins)
            {
                for (auto co : comp_names)
                {
                    auto component = co.second;
                    if (p->component == component)
                    {
                        c.AddEdge(os, co.first, w.first, p->intensity);
                    }
                }
            }
        }

        os << "}" << std::endl;

        return os;
    }

    double Circuit::compute_total_error() const
    {
        double E = 0;
        for (auto &c : components)
            c->compute_i();
        for (auto w : wires)
        {
            auto e = w->compute_error();
            E += e * e;
        }
        return E;
    }

}