#include "Point.h"

namespace point_processor
{

    /// <summary>
    /// Point constructor
    /// </summary>
    Point::Point(double* value, Quality* quality, std::chrono::duration<int, std::micro>* average_calc_time) :
        value(value),
        quality(quality),
        average_calc_time(average_calc_time)
    {
    }

    /// <summary>
    /// Get the point quality
    /// </summary>
    /// <returns>Point quality</returns>
    Quality Point::get_quality() const
    {
        return *this->quality;
    }

    /// <summary>
    /// Get the average time it takes to calculate this point
    /// </summary>
    /// <returns>Average calculation time</returns>
    std::chrono::duration<int, std::micro> Point::get_average_calc_time() const
    {
        return *this->average_calc_time;
    }

    /// <summary>
    /// Calculate the point value
    /// </summary>
    void Point::calculate()
    {
        using namespace std::chrono;
        steady_clock::time_point t1 = steady_clock::now();
        this->calc();
        auto calc_duration = duration_cast<duration<int, std::micro>>(
            std::chrono::steady_clock::now() - t1);
        if (this->average_calc_time->count() == 0)
        {
            *this->average_calc_time = calc_duration;
        }
        else
        {
            auto avg = 0.1 * calc_duration.count() +
                0.9 * this->average_calc_time->count();
            auto int_avg = static_cast<int>(avg);
            *this->average_calc_time = duration<int, std::micro>(int_avg);
        }
    }

    /// <summary>
    /// Print the point summary to an output stream
    /// </summary>
    /// <param name="os">Output stream</param>
    /// <param name="point">Point</param>
    /// <returns>Output stream</returns>
    std::ostream& operator<<(std::ostream& os, Point& point)
    {
        os << "POINT" << std::endl
            << "    Value       = " << point.get_value<double>() << std::endl
            << "    Quality     = " << point.get_quality() << std::endl
            << "    Avg Calc    = " << point.get_average_calc_time().count()
            << " usec" << std::endl
            ;
        return os;
    }
}
