#pragma once

#include <iostream>
#include <istream>
#include <utility>

#pragma cpt begin
#include "types.hpp"
#pragma cpt end

namespace cpt {

template <class K, class V>
std::istream &operator>>(std::istream &is, std::pair<K, V> &value) {
  is >> value.first >> value.second;
  return is;
}
template <class... Args>
std::istream &operator>>(std::istream &is, std::tuple<Args...> &value) {
  std::apply([&](auto &...args) { ((is >> args), ...); });
  return is;
}

// sized input
template <class T, class Container = std::vector<T>>
inline Container sized_input(std::istream &is, size_t n) {
  Container c;
  for (size_t i = 0; i < n; ++i) {
    typename Container::value_type value;
    is >> value;
    c.insert(c.end(), value);
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

template <size_t N, class T = ::cpt::ll>
inline std::array<T, N> input_stdin_array() {
  std::array<T, N> arr;
  for (auto &a : arr)
    std::cin >> a;
  return arr;
}

} // namespace cpt

// CP friendly API
template <class T = long long> inline T input() {
  return cpt::input_stdin<T>();
}

template <class T = ::cpt::ll, class Container = std::vector<T>>
inline Container load(::cpt::ll n) {
  return cpt::sized_input<T, Container>(std::cin, ::cpt::ll_to_size(n));
}

#define ia(...) input_stdin_array<__VA_ARGS__>()
