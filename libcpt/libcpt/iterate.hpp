#pragma once

#include <algorithm>
#include <functional>
#include <iterator>
#include <type_traits>
#include <utility>

#pragma cpt begin
#include "types.hpp"
#pragma cpt end

#define f(i, s, e) fs(i, s, e, 1)
#define fs(i, s, e, st) for (::cpt::ll i = s; i < e; i += st)
#define rf(i, s, e) rfs(i, s, e, 1)
#define rfs(i, s, e, st) for (::cpt::ll i = e - 1; i >= s; i -= st)
#define fe(c, ...) for (auto &[__VA_ARGS__] : c)
#define fer(itr, c) for (auto itr = c.rbegin(); itr != c.rend(); ++itr)
#define fdiv(x, n)                                                             \
  for (::cpt::ll x = 1; x * x <= n; ++x)                                       \
    if (n % x == 0)

#define all(v) ::std::begin(v), ::std::end(v)
#define allc(v) ::std::cbegin(v), ::std::cend(v)
#define allr(v) ::std::rbegin(v), ::std::rend(v)

namespace cpt {
template <class Int = ll> class int_iterator {
private:
  Int value;

public:
  using difference_type = std::make_signed_t<Int>;
  int_iterator(Int value) : value{value} {}

  operator Int() const { return value; }
  Int operator*() const { return value; }

  Int operator++() { return ++value; }
  Int operator++(int) { return value++; }
  Int operator--() { return --value; }
  Int operator--(int) { return value--; }
  Int operator+=(Int amt) { return value += amt; }
  Int operator-=(Int amt) { return value -= amt; }
  friend difference_type operator-(int_iterator x, int_iterator y) {
    return x.value - y.value;
  }
  friend Int operator+(int_iterator x, int_iterator y) {
    return x.value + y.value;
  }

#define MAKEOP(op)                                                             \
  bool operator op(const Int &other) const { return value op other; }
  MAKEOP(==);
  MAKEOP(!=);
  MAKEOP(<=);
  MAKEOP(>=);
  MAKEOP(<);
  MAKEOP(>);
#undef MAKEOP
};
} // namespace cpt

namespace std {
template <class Int> struct iterator_traits<::cpt::int_iterator<Int>> {
  using difference_type = std::make_signed_t<Int>;
  using value_type = Int;
  using iterator_category = std::random_access_iterator_tag;
};
} // namespace std

#ifdef __cpp_lib_span
#include <span>

template <class T> inline auto bisect_span(span<T> sp) {
  size_t mid = sp.size() / 2;
  auto left = sp.subspan(0, mid);
  auto right = sp.subspan(mid, sp.size() - mid);
  return std::make_pair(left, right);
}
#endif

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
