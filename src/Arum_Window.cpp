#include "Arum_Window.h"

Arum_Window::Arum_Window(int32_t width, int32_t height, std::string title)
	:
	_width(width),
	_height(height),
	_title(title),
	_windowHandle(0)
{
	WNDCLASSEX windowClass = { };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = Arum_Window::_Arum_Win32HandleMessageState;
	windowClass.hInstance = GetModuleHandle(0);
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = "ARUM_WINDOW";

	// TODO: Error checking here
	RegisterClassEx(&windowClass);

	// Create window handle and adjusting it
	RECT rc = { 0, 0, (LONG)_width, (LONG)_height };

	// TODO: Error checking here
	AdjustWindowRect(&rc, WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX, false);

	// TODO: Error checking here
	_windowHandle = CreateWindow(
		windowClass.lpszClassName,
		_title.c_str(),
		WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,
		nullptr,
		GetModuleHandle(0),
		this);
}

Arum_Window::~Arum_Window()
{}

LRESULT Arum_Window::_Arum_Win32HandleMessageState(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CREATE)
	{
		CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		Arum_Window * pWindowState = reinterpret_cast<Arum_Window*>(pCreate->lpCreateParams);

		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindowState)); // Store the pWindowState pointer in the instance data for the window
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Arum_Window::_Arum_Win32HandleProcess));
		Arum_Window::_Arum_Win32HandleProcess(hwnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT Arum_Window::_Arum_Win32HandleProcess(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void Arum_Window::Show() const
{
	ShowWindow(_windowHandle, SW_SHOW);
}

uint8_t Arum_Window::ProcessMessage()
{
	MSG msg = { };
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
		{
			return 0;
		}

		if (GetAsyncKeyState(VK_ESCAPE))
		{
			return 0;
		}
	}

	return 1;
}

