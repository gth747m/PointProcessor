#pragma once

#include <cstdint>
#include <vector>

#include "Point.h"

namespace PointProcessor
{
    /// <summary>
    /// Select point
    /// </summary>
    /// <typeparam name="T">Point value type</typeparam>
    template <typename T>
    class SelectPoint :
        public Point
    {
    public:
        /// <summary>
        /// Set the point to be used as the index selector
        /// </summary>
        inline void set_index_point(Point* point)
        {
            this->index_point = point;
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
        /// Select the appropriate point
        /// </summary>
        inline virtual void calc()
        {
            if (index_point == nullptr)
            {
                this->quality = Quality::NOT_CALCULABLE;
                return;
            }
            uint32_t index = (uint32_t)this->index_point->template get_value<int32_t>() - 1;
            if (!IsUsableQuality(index_point->get_quality()))
            {
                this->quality = Quality::NOT_CALCULABLE;
                return;
            }
            if (index > input_points.size())
            {
                this->quality = Quality::NOT_CALCULABLE;
                return;
            }
            auto inp_point = this->input_points.at(index);
            this->value = inp_point->template get_value<double>();
            this->quality = inp_point->get_quality();
        }
    private:
        /// <summary>
        /// Selection point
        /// </summary>
        Point* index_point = nullptr;
        /// <summary>
        /// List of input points
        /// </summary>
        std::vector<Point*> input_points;
    };
}
