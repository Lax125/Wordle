#include <string>
#include "Game.h"

constexpr char ESC = 0x1b;

void Game::addColorRow(string guess) {
    vector<unsigned int> nonmatchingLetterIndices;
    vector<Color> colorRow(wordLength, Color::gray);
    unsigned int matchedLetterFrequencies[256] = {};

    for (unsigned int i = 0; i < wordLength; i++) {
        if (guess[i] == word[i]) {
            matchedLetterFrequencies[guess[i]]++;
            colorRow[i] = Color::green;
        }
        else {
            nonmatchingLetterIndices.push_back(i);
        }
    }

    for (auto i : nonmatchingLetterIndices) {
        const char letter = guess[i];
        if (letterFrequencies[letter] - matchedLetterFrequencies[letter] > 0) {
            matchedLetterFrequencies[letter]++;
            colorRow[i] = Color::orange;
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

void setConsoleColors(Color c) {
    cout << ESC << "[48;5;";
    switch (c) {
    case Color::gray:
        cout << "242m"; break;
    case Color::orange:
        cout << "172m"; break;
    case Color::green:
        cout << "40m"; break;
    }

    // Make foreground white
    cout << ESC << "[38;5;15m";
}

void resetConsoleColors() {
    cout << ESC << "[0m";
}

void Game::printGame(string partialGuess) {
    cout << '\xC9';
    for (unsigned int i = 0; i < wordLength; i++) {
        cout << "\xCD\xCD\xCD\xCD\xCD\xCD\xCD";
        if (i != wordLength - 1) cout << '\xCB';
    }
    cout << '\xBB' << endl;
    for (unsigned int i = 0; i < maxGuesses; i++) {
        for (unsigned int j = 0; j < wordLength; j++) {
            cout << '\xBA';
            if (i < guessCount) setConsoleColors(tileColors[i][j]);
            cout << "       ";
            resetConsoleColors();
        }
        cout << '\xBA' << endl;
        for (unsigned int j = 0; j < wordLength; j++) {
            cout << '\xBA';
            if (i < guessCount) {
                setConsoleColors(tileColors[i][j]);
                cout << "   " << guesses[i][j] << "   ";
                resetConsoleColors();
            }
            else if (i == guessCount) {
                cout << "   ";
                if (j == partialGuess.length() || j == wordLength - 1 && partialGuess.length() == wordLength) {
                    cout << ESC << "[4m";
                }
                if (j < partialGuess.length())
                    cout << partialGuess[j];
                else
                    cout << ' ';
                cout << ESC << "[24m";
                cout << "   ";
            }
            else {
                cout << "       ";
            }
        }
        cout << '\xBA' << endl;
        for (unsigned int j = 0; j < wordLength; j++) {
            cout << '\xBA';
            if (i < guessCount) setConsoleColors(tileColors[i][j]);
            cout << "       ";
            resetConsoleColors();
        }
        cout << '\xBA' << endl;
        if (i == maxGuesses - 1) {
            cout << '\xC8';
            for (unsigned int i = 0; i < wordLength; i++) {
                cout << "\xCD\xCD\xCD\xCD\xCD\xCD\xCD";
                if (i != wordLength - 1) cout << '\xCA';
            }
            cout << '\xBC' << endl;
        }
        else {
            cout << '\xCC';
            for (unsigned int i = 0; i < wordLength; i++) {
                cout << "\xCD\xCD\xCD\xCD\xCD\xCD\xCD";
                if (i != wordLength - 1) cout << '\xCE';
            }
            cout << '\xB9' << endl;
        }
    }
}


