#include "../source/functions.h"
#include <eps3/dll_export.h>

//emulator
EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorCreate(Eps3Emulator *handle)
{
	return _eps3EmulatorCreate(handle);
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorDestroy(Eps3Emulator handle)
{
	return _eps3EmulatorDestroy(handle);
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorAddModule(Eps3Emulator handle, Eps3Module module)
{
	return _eps3EmulatorAddModule(handle, module);
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorLoad(Eps3Emulator handle, Eps3Executable executable)
{
	return _eps3EmulatorLoad(handle, executable);
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorStart(Eps3Emulator handle)
{
	return _eps3EmulatorStart(handle);
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorStop(Eps3Emulator handle)
{
	return _eps3EmulatorStop(handle);
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorPause(Eps3Emulator handle)
{
	return _eps3EmulatorPause(handle);
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorOnStateChange(Eps3Emulator handle, Eps3OnStateChangeCallback callback)
{
	return _eps3EmulatorOnStateChange(handle, callback);
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorGetThreadsList(Eps3Emulator handle, Eps3Thread *threadsList, int maxCount, int *count)
{
	return _eps3EmulatorGetThreadsList(handle, threadsList, maxCount, count);
}

//executable
EPS3API_DLL_EXPORT Eps3ErrorCode eps3ExecutableLoad(Eps3Executable *executable, const char *path)
{
	return _eps3ExecutableLoad(executable, path);
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3ExecutableUnload(Eps3Executable executable)
{
	return _eps3ExecutableUnload(executable);
}

EPS3API_DLL_EXPORT Eps3ExecutableType eps3ExecutableGetType(Eps3Executable executable)
{
	return _eps3ExecutableGetType(executable);
}

//module
EPS3API_DLL_EXPORT Eps3ErrorCode eps3ModuleLoad(Eps3Module *module, const char *path)
{
	return _eps3ModuleLoad(module, path);
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3ModuleUnload(Eps3Module module)
{
	return _eps3ModuleUnload(module);
}

EPS3API_DLL_EXPORT const char *eps3ModuleGetName(Eps3Module module)
{
	return _eps3ModuleGetName(module);
}

EPS3API_DLL_EXPORT Eps3Version eps3ModuleGetVersion(Eps3Module module)
{
	return _eps3ModuleGetVersion(module);
}

EPS3API_DLL_EXPORT Eps3ModuleType eps3ModuleGetType(Eps3Module module)
{
	return _eps3ModuleGetType(module);
}

//thread
EPS3API_DLL_EXPORT Eps3ErrorCode eps3ThreadGetInfo(Eps3Thread thread, Eps3ThreadInfo *info)
{
	return _eps3ThreadGetInfo(thread, info);
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3ThreadGetRegister(Eps3Thread thread, int type, int index, void **destRegister)
{
	return _eps3ThreadGetRegister(thread, type, index, destRegister);
}

