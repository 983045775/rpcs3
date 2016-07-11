#ifndef _EPS3API_DLL_EXPORT_H_
#define _EPS3API_DLL_EXPORT_H_

#ifdef _MSC_VER
	#define EPS3API_DLL_EXPORT_IMPL __declspec(dllexport)
#else
	#define EPS3API_DLL_EXPORT_IMPL __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
#define EPS3API_DLL_EXPORT extern "C" EPS3API_DLL_EXPORT_IMPL
#else
#define EPS3API_DLL_EXPORT EPS3API_DLL_EXPORT_IMPL
#endif

#endif /* _EPS3API_DLL_EXPORT_H_ */
