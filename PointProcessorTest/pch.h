//
// pch.h
// Header for standard system include files.
//

#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
#include <pthread.h>
#endif

// PointProcessorLib System Libraries
#include "NamedMutex.h"
#include "SharedMemory.h"

// PointProcessorLib Point Libraries
#include "Point.h"
#include "Quality.h"
#include "Frequency.h"
// PointProcessorLib Points
#include "AveragePoint.h"
#include "CToFPoint.h"
#include "FToCPoint.h"
#include "SumPoint.h"

#include "gtest/gtest.h"

