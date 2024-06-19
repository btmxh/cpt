#pragma once

#include <queue>
#include <type_traits>

namespace cpt {

template <class T, class = void> inline constexpr bool is_iterable = false;

template <class T>
inline constexpr bool
    is_iterable<T, std::void_t<decltype(std::declval<T>().cbegin()),
                               decltype(std::declval<T>().cend())>> = true;
static_assert(is_iterable<const std::vector<int>>);
static_assert(!is_iterable<std::queue<int>>);

} // namespace cpt
