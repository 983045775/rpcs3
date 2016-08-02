#pragma once
#include <utils/event_def.h>
#include <utils/state_machine.h>
#include <functional>

namespace rpcs3
{
	enum class emulator_state
	{
		idle,
		runnable,
		onproc,
		sleep,
		stop,
		zombie,
		dead
	};

	extern utils::state_machine<emulator_state> state_machine;
	extern utils::event on_start;
	extern utils::event on_stop;
	extern utils::event on_resume;
	extern utils::event on_pause;

	//TODO: error codes
	bool create();
	void destroy();

	void start();
	void stop();
	void pause();

	void loop(std::function<void()> callback);
	void loop_until(std::function<bool()> condition, std::function<void()> callback);
	void wait_until(std::function<bool()> condition);

	const char *name();
	void get_version_number(uint32_t *major, uint32_t *minor, uint32_t *build);
}
