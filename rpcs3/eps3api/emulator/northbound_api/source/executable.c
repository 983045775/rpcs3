#include "eps3/executable.h"
#include "eps3/enums.h"
#include "eps3/southbound-executable-api.h"

Eps3ErrorCode eps3ExecutableLoad(Eps3Executable *executable, const char *path)
{
	if (!path)
	{
		return eps3ErrorBadArgument;
	}

	return eps3ExecutableLoadImpl(executable, path);
}

Eps3ErrorCode eps3ExecutableUnload(Eps3Executable executable)
{
	return eps3ExecutableUnloadImpl(executable);
}

Eps3ExecutableType eps3ExecutableGetType(Eps3Executable executable)
{
	return eps3ExecutableGetTypeImpl(executable);
}
