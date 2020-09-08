
#include <assert.h>

#include "PointLib/Constants.h"
#include "PointLib/Data.h"
#include "PointLib/PointLib.h"
#include "PointLib/System/SharedMemory.h"

#ifdef __linux__
__attribute((constructor))
void alloc_dll_shm()
{
    // Create or get a reference to shared memory
    shared_memory_get(&shm, SHARED_MEM_NAME, sizeof(Data));
    data = shm.memory;
    assert(data != NULL);
}

__attribute((destructor))
void dealloc_dll_shm()
{
    shared_memory_close(&shm);
}

#elif defined _WIN32
#    define WIN32_LEAN_AND_MEAN
#    include <Windows.h>
/// <summary>
/// Method run on load/unload of this DLL
/// </summary>
/// <param name="hModule">Handle to DLL module</param>
/// <param name="ul_reason_for_call">Reason for calling function</param>
/// <param name="lpReserved">Reserved</param>
/// <returns></returns>
BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD   ul_reason_for_call,
    LPVOID  lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // Create or get a reference to shared memory
        shared_memory_get(&shm, SHARED_MEM_NAME, sizeof(Data));
        data = shm.memory;
        assert(data != NULL);
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        // Destroy shared memory
        shared_memory_close(&shm);
        break;
    }
    return TRUE;
}
#endif
