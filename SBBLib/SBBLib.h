#pragma once

#include <chrono>
#include <cstdint>
#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <new>
#include <sstream>
#include <stdlib.h>
#include <string>
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

#include "NamedMutex.h"
#include "SharedMemory.h"
#include "ShmPool.h"
#include "ShmAllocator.h"
#include "ShmTypes.h"
