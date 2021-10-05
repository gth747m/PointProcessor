#pragma once

#include "PointProcessorLib.h"

namespace point_processor
{
    /// <summary>
    /// External point
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    template <typename T>
    class ExternalPoint :
        public Point
    {
    public:
        /// <summary>
        /// Class Constructor
        /// </summary>
        ExternalPoint() : Point(PointType::EXTERNAL)
        {
        }
        /// <summary>
        /// Set the point value
        /// </summary>
        /// <param name="value">Point value</param>
        void set_value(T value)
        {
            this->value = static_cast<double>(value);
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