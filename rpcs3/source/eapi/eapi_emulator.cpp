#include "rpcs3/pch.h"
#include <eps3/southbound-emulator-api.h>
#include <eps3/enums.h>

Eps3ErrorCode eps3EmulatorCreateImpl(Eps3Emulator *handle)
{
	return eps3ErrorNotImplemented;
}

Eps3ErrorCode eps3EmulatorDestroyImpl(Eps3Emulator handle)
{
	return eps3ErrorNotImplemented;
}

Eps3ErrorCode eps3EmulatorAddModuleImpl(Eps3Emulator handle, Eps3Module module)
{
	return eps3ErrorNotImplemented;
}

Eps3ErrorCode eps3EmulatorLoadImpl(Eps3Emulator handle, Eps3Executable executable)
{
	return eps3ErrorNotImplemented;
}

Eps3ErrorCode eps3EmulatorStartImpl(Eps3Emulator handle)
{
	return eps3ErrorNotImplemented;
}

Eps3ErrorCode eps3EmulatorStopImpl(Eps3Emulator handle)
{
	return eps3ErrorNotImplemented;
}

Eps3ErrorCode eps3EmulatorPauseImpl(Eps3Emulator handle)
{
	return eps3ErrorNotImplemented;
}

Eps3ErrorCode eps3EmulatorOnStateChangeImpl(Eps3Emulator handle, Eps3OnStateChangeCallback callback)
{
	return eps3ErrorNotImplemented;
}

Eps3ErrorCode eps3EmulatorGetThreadsListImpl(Eps3Emulator handle, Eps3Thread *threadsList, int maxCount, int *count)
{
	*count = 0;
	return eps3ErrorNotImplemented;
}
