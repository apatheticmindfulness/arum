#pragma once

#include <cstdint>
#include <string>
#include "AR_WinLib.h"

struct Arum_Window
{
public:
	Arum_Window() = default;
	Arum_Window(int32_t width, int32_t height, std::string title);
	Arum_Window(const Arum_Window&) = delete;
	~Arum_Window();
	void Show() const;
	uint8_t ProcessMessage();

private:
	static LRESULT CALLBACK _Arum_Win32HandleMessageState(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK _Arum_Win32HandleProcess(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


private:
	int32_t _width;
	int32_t _height;
	std::string _title;
	HWND _windowHandle;
};