#include "rpcs3/pch.h"
#include <mutex>
#include <condition_variable>
#include <rpcs3/cell/thread.h>
#include <rpcs3/system.h>

thread_local cpu_thread* g_tls_current_cpu_thread = nullptr;

extern std::mutex& get_current_thread_mutex();
extern std::condition_variable& get_current_thread_cv();

void cpu_thread::on_task()
{
	state -= cpu_state::exit;

	g_tls_current_cpu_thread = this;

	//Emu.SendDbgCommand(DID_CREATE_THREAD, this);

	std::unique_lock<std::mutex> lock(get_current_thread_mutex());

	// Check thread status
	rpcs3::loop_until([&] { return !(state & cpu_state::exit); }, [&]
	{
		// check stop status
		if (!(state & cpu_state::stop))
		{
			if (lock) lock.unlock();

			try
			{
				cpu_task();
			}
			catch (cpu_state _s)
			{
				state += _s;
			}
			catch (const std::exception&)
			{
				LOG_NOTICE(GENERAL, "\n%s", dump());
				throw;
			}

			state -= cpu_state::ret;
			return;
		}

		if (!lock)
		{
			lock.lock();
			return;
		}

		get_current_thread_cv().wait(lock);
	});
}

void cpu_thread::on_stop()
{
	state += cpu_state::exit;
	(*this)->lock_notify();
}

cpu_thread::~cpu_thread()
{
}

cpu_thread::cpu_thread(cpu_type type)
	: type(type)
{
}

bool cpu_thread::check_status()
{
	std::unique_lock<std::mutex> lock(get_current_thread_mutex(), std::defer_lock);

	rpcs3::wait_until([&]
	{
		if (!state.test(cpu_state_pause) && !state.test(cpu_state::interrupt))
		{
			return false;
		}

		if (!lock)
		{
			lock.lock();
			return true;
		}

		if (!state.test(cpu_state_pause) && state & cpu_state::interrupt && handle_interrupt())
		{
			return true;
		}

		get_current_thread_cv().wait(lock);
		return true;
	});

	if (state & cpu_state::exit)
	{
		return true;
	}

	const auto state_ = state.load();

	if (state_ & make_bitset(cpu_state::ret, cpu_state::stop))
	{
		return true;
	}

	if (state_ & cpu_state::dbg_step)
	{
		state += cpu_state::dbg_pause;
		state -= cpu_state::dbg_step;
	}

	return false;
}
