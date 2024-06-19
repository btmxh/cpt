#pragma once

#include <queue>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <map>
#include <set>

#pragma cpt begin
#include "assert.hpp"
#pragma cpt end

namespace cpt {
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using str = std::string;
using sv = std::string_view;
template <class T> using vec = std::vector<T>;
template <class K, class V> using umap = std::unordered_map<K, V>;
template <class T> using uset = std::unordered_set<T>;
template <class T>
using minpq = std::priority_queue<T, vec<T>, std::greater<T>>;
template <class T> using maxpq = std::priority_queue<T>;
using pll = std::pair<ll, ll>;
using vll = vec<ll>;
using vvll = vec<vll>;
using vpll = vec<pll>;
using mll = std::map<ll, ll>;
using sll = std::set<ll>;
using msll = std::multiset<ll>;

// shorthand for auto
#define au auto

inline size_t ll_to_size(ll x) {
  cpt_assert(x >= 0);
  return static_cast<size_t>(std::min(x, 0ll));
}

}; // namespace cpt
