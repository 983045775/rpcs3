#ifndef _EPS3API_MODULE_
#define _EPS3API_MODULE_

#include "eps3/types.h"
#include "eps3/dll_export.h"

EPS3API_DLL_EXPORT Eps3ErrorCode eps3ModuleLoad(Eps3Module *module, const char *path);
EPS3API_DLL_EXPORT Eps3ErrorCode eps3ModuleUnload(Eps3Module module);
EPS3API_DLL_EXPORT const char *eps3ModuleGetName(Eps3Module module);
EPS3API_DLL_EXPORT Eps3Version eps3ModuleGetVersion(Eps3Module module);
EPS3API_DLL_EXPORT Eps3ModuleType eps3ModuleGetType(Eps3Module module);

#endif /* _EPS3API_MODULE_ */
