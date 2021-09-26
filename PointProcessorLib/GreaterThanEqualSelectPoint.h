#pragma once

#include "PointProcessorLib.h"

namespace point_processor
{
    /// <summary>
    /// If the first input is greater than or equal to the second
    /// then select the first output point, else select the second
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    template <typename T>
    class GreaterThanEqualSelectPoint :
        public Point
    {
    public:
        /// <summary>
        /// Set the input points
        /// </summary>
        /// <param name="point1">Input point to compare to point2</param>
        /// <param name="point2">Input point to compare to point1</param>
        inline void set_inputs(Point* point1, Point* point2)
        {
            this->input_points = std::make_pair(point1, point2);
        }
        /// <summary>
        /// Set the output points
        /// </summary>
        /// <param name="point1">Output point if point1 >= point2</param>
        /// <param name="point2">Output point if point1 < point2</param>
        inline void set_outputs(Point* point1, Point* point2)
        {
            this->output_points = std::make_pair(point1, point2);
        }
    protected:
        /// <summary>
        /// Convert the input point's value from Celcius to Farenheit
        /// </summary>
        inline virtual void calc()
        {
            if (input_points.first == nullptr || input_points.second == nullptr ||
                output_points.first == nullptr || output_points.second == nullptr)
            {
                this->quality = Quality::NOT_CALCULABLE;
                return;
            }
            if (this->input_points.first->template get_value<T>() >=
                this->input_points.second->template get_value<T>())
            {
                if (quality::is_usable(this->input_points.first->get_quality()))
                {
                    this->value = static_cast<double>(this->output_points.first->template get_value<T>());
                    this->quality = this->output_points.first->get_quality();
                    return;
                }
                else
                {
                    this->quality = Quality::NOT_CALCULABLE;
                    return;
                }
            }
            else
            {
                if (quality::is_usable(this->input_points.second->get_quality()))
                {
                    this->value = static_cast<double>(this->output_points.second->template get_value<T>());
                    this->quality = this->output_points.second->get_quality();
                    return;
                }
                else
                {
                    this->quality = Quality::NOT_CALCULABLE;
                    return;
                }
            }
        }
    private:
        /// <summary>
        /// Input points
        /// </summary>
        std::pair<Point*, Point*> input_points;
        /// <summary>
        /// Output points
        /// </summary>
        std::pair<Point*, Point*> output_points;
    };
}
