#pragma once

#include <vector>

#include "Point.h"

namespace point_processor
{
    /// <summary>
    /// Summation point
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    template <typename T>
    class SumPoint :
        public Point
    {
    public:
        /// <summary>
        /// Point constructor
        /// </summary>
        SumPoint(double* value, Quality* quality, std::chrono::duration<int, std::micro>* duration) :
            Point(value, quality, duration)
        {
        }
        /// <summary>
        /// Add a point the the list of inputs to sum
        /// </summary>
        /// <param name="point">Point to add</param>
        inline void add_input(Point* point)
        {
            this->input_points.push_back(point);
        }
    protected:
        /// <summary>
        /// Sum the value of the input points
        /// </summary>
        inline virtual void calc()
        {
            if (this->input_points.size() == 0)
            {
                *this->quality = Quality::NOT_CALCULABLE;
                return;
            }
            Quality qual = Quality::GOOD;
            bool first = true;
            T val = T();
            for (auto point = this->input_points.cbegin();
                point != this->input_points.cend(); point++)
            {
                if (!quality::is_usable((*point)->get_quality()))
                {
                    *this->quality = Quality::NOT_CALCULABLE;
                    return;
                }
                if (first)
                {
                    val = (*point)->template get_value<T>();
                    first = false;
                }
                else
                {
                    val += (*point)->template get_value<T>();
                }
            }
            *this->value = static_cast<double>(val);
            *this->quality = qual;
        }
    private:
        /// <summary>
        /// List of input points
        /// </summary>
        std::vector<Point*> input_points;
    };
}
