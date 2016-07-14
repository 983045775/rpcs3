#include "rpcs3/pch.h"
#include "rpcs3/emulator.h"
#include <utils/event.h>
#include <thread>

namespace rpcs3
{
	utils::state_machine<emulator_state> state_machine;

	utils::event on_start;
	utils::event on_stop;
	utils::event on_resume;
	utils::event on_pause;

	bool create()
	{
		state_machine.register_state(emulator_state::idle);
		state_machine.register_state(emulator_state::runnable);
		state_machine.register_state(emulator_state::onproc);
		state_machine.register_state(emulator_state::sleep);
		state_machine.register_state(emulator_state::stop);
		state_machine.register_state(emulator_state::zombie);
		state_machine.register_state(emulator_state::dead);

		state_machine.register_state_change(emulator_state::idle, emulator_state::runnable); //TODO: loader
		state_machine.register_state_change(emulator_state::runnable, emulator_state::onproc, on_start);
		state_machine.register_state_change(emulator_state::onproc, emulator_state::sleep, on_pause);
		state_machine.register_state_change(emulator_state::sleep, emulator_state::onproc, on_resume);

		state_machine.register_state_change(emulator_state::runnable, emulator_state::stop, on_stop);
		state_machine.register_state_change(emulator_state::onproc, emulator_state::stop, on_stop);
		state_machine.register_state_change(emulator_state::sleep, emulator_state::stop, on_stop);
		state_machine.register_state_change(emulator_state::stop, emulator_state::zombie);
		state_machine.register_state_change(emulator_state::zombie, emulator_state::dead);

		//TODO
		return true;
	}

	void destroy()
	{
		printf("rpcs3: Bye!\n");
		//TODO
	}

	void start()
	{
		state_machine.set_state(emulator_state::runnable);
	}

	void stop()
	{
		state_machine.set_state(emulator_state::stop);
	}

	void pause()
	{
		state_machine.set_state(emulator_state::sleep);
	}

	inline bool loop_default_condition()
	{
		return state_machine.state() != emulator_state::stop;
	}

	void loop(std::function<void()> callback)
	{
		while (loop_default_condition())
		{
			callback();
			std::this_thread::yield();
		}
	}

	void loop_until(std::function<void()> callback, std::function<bool()> condition)
	{
		while (loop_default_condition() && condition())
		{
			callback();
			std::this_thread::yield();
		}
	}

	void loop_until(std::function<bool()> condition)
	{
		while (loop_default_condition() && condition())
		{
			std::this_thread::yield();
		}
	}

	const char *name()
	{
		//TODO: rename project?
		return "RPCS3";
	}
}
