#include "functions.h"
#include "eps3/enums.h"
#include "eps3/executable-api.h"

Eps3ErrorCode _eps3ExecutableLoad(Eps3Executable *executable, const char *path)
{
	if (!path)
	{
		return eps3ErrorBadArgument;
	}

	return eps3ExecutableLoadImpl(executable, path);
}

Eps3ErrorCode _eps3ExecutableUnload(Eps3Executable executable)
{
	return eps3ExecutableUnloadImpl(executable);
}

Eps3ExecutableType _eps3ExecutableGetType(Eps3Executable executable)
{
	return eps3ExecutableGetTypeImpl(executable);
}
