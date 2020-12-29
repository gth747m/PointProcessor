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

#include "NamedMutex.h"
#include "SharedMemory.h"

#include "gtest/gtest.h"

