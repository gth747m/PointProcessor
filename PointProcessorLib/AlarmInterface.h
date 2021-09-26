#pragma once

#include "Point.h"

namespace point_processor
{
    template<typename T>
    class AlarmedInterface
    {
        public:
            /// <summary>
            /// 
            /// </summary>
            virtual void pre_calc() = deleted;
            virtual void post_calc() = deleted;
        protected:
        private:
            T prev_value;
    };
}