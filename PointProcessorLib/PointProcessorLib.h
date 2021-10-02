#pragma once

#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#ifdef _WIN32
#    define WIN32_LEAN_AND_MEAN
#    include <Windows.h>
#endif

// Base Point Definitions
#include "Frequency.h"
#include "Quality.h"
#include "Point.h"

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
