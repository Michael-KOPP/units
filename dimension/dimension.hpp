#pragma once
#include <type_traits>
#include <ratio>

class dimension
{

};

template<typename T>
concept dim = std::is_base_of_v<dimension, T>;

class length : public dimension
{

};

class time_dim : public dimension
{

};

class mass : public dimension
{

};

class temperature : public dimension
{

};

class quantity_of_mater : public dimension
{

};

class luminosity : public dimension
{

};

template<typename T>
struct is_ratio
{
    static constexpr bool value = false;
};

template<auto n, auto d>
struct is_ratio<std::ratio<n,d>>
{
    static constexpr bool value = true;
};

template<typename T>
constexpr bool is_ratio_v = is_ratio<T>::value;

template<typename T>
concept rat = is_ratio_v<T>;

template<dim d, rat r>
class fractional_dimension
{

};

template<typename T>
struct is_fractional_dimension
{
    static constexpr bool value = false;
};

template<typename T, typename U>
struct is_fractional_dimension<fractional_dimension<T, U>>
{
    static constexpr bool value = true;
};

template<typename T>
constexpr bool is_fractional_dimension_v = is_fractional_dimension<T>::value;

template<typename T>
concept fractional_dim = is_fractional_dimension_v<T>;

template<fractional_dim ... fractional_dimensions>
class composed_dimension
{
};

template<fractional_dim dim, fractional_dim ... fractional_dimensions>
class composed_dimension<dim, fractional_dimensions...>
{
    using first = dim;
    using pop = composed_dimension<fractional_dimensions...>;

    template<fractional_dim d>
    using append = composed_dimension<dim, fractional_dimensions..., d>;
};

template<typename T>
struct is_composed_dimension
{
    static constexpr bool value = false;
};

template<typename ... T>
struct is_composed_dimension<composed_dimension<T...>>
{
    static constexpr bool value = true;
};

template<typename T>
constexpr bool is_composed_dimension_v = is_composed_dimension<T>::value;

template<typename T>
concept composed_dim = is_composed_dimension_v<T>;