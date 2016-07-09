#include "eps3/module.h"
#include "eps3/enums.h"
#include "eps3/dll_export.h"

Eps3ErrorCode eps3ModuleLoad(Eps3Module *module, const char *path)
{
	return eps3ErrorNotImplemented;
}

Eps3ErrorCode eps3ModuleUnload(Eps3Module module)
{
	return eps3ErrorNotImplemented;
}

const char *eps3ModuleGetName(Eps3Module module)
{
	return NULL;
}

Eps3Version eps3ModuleGetVersion(Eps3Module module)
{
	Eps3Version result = { .major = 0,.minor = 0,.number = 0 };
	return result;
}

Eps3ModuleType eps3ModuleGetType(Eps3Module module)
{
	return eps3ErrorNotImplemented;
}
