#include <string>
#include "Game.h"

void Game::addColorRow(string guess) {
    vector<unsigned int> nonmatchingLetterIndices;
    vector<Color> colorRow(wordLength, red);
    unsigned int matchedLetterFrequencies[256] = {};

    for (unsigned int i = 0; i < wordLength; i++) {
        if (guess[i] == word[i]) {
            matchedLetterFrequencies[guess[i]]++;
            colorRow[i] = green;
        }
        else {
            nonmatchingLetterIndices.push_back(i);
        }
    }

    for (auto i : nonmatchingLetterIndices) {
        const char letter = guess[i];
        if (letterFrequencies[letter] - matchedLetterFrequencies[letter] > 0) {
            matchedLetterFrequencies[letter]++;
            colorRow[i] = yellow;
        }
    }

    tileColors.push_back(colorRow);
}

Game::Game(string _word, unsigned int _maxGuesses) : 
    word(_word),
    wordLength(_word.length()),
    maxGuesses(_maxGuesses)
{
    for (char letter : word) {
        letterFrequencies[letter]++;
    }
}

bool Game::confirmGuess(string guess) {
    if (guessCount >= maxGuesses) throw "Too many guesses.";
    if (guess.length() != wordLength) throw "Incorrect guess length.";
    guesses.push_back(guess);
    addColorRow(guess);
    guessCount++;
    return guess == word;
}

void Game::printGame(string partialGuess) {
    // TODO: replace with fancier graphics
    for (unsigned int i = 0; i < guessCount; i++) {
        for (unsigned int j = 0; j < wordLength; j++) {
            cout << guesses[i][j];
            switch (tileColors[i][j]) {
            case red:
                cout << '.'; break;
            case yellow:
                cout << '?'; break;
            case green:
                cout << '!'; break;
            }
            cout << ' ';
        }
        cout << endl;
    }

    for (unsigned int i = 0; i < maxGuesses - guessCount; i++) {
        for (unsigned int j = 0; j < wordLength; j++) cout << "__ ";
        cout << endl;
    }
}
