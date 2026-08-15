#pragma once
#include <iostream>
#include <string>
#include <concepts>
#include <type_traits>

#include <crtDefs.hpp>

namespace crt
{
    namespace Concept
    {
        template <typename T>
        concept Component =
            requires(const T t, std::ostream &os, int i) {
                typename T::element_type;

                t->symbol(os, i);
                t->compute_i();
                { t->name(i) } -> std::convertible_to<std::string>;
            };

        template <typename W>
        concept Wire =
            requires(const W w, int i, std::ostream &os) {
                typename W::element_type;
                { w->get_potential() } -> std::convertible_to<double>;
                { w->compute_error() } -> std::convertible_to<double>;
                { w->is_fixed() } -> std::convertible_to<bool>;
                { w->name(i) } -> std::convertible_to<std::string>;
                { w->symbol(os, i) };
            } &&
            requires(W w, crt::Pin_ref p, double v) {
                w == p;
                w->set_potential(v);
            };

        template <typename Circuit>
        concept NaiveSolve_Circuit =
            requires(Circuit c) {
                { c.compute_total_error() } -> std::convertible_to<double>;
                { c.wires } -> std::ranges::range;
                { c.components } -> std::ranges::range;
            } && Wire<typename std::decay_t<decltype(std::declval<Circuit>().wires)>::value_type> &&
            Component<typename std::decay_t<decltype(std::declval<Circuit>().components)>::value_type>;

        template <typename Circuit>
        concept Grad_Desc =
            NaiveSolve_Circuit<Circuit> &&
            requires(Circuit c, typename std::decay_t<decltype(c.wires)>::value_type w) {
                { c.compute_grad() } -> std::ranges::range;
                { *(c.compute_grad().begin()) } -> std::convertible_to<double>;
            };
    }
}