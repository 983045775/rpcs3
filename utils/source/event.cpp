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

	event::iterator event::operator +=(function function_)
	{
		m_entries.push_back(function_);

		auto end = m_entries.end();

		return --end;
	}

	void event::operator -=(iterator it)
	{
		m_entries.erase(it);
	}
}
