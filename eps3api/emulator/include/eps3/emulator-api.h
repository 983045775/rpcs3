#ifndef _EPS3API_SOUTHBOUND_EMULATOR_API_
#define _EPS3API_SOUTHBOUND_EMULATOR_API_

#include "eps3/types.h"

#ifdef __cplusplus
extern "C"
{
#endif

Eps3ErrorCode eps3EmulatorCreateImpl();
Eps3ErrorCode eps3EmulatorDestroyImpl();

Eps3ErrorCode eps3EmulatorAddModuleImpl(Eps3Module module);

Eps3ErrorCode eps3EmulatorLoadImpl(Eps3Executable executable);
Eps3ErrorCode eps3EmulatorStartImpl();
Eps3ErrorCode eps3EmulatorStopImpl();
Eps3ErrorCode eps3EmulatorPauseImpl();
Eps3ErrorCode eps3EmulatorOnStateChangeImpl(Eps3OnStateChangeCallback callback);

Eps3ErrorCode eps3EmulatorGetThreadsListImpl(Eps3Thread *threadsList, int maxCount, int *count);

#ifdef __cplusplus
}
#endif

#endif /* _EPS3API_SOUTHBOUND_EMULATOR_API_ */
