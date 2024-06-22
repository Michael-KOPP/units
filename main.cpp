#include "dimension/dimension_op.hpp"

template<composed_dim dim>
class unit
{

};

template<composed_dim dim, typename E, typename F>
class affine_quantity
{
    public:
    constexpr affine_quantity(double value) : value(value) {

    }


};

int main(int, char**){
    using speed_dim = composed_dimension<fractional_dimension<time_dim, std::ratio<-1, 1>>, fractional_dimension<length, std::ratio<1, 1>>>;
    
    using time_dim = composed_dimension<fractional_dimension<time_dim, std::ratio<1, 1>>>;


    using length_dim_from_speed_times_time = typename dimension_prod<speed_dim, time_dim>::type;
    using length_dim = composed_dimension<fractional_dimension<length, std::ratio<1, 1>>>;

    constexpr bool eq = std::is_same_v<length_dim_from_speed_times_time, length_dim>;
}
