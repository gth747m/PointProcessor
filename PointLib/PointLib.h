// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the POINT_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// POINTLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef POINT_EXPORTS
#define POINTLIB_API __declspec(dllexport)
#else
#define POINTLIB_API __declspec(dllimport)
#endif

/*
extern POINTLIB_API int nPoint;
POINTLIB_API int fnPoint(void);
*/
