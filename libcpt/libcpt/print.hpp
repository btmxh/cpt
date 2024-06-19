#pragma once

#include <iostream>
#include <ostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <type_traits>

#pragma cpt begin
#include "is_iterable.hpp"
#pragma cpt end

namespace cpt {

template <class T> std::string to_string(const T &value) {
  std::stringstream ss;
  ss << value;
  return ss.str();
}

template <class OStream> class prefix_suffix_raii {
private:
  OStream &os;
  std::string_view suffix;

public:
  prefix_suffix_raii(OStream &os, std::string_view prefix = "[",
                     std::string_view suffix = "]")
      : os{os}, suffix{suffix} {
    os << prefix;
  }

  ~prefix_suffix_raii() { os << suffix; }
};

template <class OStream> class delim_stream {
private:
  OStream &stream;
  bool first = true;
  std::string_view delim;

public:
  delim_stream(OStream &stream, std::string_view delim = ", ")
      : stream{stream}, delim{delim} {}

  template <class T> void append(const T &value) {
    if (!first) {
      stream << delim;
    }
    first = false;
    stream << value;
  }

  // shorthand alias
  template <class T> void ps(const T &value) { append(value); }
};

template <class Tup> inline void print_tuple(std::ostream &st, const Tup &tup) {
  delim_stream s{st};
  prefix_suffix_raii _{st};
  std::apply([&](const auto &...args) { (s.ps(args), ...); }, tup);
}

template <class... Args>
inline std::ostream &operator<<(std::ostream &st,
                                const std::tuple<Args...> &args) {
  print_tuple(st, args);
  return st;
}

template <class K, class V>
inline std::ostream &operator<<(std::ostream &st, const std::pair<K, V> &args) {
  print_tuple(st, args);
  return st;
}

// iterable printing
template <class T, class = std::enable_if_t<is_iterable<T>>>
std::ostream &operator<<(std::ostream &st, const T &value) {
  delim_stream s{st};
  prefix_suffix_raii _{st};
  for (const auto &val : value) {
    s.ps(val);
  }
  return st;
}

template <class T, class Seq>
std::ostream &operator<<(std::ostream &st, const std::queue<T, Seq> &value) {
  delim_stream s{st};
  prefix_suffix_raii _{st};
  auto val_cpy = value;
  while (val_cpy.size()) {
    s.ps(val_cpy.front());
    val_cpy.pop();
  }
  return st;
}

template <class T, class Seq>
std::ostream &operator<<(std::ostream &st, const std::stack<T, Seq> &value) {
  delim_stream s{st};
  prefix_suffix_raii _{st};
  auto val_cpy = value;
  while (val_cpy.size()) {
    s.ps(val_cpy.top());
    val_cpy.pop();
  }
  return st;
}

// function-like printing
template <class... Args> void print_stdout(const Args &...args) {
  delim_stream s{std::cout, " "};
  ((s.ps(args)), ...);
}
template <class... Args> void print_stderr(const Args &...args) {
  delim_stream s{std::cout, ","};
  ((s.ps(args)), ...);
}
template <class... Args> void println_stdout(const Args &...args) {
  print_stdout(args...);
  std::cout << '\n';
}
template <class... Args> void println_stderr(const Args &...args) {
  print_stderr(args...);
  std::cerr << '\n';
}

// debug inspection printing
#define CPT_DEBUG_INSPECT(...) ::cpt::debug_inspect(#__VA_ARGS__, __VA_ARGS__)

template <class... Args>
inline void debug_inspect(const char *prefix, const Args &...args) {
  print_stderr(prefix);
  std::cerr << "=";
  println_stderr(args...);
}

}; // namespace cpt

template <class... Args> inline void p(const Args &...args) {
  ::cpt::println_stdout(args...);
}

template <class... Args> inline void perr(const Args &...args) {
  ::cpt::println_stderr(args...);
}

#define pr(...)                                                                \
  do {                                                                         \
    p(__VA_ARGS__);                                                            \
    return;                                                                    \
  } while (0);

#define py p("YES")
#define pn p("NO")
#define pry pr("YES")
#define prn pr("NO")
#define pyn(x) p(x ? "YES" : "NO")
#define pryn(x) pr(x ? "YES" : "NO")

#ifdef ONLINE_JUDGE
#define DBG(...)
#else
#define DBG(...) CPT_DEBUG_INSPECT(#__VA_ARGS__)
#endif
