#pragma once

#include "PointProcessorLib.h"

namespace point_processor
{
    /// <summary>
    /// Celsius to Farenheit point
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    template <typename T>
    class CToFPoint :
        public Point
    {
    public:
        /// <summary>
        /// Set the input point
        /// </summary>
        /// <param name="point">Input point who's value is Celcius</param>
        inline void set_input(Point* point)
        {
            this->input_point = point;
        }
    protected:
        /// <summary>
        /// Convert the input point's value from Celcius to Farenheit
        /// </summary>
        inline virtual void calc()
        {
            if (input_point == nullptr)
            {
                this->quality = Quality::NOT_CALCULABLE;
                return;
            }
            this->value = static_cast<T>(
                (this->input_point->template get_value<T>() * 1.8 + 32));
            this->quality = this->input_point->get_quality();
        }
    private:
        /// <summary>
        /// Input points
        /// </summary>
        Point* input_point = nullptr;
    };
}
