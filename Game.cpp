#include <string>
#include "Game.h"

constexpr char ESC = 0x1b;

Game::Game(string _word, unsigned int _maxGuesses) : 
    word(_word),
    wordLength(_word.length()),
    maxGuesses(_maxGuesses)
{}

bool Game::confirmGuess(string guess) {
    if (guessCount >= maxGuesses) throw "Too many guesses.";
    if (guess.length() != wordLength) throw "Incorrect guess length.";
    guesses.push_back(guess);
    tileColors.push_back(guessColors(guess, word));
    keyboard.visit(guess, word);
    guessCount++;
    return guess == word;
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
    cout << keyboard;
}


