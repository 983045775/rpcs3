#ifndef _EPS3API_SOUTHBOUND_EXECUTABLE_API_
#define _EPS3API_SOUTHBOUND_EXECUTABLE_API_

#include "eps3/types.h"

#ifdef __cplusplus
extern "C"
{
#endif

Eps3ErrorCode eps3ExecutableLoadImpl(Eps3Executable *executable, const char *path);
Eps3ErrorCode eps3ExecutableUnloadImpl(Eps3Executable executable);
Eps3ErrorCode eps3ExecutableGetTypeImpl(Eps3Executable executable);

#ifdef __cplusplus
}
#endif

#endif /* _EPS3API_SOUTHBOUND_EXECUTABLE_API_ */
