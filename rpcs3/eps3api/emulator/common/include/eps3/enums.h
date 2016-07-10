#ifndef _EPS3API_ENUMS_
#define _EPS3API_ENUMS_

typedef enum Eps3ErrorCode_e
{
	eps3ErrorOk,
	eps3ErrorInvalidValue,
	eps3ErrorNotImplemented,
	eps3ErrorBadArgument
} Eps3ErrorCode;

typedef enum Eps3State_e
{
	eps3StateIdle,
	eps3StateRunnable,
	eps3StateOnproc,
	eps3StateSleep,
	eps3StateStop,
	eps3StateZombie,
	eps3StateDead
} Eps3State;

typedef enum Eps3ModuleType_e
{
	eps3ModuleTypeInvalid,
	eps3ModuleTypeCellPpu,
	eps3ModuleTypeCellSpu,
	eps3ModuleTypeRsx,
	eps3ModuleTypePad,
	eps3ModuleTypeKeyboard,
	eps3ModuleTypeMouse,
	eps3ModuleTypeAudio,
	eps3ModuleTypeHle
} Eps3ModuleType;

typedef enum Eps3ThreadType_e
{
	eps3ThreadTypeInvalid,
	eps3ThreadTypePpu,
	eps3ThreadTypeSpu
} Eps3ThreadType;

typedef enum Eps3ExecutableType_e
{
	eps3ExecutableTypeUnknown,
	eps3ExecutableTypeElf64CellOs,
	eps3ExecutableTypeElf32CellOs
} Eps3ExecutableType;

#endif /*_EPS3API_ENUMS_*/
