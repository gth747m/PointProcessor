//
// pch.h
// Header for standard system include files.
//

#pragma once

#ifdef __linux__
#include <pthread.h>
#elif defined _WIN32
#define NOMINMAX
#endif

#include <limits>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// PointProcessorLib System Libraries
#include "NamedMutex.h"
#include "SharedMemory.h"

// Google Test
#ifdef _WIN32
#pragma warning(push)
// Ignore VC++ warnings, since I don't control gtest
#pragma warning(disable: 26495)
#pragma warning(disable: 26812)
#endif
#include "gtest/gtest.h"
#ifdef _WIN32
#pragma warning(pop)
#endif

