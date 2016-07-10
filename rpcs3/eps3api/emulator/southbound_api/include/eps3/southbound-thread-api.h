#ifndef _EPS3API_SOUTHBOUND_THREAD_API_
#define _EPS3API_SOUTHBOUND_THREAD_API_

#include "eps3/types.h"

#ifdef __cplusplus
extern "C"
{
#endif

Eps3ErrorCode eps3ThreadGetInfoImpl(Eps3Thread thread, Eps3ThreadInfo *info);
Eps3ErrorCode eps3ThreadGetRegisterImpl(Eps3Thread thread, int type, int index, void **destRegister);

#ifdef __cplusplus
}
#endif

#endif /* _EPS3API_SOUTHBOUND_THREAD_API_ */
