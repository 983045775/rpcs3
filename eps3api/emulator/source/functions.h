#include "eps3/types.h"

Eps3ErrorCode _eps3EmulatorCreate();
Eps3ErrorCode _eps3EmulatorDestroy();
Eps3ErrorCode _eps3EmulatorAddModule(Eps3Module module);
Eps3ErrorCode _eps3EmulatorLoad(Eps3Executable executable);
Eps3ErrorCode _eps3EmulatorStart();
Eps3ErrorCode _eps3EmulatorStop();
Eps3ErrorCode _eps3EmulatorPause();
Eps3ErrorCode _eps3EmulatorOnStateChange(Eps3OnStateChangeCallback callback);
Eps3ErrorCode _eps3EmulatorGetThreadsList(Eps3Thread *threadsList, int maxCount, int *count);

//executable
Eps3ErrorCode _eps3ExecutableLoad(Eps3Executable *executable, const char *path);
Eps3ErrorCode _eps3ExecutableUnload(Eps3Executable executable);
Eps3ExecutableType _eps3ExecutableGetType(Eps3Executable executable);

//module
Eps3ErrorCode _eps3ModuleLoad(Eps3Module *module, const char *path);
Eps3ErrorCode _eps3ModuleUnload(Eps3Module module);
const char *_eps3ModuleGetName(Eps3Module module);
Eps3Version _eps3ModuleGetVersion(Eps3Module module);
Eps3ModuleType _eps3ModuleGetType(Eps3Module module);

//thread
Eps3ErrorCode _eps3ThreadGetInfo(Eps3Thread thread, Eps3ThreadInfo *info);
Eps3ErrorCode _eps3ThreadGetRegister(Eps3Thread thread, int type, int index, void **destRegister);
