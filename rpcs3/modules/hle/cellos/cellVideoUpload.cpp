#include "stdafx.h"
#include "Cell/PPUModule.h"

logs::channel cellVideoUpload("cellVideoUpload", logs::level::notice);

s32 cellVideoUploadInitialize()
{
	throw EXCEPTION("");
}

DECLARE(ppu_module_manager::cellVideoUpload)("cellVideoUpload", []()
{
	REG_FUNC(cellVideoUpload, cellVideoUploadInitialize);
});
