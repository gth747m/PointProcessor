#pragma once

#include "PointProcessorLib.h"

namespace PointProcessor
{
    /// <summary>
    /// Celsius to Farenheit point
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    /// <typeparam name="V">Input point type</typeparam>
    template <typename T, typename V = T>
    class CToFPoint :
        public Point<T>
    {
    public:
        /// <summary>
        /// Set the input point
        /// </summary>
        /// <param name="point">Input point who's value is Celcius</param>
        inline void set_input(Point<V>* point)
        {
            this->input_point = point;
        }
        /// <summary>
        /// Convert the input point's value from Celcius to Farenheit
        /// </summary>
        inline void calculate()
        {
            using namespace std::chrono;
            steady_clock::time_point t1 = steady_clock::now();
            V val = this->input_point->get_value() * 1.8 + 32;
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
        /// Input points
        /// </summary>
        Point<V>* input_point;
    };
}
