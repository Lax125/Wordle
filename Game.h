#pragma once
#include <vector>
#include <string>
#include <ostream>
#include <iostream>
#include "Keyboard.h"
#include "Color.h"
using namespace std;

class Game {
private:
	vector<string> guesses;
	vector<vector<Color>> tileColors;
	const string word;
	Keyboard keyboard;

public:
	const unsigned int wordLength;
	const unsigned int maxGuesses;
	unsigned int guessCount = 0;

	Game(string, unsigned int);
	Game() = delete;

	bool confirmGuess(string);
	void printGame(string);
};

