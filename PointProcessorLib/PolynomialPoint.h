#pragma once

#include <cmath>
#include <utility>
#include <vector>

#include "Point.h"

namespace PointProcessor
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
            for (auto pointPair = this->input_points.cbegin(); 
                pointPair != this->input_points.cend(); pointPair++)
            {
                if (!IsUsableQuality(pointPair->first->get_quality()) ||
                    !IsUsableQuality(pointPair->second->get_quality()))
                {
                    this->quality = Quality::NOT_CALCULABLE;
                    return;
                }
                if (power > 0)
                {
                    val += static_cast<T>(pointPair->first->template get_value<T>() *
                        std::pow(pointPair->second->template get_value<T>(), static_cast<T>(power)));
                }
                else
                {
                    val += pointPair->first->template get_value<T>();
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
