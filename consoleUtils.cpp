#include <iostream>
#include "consoleUtils.h"
using namespace std;

void clearConsole() {
	cout << "\033[2J";
}

void consoleCursorToHome() {
	cout << "\033[0;0H";
}

void disableSync() {
	std::ios_base::sync_with_stdio(false);
}

void hideConsoleCursor() {
	std::cout << "\033[?25l";
}

void showConsoleCursor() {
	std::cout << "\033[?25h";
}