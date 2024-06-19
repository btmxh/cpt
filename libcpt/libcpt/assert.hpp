#pragma once

#include <iostream>

#ifndef ONLINE_JUDGE
#define cpt_assert(x) ::cpt::do_cpt_assert(__FILE__, __LINE__, #x, x)
#define cpt_assertm(x, m) ::cpt::do_cpt_assert(__FILE__, __LINE__, #x, x, m)
#else
#define cpt_assert(...)
#define cpt_assertm(...)
#endif

namespace cpt {
template <typename T>
T do_cpt_assert(const char *file, int line, const char *value_str, T value,
                const char *message = "debug assertion failed") {
  if (!value) {
    std::cerr << message << " at " << file << ":" << line << ": " << value_str
              << '\n';
    std::exit(1);
  }
  return value;
}
} // namespace cpt
