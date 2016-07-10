#include "eps3/module.h"
#include "eps3/enums.h"
#include "eps3/southbound-module-api.h"

Eps3ErrorCode eps3ModuleLoad(Eps3Module *module, const char *path)
{
	if (!path)
	{
		return eps3ErrorBadArgument;
	}

	return eps3ModuleLoadImpl(module, path);
}

Eps3ErrorCode eps3ModuleUnload(Eps3Module module)
{
	return eps3ModuleUnloadImpl(module);
}

const char *eps3ModuleGetName(Eps3Module module)
{
	return eps3ModuleGetNameImpl(module);
}

Eps3Version eps3ModuleGetVersion(Eps3Module module)
{
	return eps3ModuleGetVersionImpl(module);
}

Eps3ModuleType eps3ModuleGetType(Eps3Module module)
{
	return eps3ModuleGetTypeImpl(module);
}
