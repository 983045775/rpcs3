#include "eps3/emulator.h"
#include "eps3/enums.h"
#include "eps3/southbound-emulator-api.h"
#include "eps3/executable.h"

Eps3ErrorCode eps3EmulatorCreate(Eps3Emulator *handle)
{
	return eps3EmulatorCreateImpl(handle);
}

Eps3ErrorCode eps3EmulatorDestroy(Eps3Emulator handle)
{
	return eps3EmulatorDestroyImpl(handle);
}

Eps3ErrorCode eps3EmulatorAddModule(Eps3Emulator handle, Eps3Module module)
{
	if (!module)
	{
		return eps3ErrorBadArgument;
	}

	return eps3EmulatorAddModuleImpl(handle, module);
}

Eps3ErrorCode eps3EmulatorLoad(Eps3Emulator handle, Eps3Executable executable)
{
	if (!executable || eps3ExecutableGetType(executable) == eps3ExecutableTypeUnknown)
	{
		return eps3ErrorBadArgument;
	}

	return eps3EmulatorLoadImpl(handle, executable);
}

Eps3ErrorCode eps3EmulatorStart(Eps3Emulator handle)
{
	return eps3EmulatorStartImpl(handle);
}

Eps3ErrorCode eps3EmulatorStop(Eps3Emulator handle)
{
	return eps3EmulatorStopImpl(handle);
}

Eps3ErrorCode eps3EmulatorPause(Eps3Emulator handle)
{
	return eps3EmulatorPauseImpl(handle);
}

Eps3ErrorCode eps3EmulatorOnStateChange(Eps3Emulator handle, Eps3OnStateChangeCallback callback)
{
	return eps3EmulatorOnStateChangeImpl(handle, callback);
}

Eps3ErrorCode eps3EmulatorGetThreadsList(Eps3Emulator handle, Eps3Thread *threadsList, int maxCount, int *count)
{
	if (maxCount < 0)
	{
		return eps3ErrorInvalidValue;
	}

	if (!threadsList || !count)
	{
		return eps3ErrorBadArgument;
	}

	return eps3EmulatorGetThreadsListImpl(handle, threadsList, maxCount, count);
}
