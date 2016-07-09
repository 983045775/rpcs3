#pragma once
#include <rpcs3/utils/types.h>

struct SaveDataEntry
{
	std::string dirName;
	std::string listParam;
	std::string title;
	std::string subtitle;
	std::string details;
	u64 size;
	s64 atime;
	s64 mtime;
	s64 ctime;
	//void* iconBuf;
	//u32 iconBufSize;
	bool isNew;
};

class SaveDialogBase
{
public:
	virtual ~SaveDialogBase() = default;

	virtual s32 ShowSaveDataList(std::vector<SaveDataEntry>& save_entries, s32 focused, struct CellSaveDataListSet *listSet) = 0;
};
