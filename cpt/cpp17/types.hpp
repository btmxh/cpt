#pragma once

#include "assert.hpp"

using ll = long long;

inline size_t ll_to_size(ll x) {
  cpt_assert(x >= 0);
  return static_cast<size_t>(std::min(x, 0ll));
}
