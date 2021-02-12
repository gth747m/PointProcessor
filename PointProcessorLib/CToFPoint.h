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
    protected:
        /// <summary>
        /// Convert the input point's value from Celcius to Farenheit
        /// </summary>
        inline virtual void _calc()
        {
            V val = (V)(this->input_point->get_value() * 1.8 + 32);
            this->value = static_cast<T>(val);
        }
    private:
        /// <summary>
        /// Input points
        /// </summary>
        Point<V>* input_point = nullptr;
    };
}
