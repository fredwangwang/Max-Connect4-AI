#include "game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;

void Game::countScore(int * _gamedata) {
    countScore(gameDataTOgameBoard(_gameData));
}

// this serves its job... but too long
void Game::countScore(int ** _gameBoard) {
    _player1Score = 0;
    _player2Score = 0;

    //check horizontally
    int i;
    for (i = 0; i < 6; i++) {
        //check player 1
        if (_gameBoard[i][0] == 1 && _gameBoard[i][1] == 1 && _gameBoard[i][2] == 1 && _gameBoard[i][3] == 1)
            _player1Score++;
        if (_gameBoard[i][1] == 1 && _gameBoard[i][2] == 1 && _gameBoard[i][3] == 1 && _gameBoard[i][4] == 1)
            _player1Score++;
        if (_gameBoard[i][2] == 1 && _gameBoard[i][3] == 1 && _gameBoard[i][4] == 1 && _gameBoard[i][5] == 1)
            _player1Score++;
        if (_gameBoard[i][3] == 1 && _gameBoard[i][4] == 1 && _gameBoard[i][5] == 1 && _gameBoard[i][6] == 1)
            _player1Score++;
        //check player 2
        if (_gameBoard[i][0] == 2 && _gameBoard[i][1] == 2 && _gameBoard[i][2] == 2 && _gameBoard[i][3] == 2)
            _player2Score++;
        if (_gameBoard[i][1] == 2 && _gameBoard[i][2] == 2 && _gameBoard[i][3] == 2 && _gameBoard[i][4] == 2)
            _player2Score++;
        if (_gameBoard[i][2] == 2 && _gameBoard[i][3] == 2 && _gameBoard[i][4] == 2 && _gameBoard[i][5] == 2)
            _player2Score++;
        if (_gameBoard[i][3] == 2 && _gameBoard[i][4] == 2 && _gameBoard[i][5] == 2 && _gameBoard[i][6] == 2)
            _player2Score++;
    }

    //check vertically
    int j;
    for (j = 0; j < 7; j++) {
        //check player 1
        if (_gameBoard[0][j] == 1 && _gameBoard[1][j] == 1 && _gameBoard[2][j] == 1 && _gameBoard[3][j] == 1)
            _player1Score++;
        if (_gameBoard[1][j] == 1 && _gameBoard[2][j] == 1 && _gameBoard[3][j] == 1 && _gameBoard[4][j] == 1)
            _player1Score++;
        if (_gameBoard[2][j] == 1 && _gameBoard[3][j] == 1 && _gameBoard[4][j] == 1 && _gameBoard[5][j] == 1)
            _player1Score++;
        //check player 2
        if (_gameBoard[0][j] == 2 && _gameBoard[1][j] == 2 && _gameBoard[2][j] == 2 && _gameBoard[3][j] == 2)
            _player2Score++;
        if (_gameBoard[1][j] == 2 && _gameBoard[2][j] == 2 && _gameBoard[3][j] == 2 && _gameBoard[4][j] == 2)
            _player2Score++;
        if (_gameBoard[2][j] == 2 && _gameBoard[3][j] == 2 && _gameBoard[4][j] == 2 && _gameBoard[5][j] == 2)
            _player2Score++;
    }

    //check diagonally

    //check player 1
    if (_gameBoard[2][0] == 1 && _gameBoard[3][1] == 1
        && _gameBoard[4][2] == 1 && _gameBoard[5][3] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[1][0] == 1 && _gameBoard[2][1] == 1
        && _gameBoard[3][2] == 1 && _gameBoard[4][3] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[2][1] == 1 && _gameBoard[3][2] == 1
        && _gameBoard[4][3] == 1 && _gameBoard[5][4] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[0][0] == 1 && _gameBoard[1][1] == 1
        && _gameBoard[2][2] == 1 && _gameBoard[3][3] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[1][1] == 1 && _gameBoard[2][2] == 1
        && _gameBoard[3][3] == 1 && _gameBoard[4][4] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[2][2] == 1 && _gameBoard[3][3] == 1
        && _gameBoard[4][4] == 1 && _gameBoard[5][5] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[0][1] == 1 && _gameBoard[1][2] == 1
        && _gameBoard[2][3] == 1 && _gameBoard[3][4] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[1][2] == 1 && _gameBoard[2][3] == 1
        && _gameBoard[3][4] == 1 && _gameBoard[4][5] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[2][3] == 1 && _gameBoard[3][4] == 1
        && _gameBoard[4][5] == 1 && _gameBoard[5][6] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[0][2] == 1 && _gameBoard[1][3] == 1
        && _gameBoard[2][4] == 1 && _gameBoard[3][5] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[1][3] == 1 && _gameBoard[2][4] == 1
        && _gameBoard[3][5] == 1 && _gameBoard[4][6] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[0][3] == 1 && _gameBoard[1][4] == 1
        && _gameBoard[2][5] == 1 && _gameBoard[3][6] == 1)
    {
        _player1Score++;
    }

    if (_gameBoard[0][3] == 1 && _gameBoard[1][2] == 1
        && _gameBoard[2][1] == 1 && _gameBoard[3][0] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[0][4] == 1 && _gameBoard[1][3] == 1
        && _gameBoard[2][2] == 1 && _gameBoard[3][1] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[1][3] == 1 && _gameBoard[2][2] == 1
        && _gameBoard[3][1] == 1 && _gameBoard[4][0] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[0][5] == 1 && _gameBoard[1][4] == 1
        && _gameBoard[2][3] == 1 && _gameBoard[3][2] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[1][4] == 1 && _gameBoard[2][3] == 1
        && _gameBoard[3][2] == 1 && _gameBoard[4][1] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[2][3] == 1 && _gameBoard[3][2] == 1
        && _gameBoard[4][1] == 1 && _gameBoard[5][0] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[0][6] == 1 && _gameBoard[1][5] == 1
        && _gameBoard[2][4] == 1 && _gameBoard[3][3] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[1][5] == 1 && _gameBoard[2][4] == 1
        && _gameBoard[3][3] == 1 && _gameBoard[4][2] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[2][4] == 1 && _gameBoard[3][3] == 1
        && _gameBoard[4][2] == 1 && _gameBoard[5][1] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[1][6] == 1 && _gameBoard[2][5] == 1
        && _gameBoard[3][4] == 1 && _gameBoard[4][3] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[2][5] == 1 && _gameBoard[3][4] == 1
        && _gameBoard[4][3] == 1 && _gameBoard[5][2] == 1)
    {
        _player1Score++;
    }
    if (_gameBoard[2][6] == 1 && _gameBoard[3][5] == 1
        && _gameBoard[4][4] == 1 && _gameBoard[5][3] == 1)
    {
        _player1Score++;
    }

    //check player 2
    if (_gameBoard[2][0] == 2 && _gameBoard[3][1] == 2
        && _gameBoard[4][2] == 2 && _gameBoard[5][3] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[1][0] == 2 && _gameBoard[2][1] == 2
        && _gameBoard[3][2] == 2 && _gameBoard[4][3] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[2][1] == 2 && _gameBoard[3][2] == 2
        && _gameBoard[4][3] == 2 && _gameBoard[5][4] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[0][0] == 2 && _gameBoard[1][1] == 2
        && _gameBoard[2][2] == 2 && _gameBoard[3][3] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[1][1] == 2 && _gameBoard[2][2] == 2
        && _gameBoard[3][3] == 2 && _gameBoard[4][4] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[2][2] == 2 && _gameBoard[3][3] == 2
        && _gameBoard[4][4] == 2 && _gameBoard[5][5] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[0][1] == 2 && _gameBoard[1][2] == 2
        && _gameBoard[2][3] == 2 && _gameBoard[3][4] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[1][2] == 2 && _gameBoard[2][3] == 2
        && _gameBoard[3][4] == 2 && _gameBoard[4][5] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[2][3] == 2 && _gameBoard[3][4] == 2
        && _gameBoard[4][5] == 2 && _gameBoard[5][6] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[0][2] == 2 && _gameBoard[1][3] == 2
        && _gameBoard[2][4] == 2 && _gameBoard[3][5] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[1][3] == 2 && _gameBoard[2][4] == 2
        && _gameBoard[3][5] == 2 && _gameBoard[4][6] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[0][3] == 2 && _gameBoard[1][4] == 2
        && _gameBoard[2][5] == 2 && _gameBoard[3][6] == 2)
    {
        _player2Score++;
    }

    if (_gameBoard[0][3] == 2 && _gameBoard[1][2] == 2
        && _gameBoard[2][1] == 2 && _gameBoard[3][0] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[0][4] == 2 && _gameBoard[1][3] == 2
        && _gameBoard[2][2] == 2 && _gameBoard[3][1] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[1][3] == 2 && _gameBoard[2][2] == 2
        && _gameBoard[3][1] == 2 && _gameBoard[4][0] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[0][5] == 2 && _gameBoard[1][4] == 2
        && _gameBoard[2][3] == 2 && _gameBoard[3][2] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[1][4] == 2 && _gameBoard[2][3] == 2
        && _gameBoard[3][2] == 2 && _gameBoard[4][1] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[2][3] == 2 && _gameBoard[3][2] == 2
        && _gameBoard[4][1] == 2 && _gameBoard[5][0] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[0][6] == 2 && _gameBoard[1][5] == 2
        && _gameBoard[2][4] == 2 && _gameBoard[3][3] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[1][5] == 2 && _gameBoard[2][4] == 2
        && _gameBoard[3][3] == 2 && _gameBoard[4][2] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[2][4] == 2 && _gameBoard[3][3] == 2
        && _gameBoard[4][2] == 2 && _gameBoard[5][1] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[1][6] == 2 && _gameBoard[2][5] == 2
        && _gameBoard[3][4] == 2 && _gameBoard[4][3] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[2][5] == 2 && _gameBoard[3][4] == 2
        && _gameBoard[4][3] == 2 && _gameBoard[5][2] == 2)
    {
        _player2Score++;
    }
    if (_gameBoard[2][6] == 2 && _gameBoard[3][5] == 2
        && _gameBoard[4][4] == 2 && _gameBoard[5][3] == 2)
    {
        _player2Score++;
    }
}

// verify selected column valid or not
bool Game::isValidColumn(int column, int * gamedata) {
    if (column < 0 || column > 6)
        return false;
    if (gamedata[column] != 0)
        return false;
    return true;
}

// place that player's piece in the requested column
bool Game::playPiece(int column, int * gamedata, int player) {
    if (!isValidColumn(column, gamedata))
        return false;

    for (int i = 5; i >= 0; i--) {
        if (gamedata[i * 7 + column] == 0) {
            gamedata[i * 7 + column] = player;
            return true;
        }
    }
    // never reach, add for safety
    return false;
}

int ** Game::gameDataTOgameBoard(int * gamedata) {
    static int* _gameboard[6];
    _gameboard[0] = &(gamedata[0]);
    _gameboard[1] = &(gamedata[7]);
    _gameboard[2] = &(gamedata[14]);
    _gameboard[3] = &(gamedata[21]);
    _gameboard[4] = &(gamedata[28]);
    _gameboard[5] = &(gamedata[35]);
    return _gameboard;
}

int Game::totalPiece(int * gamedata) {
    int total = 0;
    for (int i = 0; i < 42; ++i)
        if (gamedata[i])
            ++total;
    return total;
}









