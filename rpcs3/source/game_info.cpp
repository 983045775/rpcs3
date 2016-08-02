#include "rpcs3/pch.h"
#include "rpcs3/game_info.h"

namespace rpcs3
{
	static game_info g_game_info;

	const game_info& game_info::current()
	{
		return g_game_info;
	}

	void game_info::set_current(const game_info &info)
	{
		g_game_info = info;
	}
}
