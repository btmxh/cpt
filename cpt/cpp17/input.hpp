#pragma once

#include "is_iterable.hpp"
#include "types.hpp"
#include <iostream>
#include <istream>
#include <type_traits>
#include <utility>

namespace cpt {

template <class K, class V>
std::istream &operator>>(std::istream &is, std::pair<K, V> &value) {
  is >> value.first >> value.second;
}
template <class... Args>
std::istream &operator>>(std::istream &is, std::tuple<Args...> &value) {
  std::apply([&](auto &...args) { ((is >> args), ...); });
}

template <class T, std::enable_if_t<is_iterable<T>>>
std::istream &operator>>(std::istream &is, T &value) {
  for (auto &val : value) {
    is >> val;
  }
}

// sized input
template <class T, class Container = std::vector<T>>
inline Container sized_input(std::istream &is, size_t n) {
  Container c;
  for (size_t i = 0; i < n; ++i) {
    is >> std::inserter(c, std::end(c));
  }
  return c;
}

template <class T> T input_stdin() {
  T value;
  std::cin >> value;
  return value;
}

template <class T, class Container = std::vector<T>> T load_stdin(size_t n) {
  return sized_input<T, Container>(std::cin, n);
}

} // namespace cpt

// CP friendly API
template <class T = long long> inline T input() {
  return cpt::input_stdin<T>();
}

template <class T = ll, class Container = std::vector<T>>
inline Container load(ll n) {
  return cpt::sized_input<T, Container>(std::cin, ll_to_size(n));
}
