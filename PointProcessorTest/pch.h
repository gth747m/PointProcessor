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
#include "ChauvenetAveragePoint.h"
#include "ExternalPoint.h"
#include "FToCPoint.h"
#include "SelectPoint.h"
#include "SubtractPoint.h"
#include "SumPoint.h"

// Google Test
#include "gtest/gtest.h"

