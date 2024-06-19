#pragma once

#include <algorithm>
#include <initializer_list>

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

constexpr std::initializer_list<pll> adjacent_offsets = {
    {0, 1}, {1, 0}, {-1, 0}, {0, -1}};

// pair pairwise operations
#define MAKEOP(op)                                                             \
  template <class K, class V>                                                  \
  auto operator op(const std::pair<K, V> &lhs, const std::pair<K, V> &rhs) {   \
    return std::make_pair(lhs.first op lhs.second, rhs.first op rhs.second);   \
  }
MAKEOP(+);
MAKEOP(-);
#undef MAKEOP

} // namespace cpt

// alias of max_element(allc(c))
template <class Cont> auto maxv(const Cont &c) {
  return max_element(std::cbegin(c), std::cend(c));
}
template <class Cont> auto minv(const Cont &c) {
  return min_element(std::cbegin(c), std::cend(c));
}
template <class Fn> auto cmpsel(Fn fn) { return ::cpt::compare_select(fn); }

#define pb push_back
#define eb emplace_back

template <class Cont> auto popb(const Cont &c) {
  auto back = c.back();
  c.pop_back();
  return back;
}

template <class Cont> auto popf(const Cont &c) {
  auto front = c.front();
  c.pop_front();
  return front;
}
