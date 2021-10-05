#pragma once

#include "PointProcessorLib.h"

namespace point_processor
{
    class PointProcessorShm
    {
        PointProcessorShm();
        static PointProcessorShm* get_point_processor_shm();
        std::optional<Point*> get_point_by_id(std::string id);
    private:
        ShmMap<ShmString, Point*>* points;
        ShmMap<ShmString, ShmString>* point_descriptions;
        ShmMap<ShmString, ShmVector<ShmString>>* point_aliases;
    };

}
