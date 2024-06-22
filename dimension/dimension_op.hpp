#pragma once
#include "dimension/dimension.hpp"


template<composed_dim d, fractional_dim dim>
struct dimension_append
{
};

template<typename ... args1, fractional_dim dim>
struct dimension_append<composed_dimension<args1...>, dim>
{
    using type = composed_dimension<args1..., dim>;
};

template<composed_dim dim1, composed_dim dim2, 
        composed_dim dim1_buffer = composed_dimension<>, 
        composed_dim dim2_buffer = composed_dimension<>, 
        composed_dim result = composed_dimension<>>
struct dimension_prod
{

};

template<dim d, rat r1, rat r2, fractional_dim ... dims1, fractional_dim ... dims2,
        composed_dim dim_buffer, 
        composed_dim result>
struct dimension_prod<composed_dimension<fractional_dimension<d, r1>, dims1...>, composed_dimension<fractional_dimension<d, r2>, dims2...>,
    dim_buffer,
    result>
{
    using ratio_sum = std::ratio_add<r1, r2>;
    using fractional_dim_result = fractional_dimension<d, ratio_sum>;

    using new_result = std::conditional_t<ratio_sum::num == 0, result, typename dimension_append<result, fractional_dim_result>::type>;
    using type = typename dimension_prod<composed_dimension<dims1...>, composed_dimension<dims2...>,
                dim_buffer,
                new_result>::type;
};

template<fractional_dim dim1, fractional_dim ... dims1, fractional_dim dim2, fractional_dim ... dims2,
        composed_dim dim_buffer, 
        composed_dim result>
struct dimension_prod<composed_dimension<dim1, dims1...>, composed_dimension<dim2, dims2...>,
    dim_buffer,
    result>
{
    using type = typename dimension_prod<composed_dimension<dim1, dims1...>, composed_dimension<dims2...>,
                typename dimension_append<dim_buffer, dim2>::type,
                result>::type;
};

template<fractional_dim dim1, fractional_dim ... dims1,
        composed_dim dim_buffer, 
        composed_dim result>
struct dimension_prod<composed_dimension<dim1, dims1...>, composed_dimension<>,
    dim_buffer,
    result>
{
    using type = typename dimension_prod<composed_dimension<dims1...>, dim_buffer,
                composed_dimension<>,
                typename dimension_append<result, dim1>::type>::type;
};

template<fractional_dim dim2, fractional_dim ... dims2,
        composed_dim result>
struct dimension_prod<composed_dimension<>, composed_dimension<dim2, dims2...>,
    composed_dimension<>,
    result>
{
    using type = typename dimension_prod<composed_dimension<>, composed_dimension<dims2...>,
                composed_dimension<>,
                typename dimension_append<result, dim2>::type>::type;
};

template<composed_dim result>
struct dimension_prod<composed_dimension<>, composed_dimension<>,
    composed_dimension<>,
    result>
{
    using type = result;
};