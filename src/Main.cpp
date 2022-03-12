#include "Arum_Window.h"

int WINAPI wWinMain(HINSTANCE hInstance, 
					HINSTANCE hPrevInstance, 
					PWSTR pCmdLine, 
					int nCmdShow)
{
	Arum_Window window(800, 600, "Amazing");

	window.Show();

	while (window.ProcessMessage())
	{

	}

	return 0;
}