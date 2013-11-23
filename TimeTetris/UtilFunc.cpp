#include <Windows.h>
#include <stdio.h>

int __cdecl color_printf(WORD wAttributes, const char* _Format, ...)
{
	enum COLOR
	{
		BLACK,
		BLUE,
		GREEN,
		CYAN,
		RED,
		MAGENTA,
		BROWN,
		LIGHTGRAY,
		DARKGRAY,
		LIGHTBLUE,
		LIGHTGREEN,
		LIGHTCYAN,
		LIGHTRED,
		LIGHTMAGENTA,
		YELLOW,
		WHITE
	};

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	/*
	* First save the current color information
	*/
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	/*
	* Set the new color information
	*/
	SetConsoleTextAttribute ( h, wAttributes);

	va_list argptr;
	va_start(argptr, _Format);
	int ret = vprintf_s(_Format, argptr);
	va_end(argptr);

	/*
	* Restore the original colors
	*/
	SetConsoleTextAttribute ( h, wOldColorAttrs);

	return ret;
}