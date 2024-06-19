#pragma once

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
