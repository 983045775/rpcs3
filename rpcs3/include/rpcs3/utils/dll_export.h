#pragma once

#ifdef _MSC_VER
	#define UTILS_DLL_EXPORT __declspec(dllexport)
#else
	#define UTILS_DLL_C_EXPORT __attribute__((visibility("default")))
#endif

#define UTILS_DLL_C_EXPORT extern "C" UTILS_DLL_EXPORT
