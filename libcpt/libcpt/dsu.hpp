#pragma once

#pragma cpt begin
#include "types.hpp"
#pragma cpt end

namespace cpt {
class naive_disjoint_set {
  vll parent;

public:
  naive_disjoint_set(ll n) : parent(n) {}

  void make_set(ll x) { parent[x] = x; }
  ll repr(ll x) {
    if (x == parent[x]) {
      return x;
    }
    return parent[x] = repr(parent[x]);
  }
  bool unite(ll a, ll b) {
    a = repr(a);
    b = repr(b);
    if (a == b) {
      return false;
    }

    merge(a, b);
    return true;
  }

protected:
  void merge(ll a, ll b) { parent[a] = b; }
};

class sized_disjoint_set : public naive_disjoint_set {
private:
  vll size;

public:
  sized_disjoint_set(ll n) : naive_disjoint_set(n), size(n) {}

  void make_set(ll x) {
    naive_disjoint_set::make_set(x);
    size[x] = 1;
  }

  ll get_size(ll a) { return size[repr(a)]; }

protected:
  void merge(ll a, ll b) {
    if (size[a] > size[b]) {
      std::swap(a, b);
    }

    naive_disjoint_set::merge(a, b);
    size[b] += size[a];
  }
};

class ranked_disjoint_set : public naive_disjoint_set {
private:
  vll rank;

public:
  ranked_disjoint_set(ll n) : naive_disjoint_set(n), rank(n) {}

  void make_set(ll x) {
    naive_disjoint_set::make_set(x);
    rank[x] = 0;
  }

  ll get_rank(ll a) { return rank[repr(a)]; }

protected:
  void merge(ll a, ll b) {
    if (rank[a] > rank[b])
      std::swap(a, b);
    naive_disjoint_set::merge(a, b);
    rank[b] += rank[a] == rank[b];
  }
};
} // namespace cpt

using dsu = cpt::sized_disjoint_set;
