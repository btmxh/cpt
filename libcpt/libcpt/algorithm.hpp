#pragma once

#include <algorithm>

#pragma cpt begin
#include "iterate.hpp"
#pragma cpt end

namespace cpt {
template <class Fn> auto compare_select(Fn fn) {
  return [fn](auto &&x, auto &&y) {
    return fn(std::forward<decltype(x)>(x)) < fn(std::forward<decltype(y)>(y));
  };
}
} // namespace cpt

// alias of max_element(allc(c))
template <class Cont> auto maxv(const Cont &c) {
  return max_element(std::cbegin(c), std::cend(c));
}
template <class Cont> auto minv(const Cont &c) {
  return min_element(std::cbegin(c), std::cend(c));
}
template <class Fn> auto cmpsel(Fn fn) { return ::cpt::compare_select(fn); }
