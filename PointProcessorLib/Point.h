#pragma once

#include <chrono>
#include <string>
#include <vector>

#include "Quality.h"
#include "Frequency.h"

namespace point_processor
{

    /// <summary>
    /// Base Point class
    /// </summary>
    class Point
    {
    public:
        /// <summary>
        /// Point constructor
        /// </summary>
        Point(double* value, Quality* quality, std::chrono::duration<int, std::micro>* duration);
        /// <summary>
        /// Get the point value as type T
        /// </summary>
        /// <typeparam name="T">Type to cast this value to</typeparam>
        /// <returns>Point value</returns>
        template <typename T>
        T get_value() const
        {
            return static_cast<T>(*this->value);
        }
        /// <summary>
        /// Get the point quality
        /// </summary>
        /// <returns>Point quality</returns>
        Quality get_quality() const;
        /// <summary>
        /// Get the average time it takes to calculate this point
        /// </summary>
        /// <returns>Average calculation time</returns>
        std::chrono::duration<int, std::micro> get_average_calc_time() const;
        /// <summary>
        /// Calculate the point value
        /// </summary>
        void calculate();
        /// <summary>
        /// Print the point summary to an output stream
        /// </summary>
        /// <param name="os">Output stream</param>
        /// <param name="point">Point</param>
        /// <returns>Output stream</returns>
        friend std::ostream& operator<<(std::ostream& os, Point& point);
    protected:
        /// <summary>
        /// Point value
        /// </summary>
        double* value;
        /// <summary>
        /// Point calculation
        /// </summary>
        inline virtual void calc() {};
        /// <summary>
        /// Point quality
        /// </summary>
        Quality* quality;
        /// <summary>
        /// Average amount of time it takes to execute this calculation
        /// </summary>
        std::chrono::duration<int, std::micro>* average_calc_time;
    private:
    };
}
