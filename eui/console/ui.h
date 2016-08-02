#pragma once
#include <utils/string_ref.h>

namespace ui
{
	class window
	{
		void *m_handle;

	public:
		window(utils::string_ref title, int width, int height);
		~window();

		void show() const;
		bool process_message() const;
		void *native_handle() const;
	};

	class dc
	{
		void *m_handle = nullptr;
		const class window *m_window = nullptr;

	public:
		dc() = default;
		dc(const window& window_);
		dc(const dc &) = delete;
		dc(dc &&);
		~dc();

		void *native_handle() const;
		const class window *window() const;
	};

	class context
	{
		void *m_handle;
		dc m_dc;

	public:
		context() = default;
		context(dc &&dc_);
		context(const context &) = delete;
		context(context &&) = default;;
		~context();

		void set_current() const;

		template<typename Type>
		Type *get_function(utils::string_ref name) const
		{
			return (Type *)get_function(utils::string_ref name);
		}

		void *get_function(utils::string_ref name) const;

		void *native_handle() const;
	};
}
