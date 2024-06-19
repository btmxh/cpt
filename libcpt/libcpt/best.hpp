#pragma once

#include <optional>
#include <utility>
namespace cpt {
// C++17-friendly std::identity
struct identity {
  template <class T> T operator()(T value) const { return value; }
};

template <class Key, class ValueFn = identity> class best {
public:
  using value_type = std::invoke_result_t<ValueFn, Key>;

private:
  ValueFn fn;
  std::optional<std::pair<Key, value_type>> record;

public:
  best(ValueFn fn = ValueFn{}) : fn{fn} {}
  best(Key k, ValueFn fn = ValueFn{}) : fn{fn} { update(k); }

  bool update(Key k) {
    auto value = fn(k);
    if (!record || value < record->second) {
      record = std::make_pair(k, value);
      return true;
    }
    return false;
  }

  Key operator*() const { return record->first; }
  operator Key() const { return record->first; }
  auto get_key_or(Key k) const { return record ? record->first : k; }
  auto get_value() const { return record->second; }
};

template <class Fn> struct negate {
  Fn fn;
  negate(Fn fn = Fn{}) : fn{fn} {}
  template <class... Args> auto operator()(Args &&...args) {
    return -fn(std::forward<Args...>(args...));
  }
};

template <class Key, class ValueFn = identity>
struct miner : public best<Key, ValueFn> {
  using best<Key, ValueFn>::best;
};
template <class Key, class ValueFn = identity>
struct maxer : public best<Key, negate<ValueFn>> {
  using best<Key, negate<ValueFn>>::best;
  auto get_value() const { return -best<Key, negate<ValueFn>>::get_value(); }
};
} // namespace cpt
