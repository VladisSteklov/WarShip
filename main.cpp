#include "Game.h"
#include "Menu.h"
#include <Windows.h>


void hideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	hideConsole();
	Menu menu;
	return 0;
}