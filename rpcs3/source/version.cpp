#include "rpcs3/pch.h"
#include "rpcs3/version.h"
#include "rpcs3/git-version.h"

namespace rpcs3
{
	const utils::version version = utils::version{ 0, 0, 1 }
		.type(utils::version_type::pre_alpha)
		.postfix(RPCS3_GIT_VERSION);
}
