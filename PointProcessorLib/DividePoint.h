#pragma once

#include "PointProcessorLib.h"

namespace point_processor
{
    /// <summary>
    /// Division point
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    template <typename T>
    class DividePoint :
        public Point
    {
    public:
        /// <summary>
        /// Class Constructor
        /// </summary>
        DividePoint() : Point(PointType::DIVIDE)
        {
        }
        /// <summary>
        /// Add a point the the list of inputs to divide
        /// </summary>
        /// <param name="point">Point to divide</param>
        inline void add_input(Point* point)
        {
            this->input_points.push_back(point);
        }
    protected:
        /// <summary>
        /// Divide the value of the input points
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
                if (!quality::is_usable((*point)->get_quality()))
                {
                    this->quality = Quality::NOT_CALCULABLE;
                    return;
                }
                T next_value = (*point)->template get_value<T>();
                if (first)
                {
                    val = next_value;
                    first = false;
                }
                else
                {
                    if (next_value == 0)
                    {
                        this->quality = Quality::NOT_CALCULABLE;
                        return;
                    }
                    else
                    {
                        val /= next_value;
                    }
                }
            }
            this->value = static_cast<double>(val);
            this->quality = qual;
        }
    private:
        /// <summary>
        /// List of input points
        /// </summary>
        std::vector<Point*> input_points;
    };
}
