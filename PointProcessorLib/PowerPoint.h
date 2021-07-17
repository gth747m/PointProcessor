#pragma once

#include <iostream>
#include <vector>

#include "Point.h"

namespace PointProcessor
{
    /// <summary>
    /// Power point
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    template <typename T>
    class PowerPoint :
        public Point
    {
    public:
        /// <summary>
        /// Set the input point to digitally filter
        /// </summary>
        /// <param name="point">Point to filter</param>
        inline void set_input(Point* point)
        {
            this->input_point = point;
        }
        /// <summary>
        /// Set the power to which the input is raised (default 1)
        /// </summary>
        /// <param name="power">Power to which the input is raised</param>
        inline void set_power(T power)
        {
            this->power = power;
        }
    protected:
        /// <summary>
        /// Raise the input point to the specified power
        /// </summary>
        inline virtual void calc()
        {
            if (this->input_point == nullptr)
            {
                std::cerr << "Input point not set." << std::endl;
                this->quality = Quality::NOT_CALCULABLE;
                return;
            }
            if (!IsUsableQuality(this->input_point->get_quality()))
            {
                std::cerr << "Input point bad quality." << std::endl;
                this->quality = this->input_point->get_quality();
                return;
            }
            this->value = static_cast<double>(
                std::pow(this->input_point->get_value<T>(), static_cast<T>(this->power)));
            this->quality = this->input_point->get_quality();
        }
    private:
        /// <summary>
        /// Input point
        /// </summary>
        Point* input_point = nullptr;
        /// <summary>
        /// Power to which the input point is raised
        /// </summary>
        T power = 1.0;
    };
}
