#pragma once
#include <string>

namespace rpcs3
{
	struct game_info
	{
		std::string root;
		std::string title;
		std::string title_id;
		std::uint32_t sdk_version;

		static const game_info& current();
		static void set_current(const game_info &info);
	};
}
