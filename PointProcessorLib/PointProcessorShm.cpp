#include "PointProcessorLib.h"

namespace point_processor
{
    PointProcessorShm::PointProcessorShm()
    {
    }

    std::optional<Point*> PointProcessorShm::get_point_by_id(std::string id)
    {
        std::optional<Point*> point;
        auto key = this->points->find(id.c_str());
        if (key != this->points->end())
        {
            point = key->second;
        }
        return point;
    }
}