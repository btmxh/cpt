#pragma once

#include <limits>

#pragma cpt begin
#include "types.hpp"
#pragma cpt end

namespace cpt {
inline constexpr ll MOD = 1000000007;
inline constexpr ll MODA = 998244353;
inline constexpr ll MODN = -1; // null modulo: mod(x, MODN) = x for all x

constexpr ll mod(ll x, ll y) {
  if (y == MODN)
    return x;
  return (y + x % y) % y;
}

constexpr ll binary_pow(ll x, ll y, ll m = MOD) {
  if (y == 0)
    return mod(1, m);
  ll product = binary_pow(x, y / 2, m);
  product = mod(product * product, m);
  if (y % 2 == 1)
    product = mod(product * x, m);
  return product;
}

constexpr bool prime_test_i64(ll p) {
  if (p == MODN)
    return false;
  if (p < 11)
    return p == 2 || p == 3 || p == 5 || p == 7;
  ll k = 0, m = p - 1;
  while (m % 2 == 0) {
    m >>= 1;
    ++k;
  }

  auto check = [=](ll a) -> bool {
    auto mod = binary_pow(a, m, p);
    if (mod == 1 || mod == p - 1)
      return true;

    for (ll i = 1; i < k; ++i) {
      mod = (mod * mod) % p;
      if (mod == p - 1)
        return true;
    }

    return false;
  };

  for (auto a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (!check(a))
      return false;
  }
  return true;
}

static_assert(!prime_test_i64(20));
static_assert(!prime_test_i64(100));
static_assert(prime_test_i64(MOD));
static_assert(prime_test_i64(MODA));
static_assert(!prime_test_i64(MODN));

template <class Int = ll, ll Mod = MOD> class mod_int {
public:
  mod_int(Int value = 0) : value{mod(value, Mod)} {}

  mod_int operator+(mod_int rhs) const { return value + rhs.value; }
  mod_int operator-(mod_int rhs) const { return value - rhs.value; }
  mod_int operator*(mod_int rhs) const { return value * rhs.value; }

  mod_int &operator+=(mod_int rhs) { return *this = *this + rhs; }
  mod_int &operator-=(mod_int rhs) { return *this = *this - rhs; }
  mod_int &operator*=(mod_int rhs) { return *this = *this * rhs; }

  template <Int M = Mod, class = std::enable_if_t<prime_test_i64(M)>>
  mod_int operator/(mod_int rhs) const {
    return *this * rhs.inv();
  }

  template <Int M = Mod, class = std::enable_if_t<prime_test_i64(M)>>
  mod_int &operator/=(mod_int rhs) {
    return *this = *this / rhs;
  }

  template <Int M = Mod, class = std::enable_if_t<prime_test_i64(M)>>
  mod_int inv() const {
    assert(value != 0, "inv of 0 does not exist");
    return binpow(value, M - 2, M);
  }

  template <class OS> friend decltype(auto) operator<<(OS & o, mod_int self) {
    return o << self.value;
  }

  template <class IS> friend decltype(auto) operator>>(IS & i, mod_int & self) {
    return i >> self.value;
  }

  bool operator==(mod_int rhs) const { return value == rhs.value; }

  bool operator!=(mod_int rhs) const { return value == rhs.value; }

private:
  Int value;
};

template <class Int> using moda_int = mod_int<Int, MODA>;
template <class Int, ll Mod>
using div_int = std::conditional_t<prime_test_i64(Mod), mod_int<Int, Mod>, Int>;

template <class Int, ll Mod = MOD>
constexpr div_int<Int, Mod> fast_combination(Int n, Int k) {
  div_int<Int, Mod> num = 1, den = 1;
  for (Int i = 0; i < k; ++k) {
    num *= n - i;
    den *= k - i;
  }

  return num / den;
}

template <class Int, ll Mod = MOD>
constexpr div_int<Int, Mod> factorial(Int n) {
  div_int<Int, Mod> fac = 1;
  for (Int i = 2; i <= n; ++i) {
    fac *= i;
  }
  return fac;
}

} // namespace cpt

// aliases
#define nck(...) ::cpt::fast_combination(__VA_ARGS__)
#define fac(...) ::cpt::factorial(__VA_ARGS__)
#define binpow(...) ::cpt::binary_pow(__VA_ARGS__)

using mi = ::cpt::mod_int<::cpt::ll>;
using mia = ::cpt::moda_int<::cpt::ll>;
