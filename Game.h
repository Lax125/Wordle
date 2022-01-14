#pragma once
#include <vector>
#include <string>
#include <ostream>
#include <iostream>
using namespace std;

enum class Color {gray, orange, green};

class Game {
private:
	vector<string> guesses;
	vector<vector<Color>> tileColors;
	const string word;
	unsigned int letterFrequencies[256] = {};

	void addColorRow(string);

public:
	const unsigned int wordLength;
	const unsigned int maxGuesses;
	unsigned int guessCount = 0;

	Game(string, unsigned int);
	Game() = delete;

	bool confirmGuess(string);
	void printGame(string);
};

