#pragma once

#include <iostream>
#include <vector>

#include "Point.h"

namespace point_processor
{
    /// <summary>
    /// Counter point
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    template <typename T>
    class CounterPoint :
        public Point
    {
    public:
        /// <summary>
        /// Increment the counter
        /// </summary>
        inline void increment()
        {
            count++;
        }
        /// <summary>
        /// Decrement the counter
        /// </summary>
        inline void decrement()
        {
            count--;
        }
    protected:
        /// <summary>
        /// Set the current value to the total count and then reset it
        /// </summary>
        inline virtual void calc()
        {
            this->quality = Quality::GOOD;
            this->value = static_cast<double>(count);
            this->count = 0;
        }
    private:
        /// <summary>
        /// Current count
        /// </summary>
        T count = 0;
    };
}
