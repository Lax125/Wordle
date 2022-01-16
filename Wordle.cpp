
#include <conio.h>
#include <iostream>
#include <fstream>
#include "Game.h"
#include "consoleUtils.h"
#include "randUtils.h"

int main() {
	const unsigned int desiredWordLength = 5;
	ifstream dictionaryFile("dictionary.txt");
	if (!dictionaryFile.is_open()) {
		cerr << "Missing dictionary.txt!" << endl;
		return EXIT_FAILURE;
	}
	string word;
	vector<string> validWords;
	while (getline(dictionaryFile, word)) {
		if (word.length() == desiredWordLength) validWords.push_back(word);
	}
	string secretWord = *select_randomly(validWords.begin(), validWords.end());
	Game game(secretWord, 6);
	string nextGuess;
	bool validGuess = false;

	hideConsoleCursor();
	clearConsole();

	while (game.guessCount < game.maxGuesses) {
		consoleCursorToHome();
		game.printGame(nextGuess);
		if (nextGuess.length() == game.wordLength && !validGuess) {
			cout << nextGuess << " is not a valid word." << endl;
		}
		else {
			for (unsigned int i = 0; i < 21 + game.wordLength; i++) cout << ' ';
			cout << endl;
		}
		int key = _getch();
		if (key == 3 || key == 27) break;
		else if (key >= 97 && key < 123 && nextGuess.length() < game.wordLength) {
			nextGuess += (char)(key - 32);
			if (nextGuess.length() == game.wordLength) {
				validGuess = find(validWords.begin(), validWords.end(), nextGuess) != validWords.end();
			}
			continue;
		}
		else if (key == 8 && nextGuess.length() > 0) {
			nextGuess.pop_back();
		}
		else if (key == 13 && nextGuess.length() == game.wordLength) {
			if (game.confirmGuess(nextGuess)) {
				consoleCursorToHome();
				game.printGame("");
				cout << "You guessed the secret word, " << secretWord << "! You win!" << endl;
				showConsoleCursor();
				return EXIT_SUCCESS;
			}
			nextGuess.clear();
		}
	}

	consoleCursorToHome();
	game.printGame(nextGuess);
	std::cout << "You lost. The word was " << secretWord << '.';
	showConsoleCursor();
	return EXIT_SUCCESS;
}
