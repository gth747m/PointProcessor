#pragma once

#include "PointProcessorLib.h"

namespace PointProcessor
{
    /// <summary>
    /// Farenheit to Celsius point
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    /// <typeparam name="V">Input point type</typeparam>
    template <typename T, typename V = T>
    class FToCPoint :
        public Point<T>
    {
    public:
        /// <summary>
        /// Set the input point
        /// </summary>
        /// <param name="point">Input point who's value is Farenheit</param>
        inline void set_input(Point<V>* point)
        {
            this->input_point = point;
        }
    protected:
        /// <summary>
        /// Convert the input point's value from Farenheit to Celcius
        /// </summary>
        inline virtual void calc()
        {
            if (input_point == nullptr)
            {
                this->quality = Quality::NOT_CALCULABLE;
                return;
            }
            this->value = static_cast<T>(
                ((this->input_point->get_value() - 32) / 1.8));
            this->quality = this->input_point->get_quality();
        }
    private:
        /// <summary>
        /// Input points
        /// </summary>
        Point<V>* input_point = nullptr;
    };
}
