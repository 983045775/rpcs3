#pragma once
#include <list>
#include <functional>
#include "event.h"

namespace utils
{
	void event::operator()() const
	{
		for (const auto& entry : m_entries)
		{
			entry();
		}
	}

	event::iterator event::bind(function function_)
	{
		m_entries.push_back(function_);

		auto end = m_entries.end();

		return --end;
	}

	void event::unbind(iterator it)
	{
		m_entries.erase(it);
	}

	event::iterator event::operator +=(function function_)
	{
		return bind(function_);
	}

	void event::operator -=(iterator it)
	{
		unbind(it);
	}

	event_binder::binder::binder(event_binder& event_binder_, event& event_)
		: m_event_binder(event_binder_)
		, m_event(event_)
	{
	}

	event_binder::binder& event_binder::binder::operator +=(const event::function &function_)
	{
		bind(function_);
		return *this;
	}

	event::iterator event_binder::binder::bind(event::function function_) const
	{
		return m_event_binder.bind(m_event, function_);
	}

	event::iterator event_binder::bind(event& event_, event::function function)
	{
		auto result = event_.bind(function);

		m_binded_events.push_back(result);

		return result;
	}

	event_binder::binder event_binder::operator()(event& event_)
	{
		return{ *this, event_ };
	}
}
