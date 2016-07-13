#include "rpcs3/pch.h"
#include <eps3/emulator-api.h>
#include <eps3/enums.h>
#include <rpcs3/emulator.h>

Eps3ErrorCode eps3EmulatorCreateImpl()
{
	if (!rpcs3::create())
	{
		return eps3ErrorInternalError;
	}

	return eps3ErrorOk;
}

Eps3ErrorCode eps3EmulatorDestroyImpl()
{
	rpcs3::destroy();
	return eps3ErrorOk;
}

Eps3ErrorCode eps3EmulatorAddModuleImpl(Eps3Module module)
{
	return eps3ErrorNotImplemented;
}

Eps3ErrorCode eps3EmulatorLoadImpl(Eps3Executable executable)
{
	return eps3ErrorNotImplemented;
}

Eps3ErrorCode eps3EmulatorStartImpl()
{
	return eps3ErrorNotImplemented;
}

Eps3ErrorCode eps3EmulatorStopImpl()
{
	return eps3ErrorNotImplemented;
}

Eps3ErrorCode eps3EmulatorPauseImpl()
{
	return eps3ErrorNotImplemented;
}

Eps3ErrorCode eps3EmulatorOnStateChangeImpl(Eps3OnStateChangeCallback callback)
{
	return eps3ErrorNotImplemented;
}

Eps3ErrorCode eps3EmulatorGetThreadsListImpl(Eps3Thread *threadsList, int maxCount, int *count)
{
	return eps3ErrorNotImplemented;
}
