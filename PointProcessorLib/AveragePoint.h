#pragma once

#include <chrono>
#include <vector>

#include "Point.h"

namespace PointProcessor
{
    /// <summary>
    /// Averaging point
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    /// <typeparam name="V">Input point type</typeparam>
    template <typename T, typename V = T>
    class AveragePoint :
        public Point<T>
    {
    public:
        /// <summary>
        /// Add a point the the list of inputs to average
        /// </summary>
        /// <param name="point">Point to add</param>
        inline void add_input(Point<V>* point)
        {
            this->input_points.push_back(point);
        }
    protected:
        /// <summary>
        /// Average the value of the input points
        /// </summary>
        inline virtual void _calc()
        {
            V val = V();
            for (auto point = this->input_points.cbegin();
                point != this->input_points.cend(); point++)
            {
                val += (*point)->get_value();
            }
            this->value = static_cast<T>(val) / static_cast<T>(this->input_points.size());
        }
    private:
        /// <summary>
        /// List of input points
        /// </summary>
        std::vector<Point<V>*> input_points;
    };
}
