#include <cassert>
#include <iostream>
#include <memory>

#include "Point.h"
#include "AveragePoint.h"
#include "SumPoint.h"

using namespace PointProcessor;

void SUM_POINT_TEST()
{
    auto p1 = Point<float>();
    auto p2 = Point<float>();
    {
        auto sum_point = SumPoint<int, float>();
        sum_point.add_input(&p1);
        sum_point.add_input(&p2);
        p1.set_value(1.3f);
        p2.set_value(5.6f);
        sum_point.calculate();
        assert(sum_point.get_value() == 6);
    }
    {
        auto sum_point = SumPoint<float>();
        sum_point.add_input(&p1);
        sum_point.add_input(&p2);
        p1.set_value(1.3f);
        p2.set_value(5.7f);
        sum_point.calculate();
        assert(sum_point.get_value() == 7.0f);
    }
}

void AVERAGE_POINT_TEST()
{
    auto p1 = Point<int>();
    auto p2 = Point<int>();
    auto avg_point = AveragePoint<int>();
    avg_point.add_input(&p1);
    avg_point.add_input(&p2);
    p1.set_value(1);
    p2.set_value(4);
    avg_point.calculate();
    assert(avg_point.get_value() == 2);
    p1.set_value(9);
    p2.set_value(5);
    avg_point.calculate();
    assert(avg_point.get_value() == 7);
}

int main()
{
    //SUM_POINT_TEST();
    //AVERAGE_POINT_TEST();
    std::vector<std::shared_ptr<Point<float>>> external_reals;
    auto avg_point = AveragePoint<int, float>();
    for (int i = 0; i < 100; i++)
    {
        auto xr = std::make_shared<Point<float>>();
        xr->set_value(static_cast<float>(i));
        external_reals.push_back(xr);
        avg_point.add_input(xr.get());
    }
    for (int i = 1; i < 100; i++)
    {
        avg_point.calculate();
        std::cout << avg_point.get_average_calc_time().count() << std::endl;
    }
}

