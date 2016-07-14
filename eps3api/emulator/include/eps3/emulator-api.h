#ifndef _EPS3API_SOUTHBOUND_EMULATOR_API_
#define _EPS3API_SOUTHBOUND_EMULATOR_API_

#include "eps3/types.h"
#include <stdint.h>

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
Eps3ErrorCode eps3EmulatorGetVersionImpl(uint32_t *major, uint32_t *minor, uint32_t *version);
Eps3ErrorCode eps3EmulatorGetVersionStringImpl(char *destination, uint32_t limit);
const char *eps3EmulatorGetNameImpl();

Eps3ErrorCode eps3EmulatorGetThreadsListImpl(Eps3Thread *threadsList, uint32_t maxCount, uint32_t *count);

#ifdef __cplusplus
}
#endif

#endif /* _EPS3API_SOUTHBOUND_EMULATOR_API_ */
