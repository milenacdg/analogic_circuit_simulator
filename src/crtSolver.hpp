#pragma once
#include <fstream>
#include <iostream>
#include <type_traits>
#include <cmath>
#include <vector>
#include <crtConcept.hpp>
#include <algorithm>

struct Grad_Desc
{
    template <crt::Concept::Grad_Desc Circuit>
    bool solve(Circuit &c, double limit = 1e-14)
    {
        double tolerance = 1e-12;
        int k = 0;
        double step = 1e-2; // step_init;

        double error = c.compute_total_error();
        std::cout << "Initial error: " << error << std::endl;

        // Rassembler tous les fils (libres et fixes)
        std::vector<crt::Wire_ref> all_wires = c.wires;
        all_wires.insert(all_wires.end(), c.const_wires.begin(), c.const_wires.end());

        // Initial vector of potential
        std::vector<double> old_potentials(all_wires.size());
        int i = 0;
        for (auto w : all_wires)
        {
            std::cout << "Wire " << i << " Potential = " << w->get_potential() << std::endl;
            old_potentials[i++] = w->get_potential();
        }

        std::vector<double> potentials(all_wires.size());

        std::vector<double> g = c.compute_grad();
        double gradient_norm = 0.0;
        for (double gi : g)
            gradient_norm += gi * gi;
        gradient_norm = std::sqrt(gradient_norm);
        std::cout << "||grad_init|| = " << gradient_norm << std::endl;

        std::ofstream log_file("solver_log.csv");
        log_file << "k,local_step,gradient_norm,error\n";

        while (gradient_norm > tolerance)
        {
            // double prev_grad = gradient_norm;
            double old_error = error;
            double local_step = step;

            bool accepted = false;

            while (local_step > 1e-15)
            {
                int j = 0;

                // Testing local_step
                for (auto w : all_wires)
                {
                    if (!w->is_fixed())
                    {
                        double V = old_potentials[j] - local_step * g[j];
                        w->set_potential(V);
                    }
                    ++j;
                }
                // Computing the new error
                double new_error = c.compute_total_error();
                // std::cout << "error = " << error << " new_error = " << new_error << std::endl;

                // Testing if it is the right step

                if (new_error < old_error - 1e-15)
                {
                    error = new_error;
                    accepted = true;
                    // std::cout << "condition respectée " <<" k = " << k << std::endl;
                    break;
                }

                // If we arrive there it means that the previous step wasn't good
                // We reset our wires to their previous value
                int i = 0;
                for (auto w : all_wires)
                {
                    if (!w->is_fixed())
                        w->set_potential(old_potentials[i]);

                    ++i;
                }

                // std::cout << "local_step before reducing = " << local_step << std::endl;
                //  We reduce the step
                local_step *= 0.95;

                // std::cout << "local_step after reducing = " << local_step << std::endl;
            }

            // That means that the local_step reached 1e-15 without computing the right step
            // So we cannot find a good enough local_step to satisfy our current tolerance
            if (!accepted)
            {
                log_file << k << "," << local_step << ","
                         << gradient_norm << "," << error << "\n";

                std::cout << " ||grad_final|| = " << gradient_norm << std::endl;
                std::cout << "error = " << error << std::endl;
                std::cout << "Backtracking failed\n";
                break;
            }

            log_file << k << "," << local_step << ","
                     << gradient_norm << "," << error << "\n";

            // If we are here, it means that we found the right local_step so we just set our
            // old_potentials to the current one for the next computing
            // We compute the next old_potentials
            int i = 0;
            for (auto w : all_wires)
                old_potentials[i++] = w->get_potential();

            // We compute the new gradient_norm
            g = c.compute_grad();

            gradient_norm = 0.0;
            for (double gi : g)
                gradient_norm += gi * gi;

            gradient_norm = std::sqrt(gradient_norm);

            std::cout << " k = " << k << " ||grad|| = " << gradient_norm << "      \r" << std::flush;

            if (std::abs(old_error - error) < limit)
            {
                std::cout << "Blocked and can't improve more " << std::endl;
                std::cout << " ||grad_final|| = " << gradient_norm << std::endl;
                std::cout << "error = " << error << std::endl;
                break;
            }

            ++k;
        }

        std::cout << std::endl
                  << "Circuit solved in " << k << " iterations" << std::endl;

        log_file.close();
        return (gradient_norm <= tolerance);
    }
};

struct NaiveSolve
{
    template <crt::Concept::NaiveSolve_Circuit Circuit>
    bool solve(Circuit &c, double limit = 1e-14)
    {
        double epsilon = 1e-6;
        double tolerance = 1e-12;
        int k = 0;
        double error = c.compute_total_error();
        std::cout << "error : " << error << std::endl;
        while (error > tolerance)
        {
            double old_error = error;
            for (auto it = c.wires.begin(); it < c.wires.end(); ++it)
            {
                auto w = *it;
                if (w->is_fixed())
                    continue;
                double oldV = w->get_potential();

                w->set_potential(oldV + epsilon);
                double err_plus = c.compute_total_error();

                w->set_potential(oldV - epsilon);
                double err_minus = c.compute_total_error();

                w->set_potential((err_plus < err_minus) ? oldV + epsilon : oldV - epsilon);
                error = (err_plus < err_minus) ? err_plus : err_minus;
            }

            if (std::abs(old_error - error) < limit)
            {
                std::cout << "error : " << error << std::endl;
                std::cout << "Blocked and can't improve more " << std::endl;
                break;
            }

            std::cout << error << "      \r" << std::flush;
            ++k;
        }

        std::cout << std::endl
                  << "circuit solved in" << k << "interations" << std::endl;
        return true;
    }
};

template <typename SOLVER, typename Circuit_type>
bool solve(Circuit_type &c, double limit = -1.)
{
    if constexpr (std::is_same_v<SOLVER, NaiveSolve>)
    {
        if (limit == -1.)
            limit = 1e-6; // default value
        static_assert(
            crt::Concept::NaiveSolve_Circuit<Circuit_type>,
            "\ncrt::Concept::NaiveSolve_Circuit is not satisfied.\n");
    }
    else if constexpr (std::is_same_v<SOLVER, Grad_Desc>)
    {
        if (limit == -1.)
            limit = 1e-14; // default value
        static_assert(
            crt::Concept::Grad_Desc<Circuit_type>,
            "\ncrt::Concept::Grad_Desc is not satisfied.\n"
            "use crt::GradCircuit or another class with methode compute_grad().\n");
    }
    SOLVER s;
    return s.solve(c, limit);
};