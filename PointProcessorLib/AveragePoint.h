#pragma once

#include "PointProcessorLib.h"

namespace point_processor
{
    /// <summary>
    /// Averaging point
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    template <typename T>
    class AveragePoint :
        public Point
    {
    public:
        /// <summary>
        /// Add a point the the list of inputs to average
        /// </summary>
        /// <param name="point">Point to add</param>
        inline void add_input(Point* point)
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
            T val = T();
            for (auto point = this->input_points.cbegin();
                point != this->input_points.cend(); point++)
            {
                if (first)
                {
                    val = (*point)->template get_value<T>();
                    first = false;
                }
                else
                {
                    val += (*point)->template get_value<T>();
                }
                if (!quality::is_usable((*point)->get_quality()))
                {
                    this->quality = Quality::NOT_CALCULABLE;
                    return;
                }
            }
            this->value = static_cast<double>(val / this->input_points.size());
            this->quality = qual;
        }
    private:
        /// <summary>
        /// List of input points
        /// </summary>
        std::vector<Point*> input_points;
    };
}
