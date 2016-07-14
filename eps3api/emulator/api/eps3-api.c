#include "../source/functions.h"
#include <eps3/dll_export.h>


EPS3API_DLL_EXPORT uint32_t eps3GetVersion()
{
	return 1;
}

//emulator
EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorCreate()
{
	return _eps3EmulatorCreate();
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorDestroy()
{
	return _eps3EmulatorDestroy();
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorAddModule(Eps3Module module)
{
	return _eps3EmulatorAddModule(module);
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorLoad(Eps3Executable executable)
{
	return _eps3EmulatorLoad(executable);
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorStart()
{
	return _eps3EmulatorStart();
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorStop()
{
	return _eps3EmulatorStop();
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorPause()
{
	return _eps3EmulatorPause();
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorOnStateChange(Eps3OnStateChangeCallback callback)
{
	return _eps3EmulatorOnStateChange(callback);
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorGetThreadsList(Eps3Thread *threadsList, uint32_t maxCount, uint32_t *count)
{
	return _eps3EmulatorGetThreadsList(threadsList, maxCount, count);
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorGetVersion(uint32_t *major, uint32_t *minor, uint32_t *version)
{
	return _eps3EmulatorGetVersion(major, minor, version);
}

EPS3API_DLL_EXPORT Eps3ErrorCode eps3EmulatorGetVersionString(char *destination, uint32_t limit)
{
	return _eps3EmulatorGetVersionString(destination, limit);
}

EPS3API_DLL_EXPORT const char *eps3EmulatorGetName()
{
	return _eps3EmulatorGetName();
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

