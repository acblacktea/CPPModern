//
// Created by ByteDance on 18/10/23.
//

#ifndef MODERNCPP_CONTAINER_H
#define MODERNCPP_CONTAINER_H
#include <variant>

void testContainer();
void testUnorderedMap();
void testVariant();

template<size_t n, typename... T>
constexpr  std::variant<T...>_tuple_index(const std::tuple<T...>& tpl, size_t i) {
    if constexpr (n >= sizeof...(T)) {
        throw std::out_of_range("out of range");
    }

    std::cout << n << "***" << std::endl;
    if (i == n) {
        std::cout << "finish" << std::endl;
        return std::variant<T...>{std::in_place_index<n>, std::get<n>(tpl)};
    }

    return _tuple_index<(n < sizeof...(T) - 1? n + 1 : 0)>(tpl, i);
}

template<typename... T>
constexpr std::variant<T...> tuple_index(const std::tuple<T...>& tpl, size_t i) {
    return _tuple_index<0>(tpl, i);
}

template<typename T0, typename ...Ts>
std::ostream & operator<< (std::ostream &s, std::variant<T0, Ts...> const &v) {
    std::visit([&](auto &&x) { s << x;}, v);
    return s;
}



#endif //MODERNCPP_CONTAINER_H
