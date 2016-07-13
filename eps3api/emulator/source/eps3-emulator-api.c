#include "functions.h"
#include "eps3/enums.h"
#include "eps3/emulator-api.h"

Eps3ErrorCode _eps3EmulatorCreate()
{
	return eps3EmulatorCreateImpl();
}

Eps3ErrorCode _eps3EmulatorDestroy()
{
	return eps3EmulatorDestroyImpl();
}

Eps3ErrorCode _eps3EmulatorAddModule(Eps3Module module)
{
	if (!module)
	{
		return eps3ErrorBadArgument;
	}

	return eps3EmulatorAddModuleImpl(module);
}

Eps3ErrorCode _eps3EmulatorLoad(Eps3Executable executable)
{
	if (!executable || _eps3ExecutableGetType(executable) == eps3ExecutableTypeUnknown)
	{
		return eps3ErrorBadArgument;
	}

	return eps3EmulatorLoadImpl(executable);
}

Eps3ErrorCode _eps3EmulatorStart()
{
	return eps3EmulatorStartImpl();
}

Eps3ErrorCode _eps3EmulatorStop()
{
	return eps3EmulatorStopImpl();
}

Eps3ErrorCode _eps3EmulatorPause()
{
	return eps3EmulatorPauseImpl();
}

Eps3ErrorCode _eps3EmulatorOnStateChange(Eps3OnStateChangeCallback callback)
{
	return eps3EmulatorOnStateChangeImpl(callback);
}

Eps3ErrorCode _eps3EmulatorGetThreadsList(Eps3Thread *threadsList, int maxCount, int *count)
{
	if (maxCount < 0)
	{
		return eps3ErrorInvalidValue;
	}

	if (!threadsList || !count)
	{
		return eps3ErrorBadArgument;
	}

	return eps3EmulatorGetThreadsListImpl(threadsList, maxCount, count);
}
