#pragma once

#include <cmath>
#include <vector>

#include "Point.h"

namespace point_processor
{
    /// <summary>
    /// Chauvenet averaging point
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    template <typename T>
    class ChauvenetAveragePoint :
        public Point
    {
    public:
        /// <summary>
        /// Point constructor
        /// </summary>
        ChauvenetAveragePoint(double* value, Quality* quality, std::chrono::duration<int, std::micro>* duration) :
            Point(value, quality, duration)
        {
        }
        /// <summary>
        /// Set the point who's value is the minimum number of good points
        /// </summary>
        /// <param name="point">Point to add</param>
        inline void set_min_good_points(Point* point)
        {
            this->min_good_points = point;
        }
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
            if (this->min_good_points == nullptr)
            {
                *this->quality = Quality::NOT_CALCULABLE;
                return;
            }
            // points to be used in the averaging
            std::vector<Point*> used_points = this->input_points;
            Quality qual;
            // Iterate until we've got a good answer or we run out of points
            while (true)
            {
                T avg = T();
                qual = Quality::GOOD;
                bool first = true;
                if ((used_points.size() < this->min_good_points->template get_value<uint64_t>()) ||
                    (used_points.size() < 3))
                {
                    *this->quality = Quality::NOT_CALCULABLE;
                    return;
                }
                // Get the average
                std::vector<Point*>::const_iterator point_to_remove = used_points.cend();
                for (auto point = used_points.cbegin();
                    point != used_points.cend(); point++)
                {
                    if (!quality::is_usable((*point)->get_quality()))
                    {
                        point_to_remove = point;
                        break;
                    }
                    if (first)
                    {
                        avg = (*point)->template get_value<T>();
                        first = false;
                    }
                    else
                    {
                        avg += (*point)->template get_value<T>();
                    }
                }
                // If we need to remove a point for a bad quality, do so and redo the calculation
                if (point_to_remove != used_points.cend())
                {
                    used_points.erase(point_to_remove);
                    continue;
                }
                // We've got good qualities so get their average
                avg = avg / static_cast<T>(used_points.size());
                // Now calculate the standard deviation
                double stdev = 0;
                first = true;
                for (auto point = used_points.cbegin(); point != used_points.cend(); point++)
                {
                    if (first)
                    {
                        stdev = (avg - (*point)->template get_value<double>()) 
                            * (avg - (*point)->template get_value<double>());
                        first = false;
                    }
                    else
                    {
                        stdev += (avg - (*point)->template get_value<double>()) 
                            * (avg - (*point)->template get_value<double>());
                    }
                }
                stdev = sqrt(stdev / static_cast<uint64_t>(used_points.size()));
                // Don't divide by zero
                if (stdev != 0)
                {
                    // Determine the appropriate criterion
                    double chau = 0;
                    // 3 - 40 input points
                    if (used_points.size() <= 40)
                    {
                        chau = CHAUVENET_TABLE[used_points.size() - 3];
                    }
                    // 41 - 50 input points
                    else if (used_points.size() < 50)
                    {
                        chau = CHAUVENET_TABLE[38];
                    }
                    // 51 - 100 input points
                    else if (used_points.size() < 100)
                    {
                        chau = CHAUVENET_TABLE[39];
                    }
                    // 101 - 500 input points
                    else if (used_points.size() < 500)
                    {
                        chau = CHAUVENET_TABLE[40];
                    }
                    // > 500 input points
                    else 
                    {
                        chau = CHAUVENET_TABLE[41];
                    }
                    // Check for points to remove based on the Chauvenet criteria
                    point_to_remove = used_points.cend();
                    for (auto point = used_points.cbegin(); point != used_points.cend(); point++)
                    {
                        if ((abs((*point)->template get_value<T>() - avg) / stdev) > chau)
                        {
                            point_to_remove = point;
                            break;
                        }
                    }
                    // If we need to remove a point, do so and redo the calculation
                    if (point_to_remove != used_points.cend())
                    {
                        used_points.erase(point_to_remove);
                        continue;
                    }
                }
                // All points are good
                *this->value = static_cast<double>(avg);
                *this->quality = qual;
                return;
            }
        }
    private:
        /// <summary>
        /// Point who's value is the minimum number of good input points needed
        /// </summary>
        Point* min_good_points = nullptr;
        /// <summary>
        /// List of input points
        /// </summary>
        std::vector<Point*> input_points;
        /// <summary>
        /// Chauvenet criterion table
        /// </summary>
        static constexpr double CHAUVENET_TABLE[] = {
            1.383, // 3 input points
            1.534, // 4
            1.645, // 5
            1.732, // 6
            1.803, // 7
            1.863, // 8
            1.915, // 9
            1.960, // 10
            2.000, // 11
            2.037, // 12
            2.070, // 13
            2.100, // 14
            2.128, // 15
            2.154, // 16
            2.178, // 17
            2.200, // 18
            2.222, // 19
            2.241, // 20
            2.260, // 21
            2.278, // 22
            2.295, // 23
            2.311, // 24
            2.326, // 25
            2.341, // 26
            2.355, // 27
            2.369, // 28
            2.382, // 29
            2.394, // 30
            2.406, // 31
            2.418, // 32
            2.429, // 33
            2.440, // 34
            2.450, // 35
            2.460, // 36
            2.470, // 37
            2.479, // 38
            2.489, // 39
            2.498, // 40
            2.576, // 50
            2.807, // 100
            3.291, // 500
            3.481  // 1000
        };
    };
}
