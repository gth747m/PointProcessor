#pragma once

#include <chrono>
#include <vector>

#include "Point.h"

namespace PointProcessor
{
    /// <summary>
    /// Summation point
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    /// <typeparam name="V">Input point type</typeparam>
    template <typename T, typename V = T>
    class SumPoint :
        public Point<T>
    {
    public:
        /// <summary>
        /// Add a point the the list of inputs to sum
        /// </summary>
        /// <param name="point">Point to add</param>
        inline void add_input(Point<V>* point)
        {
            this->input_points.push_back(point);
        }
        /// <summary>
        /// Calculate this point's value
        /// </summary>
        inline void calculate()
        {
            using namespace std::chrono;
            steady_clock::time_point t1 = steady_clock::now();
            V val = V();
            for (auto point = this->input_points.cbegin();
                point != this->input_points.cend(); point++)
            {
                val += (*point)->get_value();
            }
            this->value = static_cast<T>(val);
            auto calc_duration = duration_cast<duration<int, std::micro>>(
                    std::chrono::steady_clock::now() - t1);
            if (this->average_calc_time.count() == 0)
            {
                this->average_calc_time = calc_duration;
            }
            else
            {
                this->average_calc_time = duration<int, std::micro>(
                    static_cast<int>(0.1 * calc_duration.count() + 
                        0.9 * this->average_calc_time.count()));
            }
        }
    protected:
    private:
        /// <summary>
        /// List of input points
        /// </summary>
        std::vector<Point<V>*> input_points;
    };
}
