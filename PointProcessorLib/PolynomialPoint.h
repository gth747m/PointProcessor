#pragma once

#include "PointProcessorLib.h"

namespace point_processor
{
    /// <summary>
    /// Polynomial point
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    template <typename T>
    class PolynomialPoint :
        public Point
    {
    public:
        /// <summary>
        /// Class Constructor
        /// </summary>
        PolynomialPoint() : Point(PointType::POLYNOMIAL)
        {
        }
        /// <summary>
        /// Add a coefficient and variable as the next degree of the polynomial
        /// </summary>
        /// <param name="coefficient">Next degree coefficient</param>
        /// <param name="variable">Next degree variable</param>
        inline void add_input(Point* coefficient, Point* variable)
        {
            this->input_points.emplace_back(
                std::make_pair(coefficient, variable));
        }
    protected:
        /// <summary>
        /// Calculate the value of the polynomial
        /// </summary>
        inline virtual void calc()
        {
            if (this->input_points.size() == 0)
            {
                this->quality = Quality::NOT_CALCULABLE;
                return;
            }
            Quality qual = Quality::GOOD;
            T val = T();
            int power = 0;
            for (auto point_pair = this->input_points.cbegin(); 
                point_pair != this->input_points.cend(); point_pair++)
            {
                if (!quality::is_usable(point_pair->first->get_quality()) ||
                    !quality::is_usable(point_pair->second->get_quality()))
                {
                    this->quality = Quality::NOT_CALCULABLE;
                    return;
                }
                if (power > 0)
                {
                    val += static_cast<T>(point_pair->first->template get_value<T>() *
                        std::pow(point_pair->second->template get_value<T>(), static_cast<T>(power)));
                }
                else
                {
                    val += point_pair->first->template get_value<T>();
                }
                power += 1;
            }
            this->value = static_cast<double>(val);
            this->quality = qual;
        }
    private:
        /// <summary>
        /// List of input points
        /// </summary>
        std::vector<std::pair<Point*, Point*>> input_points;
    };
}
