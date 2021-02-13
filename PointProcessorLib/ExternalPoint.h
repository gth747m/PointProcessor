#pragma once

#include <vector>

#include "Point.h"

namespace PointProcessor
{
    /// <summary>
    /// External point
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    template <typename T>
    class ExternalPoint :
        public Point<T>
    {
    public:
        /// <summary>
        /// Set the point value
        /// </summary>
        /// <param name="value">Point value</param>
        void set_value(T value)
        {
            this->value = value;
        }
        /// <summary>
        /// Set the point quality
        /// </summary>
        /// <param name="quality">Point quality</param>
        void set_quality(Quality quality)
        {
            this->quality = quality;
        }
    protected:
    private:
    };
}