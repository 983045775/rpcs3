#ifndef _EPS3API_SOUTHBOUND_MODULE_API_
#define _EPS3API_SOUTHBOUND_MODULE_API_

#include "eps3/types.h"

Eps3ErrorCode eps3ModuleLoadImpl(Eps3Module *module, const char *path);
Eps3ErrorCode eps3ModuleUnloadImpl(Eps3Module module);
const char *eps3ModuleGetNameImpl(Eps3Module module);
Eps3Version eps3ModuleGetVersionImpl(Eps3Module module);
Eps3ModuleType eps3ModuleGetTypeImpl(Eps3Module module);

#endif /* _EPS3API_SOUTHBOUND_MODULE_API_ */
