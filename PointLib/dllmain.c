#ifdef __linux__
#    include <semaphore.h>
#elif defined _WIN32
#    define WIN32_LEAN_AND_MEAN
#    include <Windows.h>
#endif

#include <assert.h>

#include "PointLib/Constants.h"
#include "PointLib/Data.h"
#include "PointLib/PointLib.h"
#include "PointLib/System/SharedMemory.h"

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD   ul_reason_for_call,
    LPVOID  lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        shared_memory_get(&shm, SHARED_MEM_NAME, sizeof(Data));
        data = shm.memory;
        assert(data != NULL);
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        shared_memory_close(&shm);
        break;
    }
    return TRUE;
}

