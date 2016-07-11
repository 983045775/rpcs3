#include "functions.h"
#include "eps3/enums.h"
#include "eps3/module-api.h"

Eps3ErrorCode _eps3ModuleLoad(Eps3Module *module, const char *path)
{
	if (!path)
	{
		return eps3ErrorBadArgument;
	}

	return eps3ErrorNotImplemented;
	//return eps3ModuleLoadImpl(module, path);
}

Eps3ErrorCode _eps3ModuleUnload(Eps3Module module)
{
	return eps3ErrorNotImplemented;
	//return eps3ModuleUnloadImpl(module);
}

const char *_eps3ModuleGetName(Eps3Module module)
{
	return "";
	//return eps3ModuleGetNameImpl(module);
}

Eps3Version _eps3ModuleGetVersion(Eps3Module module)
{
	Eps3Version result = { .major = 0, .minor = 0, .number = 0 };
	return result;
	//return eps3ModuleGetVersionImpl(module);
}

Eps3ModuleType _eps3ModuleGetType(Eps3Module module)
{
	return eps3ModuleTypeInvalid;
	//return eps3ModuleGetTypeImpl(module);
}
