#include "game.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// print out the board to screen
void Game::printGameBoard() {
    int num;
    cout << "  1 2 3 4 5 6 7" << endl;
    cout << " -----------------" << endl;
    for (int i = 0; i < 6; i++) {
        cout << " |";
        for (int j = 0; j < 7; j++) {
            num = _gameBoard[i][j];
            if (num == 0) cout << " ";
            else if (num == 1) cout << "O";
            else cout << "X";
            cout << "|";
        }
        cout << endl;
    }
    cout << " -----------------" << endl;
}

// write the board to file
void Game::printGameBoardToFile(const char *outfilename) {
    if (outfilename == NULL) {
        cerr << "No output file name specified" << endl;
        exit(EXIT_FAILURE);
    }

    ofstream fout(outfilename);
    if (!fout) {
        cerr << "Error opening output file" << endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++)
            fout << _gameBoard[i][j];
        fout << endl;
    }
    fout << _currentTurn;
    fout.close();
}

void Game::printPlayerScore() {
    countScore(_gameBoard);
    cout << "Score: Player 1 = " << _player1Score << ", Player 2 = " << _player2Score << endl;
}

// read the board configuration from the input file
// if the input file doesn't exist, just start with empty board
// No error
void Game::readInputFile() {
    _pieceCount = 0;
    ifstream fin(_infilename);
    if (!fin)
        return;

    string oneline;
    for (int i = 0; i < 6; ++i) {
        getline(fin, oneline);
        for (int j = 0; j < 7; ++j) {
            _gameBoard[i][j] = (int) oneline[j] - ASCII_0;
            if (_gameBoard[i][j])
                ++_pieceCount;
        }
    }

    fin >> _currentTurn;
    fin.close();
}
