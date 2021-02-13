#pragma once

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
    protected:
        /// <summary>
        /// Sum the value of the input points
        /// </summary>
        inline virtual void calc()
        {
            if (this->input_points.size() == 0)
            {
                this->quality = Quality::NOT_CALCULABLE;
                return;
            }
            Quality qual = Quality::GOOD;
            V val = V();
            for (auto point = this->input_points.cbegin();
                point != this->input_points.cend(); point++)
            {
                val += (*point)->get_value();
                if (!IsUsableQuality((*point)->get_quality()))
                {
                    qual = Quality::NOT_CALCULABLE;
                    return;
                }
            }
            this->value = static_cast<T>(val);
            this->quality = qual;
        }
    private:
        /// <summary>
        /// List of input points
        /// </summary>
        std::vector<Point<V>*> input_points;
    };
}
