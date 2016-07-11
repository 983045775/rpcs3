#pragma once
#include <list>
#include <functional>

namespace utils
{
	class event
	{
	public:
		using iterator = std::list<std::function<void()>>::iterator;
		using const_iterator = std::list<std::function<void()>>::const_iterator;
		using function = std::function<void()>;

	private:
		std::list<function> m_entries;

	public:
		void operator()() const;

		iterator bind(function function_);
		void unbind(iterator it);

		iterator operator +=(function function_);
		void operator -=(iterator it);
	};

	class event_binder
	{
		std::list<event::iterator> m_binded_events;

		class binder
		{
			event_binder& m_event_binder;
			event& m_event;

		public:
			binder(event_binder& event_binder_, event& event_)
				: m_event_binder(event_binder_)
				, m_event(event_)
			{
			}

			binder& operator +=(const event::function &function_)
			{
				bind(function_);
				return *this;
			}

			event::iterator bind(event::function function_)
			{
				return m_event_binder.bind(m_event, function_);
			}
		};

	public:
		event::iterator bind(event& event_, event::function function)
		{
			event::iterator result = event_.bind(function);

			m_binded_events.push_back(result);

			return result;
		}

		binder operator()(event& event_)
		{
			return{ *this, event_ };
		}
	};
}
