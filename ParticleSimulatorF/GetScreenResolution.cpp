#include "GetScreenResolution.h"
GetScreenResolution::GetScreenResolution()
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	width = desktop.right;
	height = desktop.bottom;
}
int GetScreenResolution::get_height()
{
	return height;
}
int GetScreenResolution::get_width()
{
	return width;
}