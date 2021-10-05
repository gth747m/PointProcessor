#pragma once

#include <chrono>
#include <cmath>
#include <cstdint>
#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <new>
#include <optional>
#include <ostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <utility>
#include <vector>

#ifdef __linux__
#    include <errno.h>
#    include <fcntl.h>
#    include <limits.h>
#    include <stdlib.h>
#    include <string.h>
#    include <sys/ipc.h>
#    include <sys/mman.h>
#    include <sys/sem.h>
#    include <sys/stat.h>
#    include <sys/types.h>
#    include <unistd.h>
#elif defined _WIN32
#    define WIN32_LEAN_AND_MEAN
#    include <Windows.h>
#endif

// Libraries
#include "SharedMemory.h"
#include "NamedMutex.h"
#include "ShmPool.h"
#include "ShmAllocator.h"
#include "ShmTypes.h"

// Base Point Definitions
#include "Frequency.h"
#include "Quality.h"
#include "PointType.h"
#include "Point.h"

// Process Shared Memory
#include "PointProcessorShm.h"

// Point Types
#include "AveragePoint.h"
#include "ChauvenetAveragePoint.h"
#include "CounterPoint.h"
#include "CToFPoint.h"
#include "DigitalFilterPoint.h"
#include "DividePoint.h"
#include "EqualSelectPoint.h"
#include "ExternalPoint.h"
#include "FToCPoint.h"
#include "GreaterThanEqualSelectPoint.h"
#include "GreaterThanSelectPoint.h"
#include "MultiplyPoint.h"
#include "PolynomialPoint.h"
#include "PowerPoint.h"
#include "SelectPoint.h"
#include "SubtractPoint.h"
#include "SumPoint.h"

