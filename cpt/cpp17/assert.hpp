#pragma once

#include <iostream>

#ifndef ONLINE_JUDGE
#define cpt_assert(x) ::cpt::do_cpt_assert(__FILE__, __LINE__, #x, x)
#define cpt_assertm(x, m) ::cpt::do_cpt_assert(__FILE__, __LINE__, #x, x, m)
#endif

namespace cpt {
inline decltype(auto)
do_cpt_assert(const char *file, int line, const char *value_str, auto value,
              const char *message = "debug assertion failed") {
  if (!value) {
    std::cout << message << " at " << file << ":" << line << ": " << value_str
              << '\n';
  }
  return value;
}
} // namespace cpt
