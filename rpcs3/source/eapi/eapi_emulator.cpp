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
	rpcs3::start();
	return eps3ErrorOk;
}

Eps3ErrorCode eps3EmulatorStopImpl()
{
	rpcs3::stop();
	return eps3ErrorOk;
}

Eps3ErrorCode eps3EmulatorPauseImpl()
{
	rpcs3::pause();
	return eps3ErrorOk;
}

Eps3ErrorCode eps3EmulatorOnStateChangeImpl(Eps3OnStateChangeCallback callback)
{
	rpcs3::state_machine.on_change += [&, callback] { callback(static_cast<Eps3State>(rpcs3::state_machine.state())); };
	return eps3ErrorOk;
}

Eps3ErrorCode eps3EmulatorGetThreadsListImpl(Eps3Thread *threadsList, int maxCount, int *count)
{
	return eps3ErrorNotImplemented;
}
