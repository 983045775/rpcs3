#ifndef _EPS3API_EXECUTABLE_
#define _EPS3API_EXECUTABLE_

#include "eps3/types.h"
#include "eps3/dll_export.h"

#ifdef __cplusplus
extern "C"
{
#endif

EPS3API_DLL_EXPORT Eps3ErrorCode eps3ExecutableLoad(Eps3Executable *executable, const char *path);
EPS3API_DLL_EXPORT Eps3ErrorCode eps3ExecutableUnload(Eps3Executable executable);

EPS3API_DLL_EXPORT Eps3ExecutableType eps3ExecutableGetType(Eps3Executable executable);

#ifdef __cplusplus
}
#endif

#endif /* _EPS3API_EXECUTABLE_ */
