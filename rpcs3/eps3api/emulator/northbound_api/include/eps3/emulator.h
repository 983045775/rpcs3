#ifndef _EPS3API_EMULATOR_
#define _EPS3API_EMULATOR_

#include "eps3/types.h"
#include "eps3/dll_export.h"

#ifdef __cplusplus
extern "C"
{
#endif

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorCreate(Eps3Emulator *handle);
EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorDestroy(Eps3Emulator handle);

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorAddModule(Eps3Emulator handle, Eps3Module module);

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorLoad(Eps3Emulator handle, Eps3Executable executable);
EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorStart(Eps3Emulator handle);
EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorStop(Eps3Emulator handle);
EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorPause(Eps3Emulator handle);
EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorOnStateChange(Eps3Emulator handle, Eps3OnStateChangeCallback callback);

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorGetThreadsList(Eps3Emulator handle, Eps3Thread *threadsList, int maxCount, int *count);

#ifdef __cplusplus
}
#endif

#endif /* _EPS3API_EMULATOR_ */
