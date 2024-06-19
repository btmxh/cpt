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

std::string to_string(const auto &value) {
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
  bool first = false;
  std::string_view delim;

public:
  delim_stream(OStream &stream, std::string_view delim = ", ")
      : stream{stream}, delim{delim} {}

  void append(const auto &value) {
    if (!first) {
      stream << delim;
    }
    first = true;
    stream << value;
  }

  // shorthand alias
  void ps(const auto &value) { append(value); }
};

inline void print_tuple(std::ostream &st, const auto &tup) {
  delim_stream s{st};
  prefix_suffix_raii _{st};
  std::apply([&](const auto &...args) { (s.ps(args), ...); }, tup);
}

template <class... Args>
inline std::ostream &operator<<(std::ostream &st,
                                const std::tuple<Args...> &args) {
  print_tuple(st, args);
}

template <class K, class V>
inline std::ostream &operator<<(std::ostream &st, const std::pair<K, V> &args) {
  print_tuple(st, args);
}

// iterable printing
template <class T, class = std::enable_if_t<is_iterable<T>>>
std::ostream &operator<<(std::ostream &st, const T &value) {
  delim_stream s{st};
  prefix_suffix_raii _{st};
  for (const auto &val : value) {
    s.ps(val);
  }
}

template <class T, class Seq>
std::ostream &operator<<(std::ostream &st, const std::queue<T, Seq> &value) {
  delim_stream s{st};
  prefix_suffix_raii _{st};
  auto val_cpy = value;
  while (val_cpy.size()) {
    s << val_cpy.front();
    val_cpy.pop();
  }
}

template <class T, class Seq>
std::ostream &operator<<(std::ostream &st, const std::stack<T, Seq> &value) {
  delim_stream s{st};
  prefix_suffix_raii _{st};
  auto val_cpy = value;
  while (val_cpy.size()) {
    s << val_cpy.top();
    val_cpy.pop();
  }
}

// function-like printing
void print_stdout(const auto &...args) {
  delim_stream s{std::cout, ","};
  ((s << args), ...);
}

void print_stderr(const auto &...args) {
  delim_stream s{std::cout, ","};
  ((s << args), ...);
}

void println_stdout(const auto &...args) {
  print_stdout(args...);
  std::cout << '\n';
}

void println_stderr(const auto &...args) {
  print_stderr(args...);
  std::cerr << '\n';
}

// debug inspection printing
#define CPT_DEBUG_INSPECT(...) debug_inspect(#__VA_ARGS__, __VA_ARGS__)

inline void debug_inspect(const char *prefix, const auto &...args) {
  print_stderr(prefix);
  std::cerr << "=";
  println_stderr(args...);
}

}; // namespace cpt

inline void p(const auto &...args) { println_stdout(args...); }
inline void perr(const auto &...args) { println_stderr(args...); }

#define pr(...)                                                                \
  do {                                                                         \
    p(__VA_ARGS__);                                                            \
    return;                                                                    \
  } while (0);

#define py p("YES")
#define pn p("NO")
#define pry pr("YES")
#define prn pr("NO")
#define pyn(x) p(x? "YES" : "NO")
#define pryn(x) pr(x? "YES" : "NO")

#ifdef ONLINE_JUDGE
#define DBG(...)
#else
#define DBG(...) CPT_DEBUG_INSPECT(#__VA_ARGS__)
#endif
