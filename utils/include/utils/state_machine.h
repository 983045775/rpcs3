#pragma once
#include <unordered_map>
#include <atomic>
#include "event.h"

namespace utils
{
	template<typename Type>
	class state_machine
	{
	public:
		using type = Type;

	private:
		struct entry
		{
			std::unordered_map<type, std::function<bool()>> on_switch;
		};

		std::atomic<type> m_current_state;
		std::unordered_map<type, entry> m_states;

	public:
		event on_change;

		void set_default_state(type state)
		{
			register_state(state);
			m_current_state = state;
		}

		void register_state(type state)
		{
			m_states[state];
		}

		void register_state_change(type from_state, type to_state, std::function<bool()> on_switch = nullptr)
		{
			m_states.at(from_state).on_switch[to_state] = on_switch;
		}

		void register_state_change(type from_state, type to_state, std::function<void()> on_switch)
		{
			m_states.at(from_state).on_switch[to_state] = [=] { on_switch(); return true; };
		}

		bool set_state(type state)
		{
			if (m_current_state == state)
			{
				return true;
			}

			const entry& entry_ = m_states.at(m_current_state);
			auto found = entry_.on_switch.find(state);

			if (found == entry_.on_switch.end())
			{
				return false;
			}

			if (const auto &on_switch = found->second)
			{
				if (!on_switch())
				{
					return false;
				}
			}

			m_current_state = state;
			on_change();
			return true;
		}

		type state() const
		{
			return m_current_state;
		}
	};
}
