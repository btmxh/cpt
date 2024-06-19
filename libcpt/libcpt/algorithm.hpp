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

// binary search helpers
template <class It, class Func> It first_true(It begin, It end, Func func) {
  return std::upper_bound(begin, end, nullptr,
                          [func](auto, auto x) { return func(x); });
}

template <class It, class Func> It last_true(It begin, It end, Func func) {
  It first_false = first_true(begin, end, std::not_fn(func));
  if (first_false == end) {
    return end;
  }
  return --first_false;
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
