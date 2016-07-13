#include "rpcs3/pch.h"
#include "rpcs3/emulator.h"
#include <utils/event.h>
#include <utils/state_machine.h>

namespace rpcs3
{
	enum class emulator_state
	{
		idle,
		start
		//TODO
	};

	utils::state_machine<emulator_state> state_machine;

	utils::event on_start;
	utils::event on_stop;
	utils::event on_resume;
	utils::event on_pause;

	bool create()
	{
		state_machine.register_state(emulator_state::idle);
		state_machine.register_state(emulator_state::start);

		state_machine.register_state_change(emulator_state::idle, emulator_state::start, on_start);

		//TODO
		return true;
	}

	void destroy()
	{
		printf("rpcs3: Bye!\n");
		//TODO
	}
}
