#include "game.h"

using namespace std;

// initialize an empty game board
Game::Game() {
    _gameBoard[0] = &(_gameData[0]);
    _gameBoard[1] = &(_gameData[7]);
    _gameBoard[2] = &(_gameData[14]);
    _gameBoard[3] = &(_gameData[21]);
    _gameBoard[4] = &(_gameData[28]);
    _gameBoard[5] = &(_gameData[35]);

    for (int i = 0; i < 42; i++)
        _gameData[i] = 0;

    _currentTurn = 1;
    _pieceCount = 0;
    _player1Score = 0;
    _player2Score = 0;
    _gamemode = NOTSET;
}
