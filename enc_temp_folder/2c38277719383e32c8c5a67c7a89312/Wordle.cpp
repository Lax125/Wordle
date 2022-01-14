#include <windows.h>
#include <conio.h>
#include "Game.h"

void clearConsole() {
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void enableVirtualTerminalProcessing() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD consoleMode;
	GetConsoleMode(hConsole, &consoleMode);
	consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hConsole, consoleMode);
}

void consoleCursorToHome() {
	HANDLE                     hStdOut;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void disableSync() {
	std::ios_base::sync_with_stdio(false);
}

void hideConsoleCursor() {
	std::cout << "\033[?25l";
}

int main() {
	enableVirtualTerminalProcessing();
	hideConsoleCursor();
	clearConsole();

	string secretWord = "PANDA";
	Game game(secretWord, 6);
	string nextGuess;
	while (game.guessCount < game.maxGuesses) {
		consoleCursorToHome();
		game.printGame(nextGuess);
		int key = _getch();
		if (key == 3 || key == 27) break;
		else if (key >= 97 && key < 123 && nextGuess.length() < game.wordLength) {
			nextGuess += (char)(key - 32);
			continue;
		}
		else if (key == 8 && nextGuess.length() > 0) {
			nextGuess.pop_back();
		}
		else if (key == 13 && nextGuess.length() == game.wordLength) {
			if (game.confirmGuess(nextGuess)) {
				game.printGame("");
				cout << "You win!";
				return EXIT_SUCCESS;
			}
			nextGuess.clear();
		}
	}
	consoleCursorToHome();
	game.printGame(nextGuess);
	std::cout << "You lost. The word was " << secretWord << '.';
	return EXIT_SUCCESS;
}