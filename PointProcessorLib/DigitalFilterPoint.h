#pragma once

#include <vector>

#include "Point.h"

namespace point_processor
{
    /// <summary>
    /// Digital filter point
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    template <typename T>
    class DigitalFilterPoint :
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
        /// Set the fraction used to filter the input point.
        /// Valid range is 0.0 - 1.0, default = 0.1
        /// </summary>
        /// <param name="fraction">Fraction used to filter the input point</param>
        inline void set_filter_fraction(double fraction)
        {
            this->filter_fraction = fraction;
        }
    protected:
        /// <summary>
        /// Filter the input point
        /// </summary>
        inline virtual void calc()
        {
            if ((this->input_point == nullptr) || 
                (!quality::is_usable(this->input_point->get_quality())))
            {
                this->quality = Quality::NOT_CALCULABLE;
                return;
            }
            if (initialized)
            {
#ifdef _WIN32
// Turn off VC++ warnings about arithmetic overflow
#pragma warning(push)
#pragma warning(disable: 26451)
#endif
                this->value = static_cast<double>(
                    static_cast<T>((1.0 - this->filter_fraction) * this->value) + 
                    static_cast<T>(this->filter_fraction * this->input_point->template get_value<T>()));
#ifdef _WIN32
#pragma warning(pop)
#endif
            }
            else
            {
                this->value = this->input_point->template get_value<double>();
                initialized = true;
            }
            this->quality = this->input_point->get_quality();
        }
    private:
        /// <summary>
        /// Input point
        /// </summary>
        Point* input_point = nullptr;
        /// <summary>
        /// Has this point been calculated at least once?
        /// </summary>
        bool initialized = false;
        /// <summary>
        /// Degree to which the input point is filtered
        /// </summary>
        double filter_fraction = 0.1;
    };
}
