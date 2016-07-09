#ifndef _EPS3API_DLL_EXPORT_H_
#define _EPS3API_DLL_EXPORT_H_

#ifdef _MSC_VER
	#define EPS3API_DLL_EXPORT __declspec(dllexport)
#else
	#define EPS3API_DLL_EXPORT __attribute__((visibility("default")))
#endif

#define EPS3API_DLL_CPP_EXPORT extern "C" EPS3API_DLL_EXPORT

#endif /* _EPS3API_DLL_EXPORT_H_ */
