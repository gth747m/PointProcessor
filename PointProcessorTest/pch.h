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
#include "DigitalFilterPoint.h"
#include "ExternalPoint.h"
#include "FToCPoint.h"
#include "PolynomialPoint.h"
#include "SelectPoint.h"
#include "SubtractPoint.h"
#include "SumPoint.h"

// Google Test
#if defined _WIN32
#pragma warning(push)
#pragma warning(disable: 26495)
#pragma warning(disable: 26812)
#endif
#include "gtest/gtest.h"
#if defined _WIN32
#pragma warning(pop)
#endif

