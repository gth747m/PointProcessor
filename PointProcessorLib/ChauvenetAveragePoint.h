#pragma once

#include <vector>

#include "Point.h"

namespace PointProcessor
{
    /// <summary>
    /// Chauvenet Averaging point
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    template <typename T>
    class ChauvenetAveragePoint :
        public Point
    {
    public:
        /// <summary>
        /// Add a point the the list of inputs to average
        /// </summary>
        /// <param name="point">Point to add</param>
        inline void add_input(Point* point)
        {
            this->input_points.push_back(point);
        }
    protected:
        /// <summary>
        /// Average the value of the input points
        /// </summary>
        inline virtual void calc()
        {
            if (this->input_points.size() == 0)
            {
                this->quality = Quality::NOT_CALCULABLE;
                return;
            }
            Quality qual = Quality::GOOD;
            bool first = true;
            // TODO: Get the average
            V avg = V();
            for (auto point = this->input_points.cbegin();
                point != this->input_points.cend(); point++)
            {
                if (first)
                {
                    avg = (*point)->get_value<T>();
                    first = false;
                }
                else
                {
                    avg += (*point)->get_value<T>();
                }
                if (!IsUsableQuality((*point)->get_quality()))
                {
                    qual = Quality::NOT_CALCULABLE;
                    return;
                }
            }
            avg = static_cast<T>(avg) / static_cast<T>(this->input_points.size());
            // TODO: Get standard deviation
            V stdev = V();
            // TODO: Set value
            //this->value = 
            this->quality = qual;
        }
    private:
        /// <summary>
        /// List of input points
        /// </summary>
        std::vector<Point*> input_points;
    };
}
