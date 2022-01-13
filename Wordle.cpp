#include "Game.h"

int main() {
	Game game("PANDA", 8);
	while (game.guessCount < game.maxGuesses) {
		game.printGame("");
		string nextGuess;
		cin >> nextGuess;
		if (nextGuess.length() == game.wordLength) {
			bool won = game.confirmGuess(nextGuess);
			if (won) {
				game.printGame("");
				cout << "You winner!";
				return EXIT_SUCCESS;
			}
		}
	}
	game.printGame("");
	std::cout << "You loser...";
}