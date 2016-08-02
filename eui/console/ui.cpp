#include "ui.h"
#include <Windows.h>

#pragma comment(lib, "OpenGL32.lib")

namespace ui
{
	static LRESULT __stdcall WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		default:
			return DefWindowProc(hwnd, msg, wp, lp);
		}
	}

	window::window(utils::string_ref title, int width, int height)
	{
		WNDCLASSEXA wndclass =
		{
			sizeof(WNDCLASSEXA),
			CS_DBLCLKS,
			WindowProcedure,
			0, 0,
			GetModuleHandle(nullptr),
			LoadIcon(nullptr, IDI_APPLICATION),
			LoadCursor(nullptr, IDC_ARROW),
			HBRUSH(COLOR_WINDOW + 1),
			0,
			"UiClass",
			LoadIcon(0,IDI_APPLICATION)
		};

		RegisterClassExA(&wndclass);

		m_handle = CreateWindowA("UiClass", title.to_string().c_str(), WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			width, height, nullptr, nullptr, GetModuleHandleA(nullptr), nullptr);
	}

	window::~window()
	{
		DestroyWindow((HWND)native_handle());
		UnregisterClassA("UiClass", GetModuleHandleA(nullptr));
	}

	void window::show() const
	{
		ShowWindow((HWND)native_handle(), SW_SHOWNORMAL);
	}

	bool window::process_message() const
	{
		MSG msg;
		if (PeekMessage(&msg, (HWND)native_handle(), 0, 0, 1));
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			return false;
		}

		return false;
	}

	void *window::native_handle() const
	{
		return m_handle;
	}

	dc::dc(const class window& window_)
		: m_handle(GetDC((HWND)window_.native_handle()))
		, m_window(&window_)
	{
	}

	dc::dc(dc &&rhs)
		: m_handle(std::exchange(rhs.m_handle, nullptr))
		, m_window(rhs.m_window)
	{
	}

	dc::~dc()
	{
		if (m_handle)
		{
			ReleaseDC((HWND)m_window->native_handle(), (HDC)m_handle);
			m_handle = nullptr;
		}
	}

	void *dc::native_handle() const
	{
		return m_handle;
	}

	const window *dc::window() const
	{
		return m_window;
	}

	context::context(dc &&dc_) : m_dc(std::move(dc_))
	{
		const PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
			PFD_TYPE_RGBA,
			32,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,
			8,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		int pixel_format = ChoosePixelFormat((HDC)m_dc.native_handle(), &pfd);
		SetPixelFormat((HDC)m_dc.native_handle(), pixel_format, &pfd);

		m_handle = wglCreateContext((HDC)m_dc.native_handle());
	}

	context::~context()
	{
		if (m_handle)
		{
			wglDeleteContext((HGLRC)m_handle);
			m_handle = nullptr;
		}
	}

	void context::set_current() const
	{
		wglMakeCurrent((HDC)m_dc.native_handle(), (HGLRC)native_handle());
	}

	void *context::get_function(utils::string_ref name) const
	{
		return wglGetProcAddress(name.to_string().c_str());
	}

	void *context::native_handle() const
	{
		return m_handle;
	}
}

