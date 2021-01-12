
#include "ConsoleController.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static HANDLE hConsoleOutput = NULL;

ConsoleController::ConsoleController()
{
	if (hConsoleOutput) return;
	hConsoleOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
}

void ConsoleController::SetCursorPos(int x, int y)
{
	COORD dwCursorPosition;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	::SetConsoleCursorPosition(::hConsoleOutput, dwCursorPosition);
}
