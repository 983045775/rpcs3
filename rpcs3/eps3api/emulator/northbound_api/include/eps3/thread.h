#ifndef _EPS3API_EMULATOR_
#define _EPS3API_EMULATOR_

#include "eps3/dll_export.h"
#include <eps3/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

EPS3API_DLL_EXPORT Eps3ErrorCode eps3ThreadGetInfo(Eps3Thread thread, Eps3ThreadInfo *info);
EPS3API_DLL_EXPORT Eps3ErrorCode eps3ThreadGetRegister(Eps3Thread thread, int type, int index, void **destRegister);

#ifdef __cplusplus
}
#endif

#endif /* _EPS3API_EMULATOR_ */
