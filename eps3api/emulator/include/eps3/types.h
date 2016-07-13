#ifndef _EPS3API_TYPES_
#define _EPS3API_TYPES_

#include <stdint.h>

typedef enum Eps3ErrorCode_e Eps3ErrorCode;
typedef enum Eps3State_e Eps3State;
typedef enum Eps3ModuleType_e Eps3ModuleType;
typedef enum Eps3ThreadType_e Eps3ThreadType;
typedef enum Eps3ExecutableType_e Eps3ExecutableType;

typedef struct Eps3Executable_s *Eps3Executable;
typedef struct Eps3Module_s *Eps3Module;
typedef struct Eps3Thread_s *Eps3Thread;
typedef void(*Eps3OnStateChangeCallback)(Eps3State newState);

#pragma pack(push, 8)
typedef struct
{
	Eps3ThreadType type;
	Eps3State state;
	uint32_t id;
	char name[64];

	/*TODO*/
} Eps3ThreadInfo;

typedef struct
{
	uint32_t major;
	uint32_t minor;
	uint32_t number;
} Eps3Version;
#pragma pack(pop)

#endif /*_EPS3API_TYPES_ */
