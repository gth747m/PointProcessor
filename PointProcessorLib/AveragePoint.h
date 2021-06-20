#pragma once

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
        inline virtual void calc()
        {
            if (this->input_points.size() == 0)
            {
                this->quality = Quality::NOT_CALCULABLE;
                return;
            }
            Quality qual = Quality::GOOD;
            bool first = true;
            V val = V();
            for (auto point = this->input_points.cbegin();
                point != this->input_points.cend(); point++)
            {
                if (first)
                {
                    val = (*point)->get_value();
                    first = false;
                }
                else
                {
                    val += (*point)->get_value();
                }
                if (!IsUsableQuality((*point)->get_quality()))
                {
                    qual = Quality::NOT_CALCULABLE;
                    return;
                }
            }
            this->value = static_cast<T>(val) / static_cast<T>(this->input_points.size());
            this->quality = qual;
        }
    private:
        /// <summary>
        /// List of input points
        /// </summary>
        std::vector<Point<V>*> input_points;
    };
}
