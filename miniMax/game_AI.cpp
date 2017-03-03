#include "game.h"
#include <cstring>
#include <limits.h>

using namespace std;

void freeDynmBoard(int **arrBoard) {
    for (int i = 0; i < 7; ++i)
        if (arrBoard[i] != NULL)
            delete[] arrBoard[i];
    delete[] arrBoard;
}

int findNextRow(int **gameBoard, int col) {
    for (int i = 5; i >= 0; --i)
        if (gameBoard[i][col] == 0)
            return i;
    return -1;
}

// pass back an array of all possible boards
// WITH THE PIECE ALREADY BEEN PLACED
void Game::allValidChildConf(int **arrBoard, int *currBoard, int player) {
    for (int i = 0; i < 7; ++i)
        if (isValidColumn(i, currBoard)) {
            arrBoard[i] = new int[42];
            memcpy(arrBoard[i], currBoard, 42 * sizeof(int));
            playPiece(i, arrBoard[i], player);
        } else arrBoard[i] = NULL;
}

void Game::aiPlayABPruning() {
    int a = INT_MIN, b = INT_MAX;
    int score = (_currentTurn == 1) ? INT_MIN : INT_MAX;
    int col, nextTurn;
    int **arrBoard = new int *[7];

    nextTurn = ((_currentTurn == 1) ? 2 : 1);
    allValidChildConf(arrBoard, _gameData, _currentTurn);
    for (int i = 0; i < 7; ++i) {
        if (arrBoard[i] != NULL) {
            int temp = alphabeta(arrBoard[i], _depthLim - 1, nextTurn, a, b);
            if (_currentTurn == 1) {
                if (score < temp) {
                    score = temp;
                    col = i;
                }
            } else {
                if (score > temp) {
                    score = temp;
                    col = i;
                }
            }
        }
    }

    playPiece(col, _gameData, _currentTurn);

    printf("move %i: Player %i, column %i\n\n\n", _pieceCount, _currentTurn, col + 1);

    freeDynmBoard(arrBoard);
}

int Game::calcThreatScoreOf(int **gameBoard, int col, int row, int player) {
    int total = 0;
    // 1. horizontal
    if (col < 5)
        if (gameBoard[row][col + 1] == player && gameBoard[row][col + 2] == player && gameBoard[row][col + 3] == player)
            total++;
    if (col < 6 && col > 0)
        if (gameBoard[row][col + 1] == player && gameBoard[row][col + 2] == player && gameBoard[row][col - 1] == player)
            total++;
    if (col < 7 && col > 1)
        if (gameBoard[row][col + 1] == player && gameBoard[row][col - 1] == player && gameBoard[row][col - 2] == player)
            total++;
    if (col > 2)
        if (gameBoard[row][col - 3] == player && gameBoard[row][col - 1] == player && gameBoard[row][col - 2] == player)
            total++;

    // 2. vertical 
    if (row < 3)
        if (gameBoard[row + 1][col] == player && gameBoard[row + 2][col] == player && gameBoard[row + 3][col] == player)
            total++;

    // 3. up-left -- down-right diag
    if (row < 3 && col < 5)
        if (gameBoard[row + 1][col + 1] == player && gameBoard[row + 2][col + 2] == player &&
            gameBoard[row + 3][col + 3] == player)
            total++;
    if (row < 4 && row > 0 && col < 6 && col > 0)
        if (gameBoard[row + 1][col + 1] == player && gameBoard[row + 2][col + 2] == player &&
            gameBoard[row - 1][col - 1] == player)
            total++;
    if (row < 5 && row > 1 && col < 7 && col > 1)
        if (gameBoard[row + 1][col + 1] == player && gameBoard[row - 2][col - 2] == player &&
            gameBoard[row - 1][col - 1] == player)
            total++;
    if (row > 2 && col > 2)
        if (gameBoard[row - 3][col - 3] == player && gameBoard[row - 2][col - 2] == player &&
            gameBoard[row - 1][col - 1] == player)
            total++;
    // 4. up-right -- down-left diag
    if (row > 2 && col < 5)
        if (gameBoard[row - 1][col + 1] == player && gameBoard[row - 2][col + 2] == player &&
            gameBoard[row - 3][col + 3] == player)
            total++;
    if (row < 5 && row > 1 && col < 6 && col > 0)
        if (gameBoard[row + 1][col - 1] == player && gameBoard[row - 2][col + 2] == player &&
            gameBoard[row - 1][col + 1] == player)
            total++;
    if (row < 4 && row > 0 && col < 7 && col > 1)
        if (gameBoard[row - 1][col + 1] == player && gameBoard[row + 2][col - 2] == player &&
            gameBoard[row + 1][col - 1] == player)
            total++;
    if (row < 3 && col > 2)
        if (gameBoard[row + 3][col - 3] == player && gameBoard[row + 2][col - 2] == player &&
            gameBoard[row + 1][col - 1] == player)
            total++;

    return total;
}

int Game::calcThreatScore(int **gameBoard, int player) {
    int nextRow;
    int score = 0;
    for (int i = 0; i < 7; ++i) { // linearly go from left to right to eval all 
        nextRow = findNextRow(gameBoard, i);
        if (nextRow < 1)
            continue; // because the threat shouldnot be the immediate step. If it is less than 1, it is the last step can take
        for (int j = 0; j < nextRow; ++j)
            score += calcThreatScoreOf(gameBoard, i, j, player);
    }

    return score;
}

int Game::calcImmedScore(int **gameBoard, int player) {
    int nextRow;
    int score = 0;
    for (int i = 0; i < 7; ++i) { // linearly go from left to right to eval all 
        nextRow = findNextRow(gameBoard, i);
        if (nextRow >= 0)
            score += calcThreatScoreOf(gameBoard, i, nextRow, player);
    }

    return score;
}

// count how many winning rows does the player has
void Game::numWinningRow(int **_gameBoard, int &_player1winning, int &_player2winning) {
    _player2winning = 0;
    _player1winning = 0;

    //check horizontally
    int i;
    for (i = 0; i < 6; i++) {
        //check player 1
        if (_gameBoard[i][0] != 1 && _gameBoard[i][1] != 1 && _gameBoard[i][2] != 1 && _gameBoard[i][3] != 1)
            _player2winning++;
        if (_gameBoard[i][1] != 1 && _gameBoard[i][2] != 1 && _gameBoard[i][3] != 1 && _gameBoard[i][4] != 1)
            _player2winning++;
        if (_gameBoard[i][2] != 1 && _gameBoard[i][3] != 1 && _gameBoard[i][4] != 1 && _gameBoard[i][5] != 1)
            _player2winning++;
        if (_gameBoard[i][3] != 1 && _gameBoard[i][4] != 1 && _gameBoard[i][5] != 1 && _gameBoard[i][6] != 1)
            _player2winning++;
        //check player 2
        if (_gameBoard[i][0] != 2 && _gameBoard[i][1] != 2 && _gameBoard[i][2] != 2 && _gameBoard[i][3] != 2)
            _player1winning++;
        if (_gameBoard[i][1] != 2 && _gameBoard[i][2] != 2 && _gameBoard[i][3] != 2 && _gameBoard[i][4] != 2)
            _player1winning++;
        if (_gameBoard[i][2] != 2 && _gameBoard[i][3] != 2 && _gameBoard[i][4] != 2 && _gameBoard[i][5] != 2)
            _player1winning++;
        if (_gameBoard[i][3] != 2 && _gameBoard[i][4] != 2 && _gameBoard[i][5] != 2 && _gameBoard[i][6] != 2)
            _player1winning++;
    }

    //check vertically
    int j;
    for (j = 0; j < 7; j++) {
        //check player 1
        if (_gameBoard[0][j] != 1 && _gameBoard[1][j] != 1 && _gameBoard[2][j] != 1 && _gameBoard[3][j] != 1)
            _player2winning++;
        if (_gameBoard[1][j] != 1 && _gameBoard[2][j] != 1 && _gameBoard[3][j] != 1 && _gameBoard[4][j] != 1)
            _player2winning++;
        if (_gameBoard[2][j] != 1 && _gameBoard[3][j] != 1 && _gameBoard[4][j] != 1 && _gameBoard[5][j] != 1)
            _player2winning++;
        //check player 2
        if (_gameBoard[0][j] != 2 && _gameBoard[1][j] != 2 && _gameBoard[2][j] != 2 && _gameBoard[3][j] != 2)
            _player1winning++;
        if (_gameBoard[1][j] != 2 && _gameBoard[2][j] != 2 && _gameBoard[3][j] != 2 && _gameBoard[4][j] != 2)
            _player1winning++;
        if (_gameBoard[2][j] != 2 && _gameBoard[3][j] != 2 && _gameBoard[4][j] != 2 && _gameBoard[5][j] != 2)
            _player1winning++;
    }

    //check diagonally

    //check player 1
    if (_gameBoard[2][0] != 1 && _gameBoard[3][1] != 1
        && _gameBoard[4][2] != 1 && _gameBoard[5][3] != 1) {
        _player2winning++;
    }
    if (_gameBoard[1][0] != 1 && _gameBoard[2][1] != 1
        && _gameBoard[3][2] != 1 && _gameBoard[4][3] != 1) {
        _player2winning++;
    }
    if (_gameBoard[2][1] != 1 && _gameBoard[3][2] != 1
        && _gameBoard[4][3] != 1 && _gameBoard[5][4] != 1) {
        _player2winning++;
    }
    if (_gameBoard[0][0] != 1 && _gameBoard[1][1] != 1
        && _gameBoard[2][2] != 1 && _gameBoard[3][3] != 1) {
        _player2winning++;
    }
    if (_gameBoard[1][1] != 1 && _gameBoard[2][2] != 1
        && _gameBoard[3][3] != 1 && _gameBoard[4][4] != 1) {
        _player2winning++;
    }
    if (_gameBoard[2][2] != 1 && _gameBoard[3][3] != 1
        && _gameBoard[4][4] != 1 && _gameBoard[5][5] != 1) {
        _player2winning++;
    }
    if (_gameBoard[0][1] != 1 && _gameBoard[1][2] != 1
        && _gameBoard[2][3] != 1 && _gameBoard[3][4] != 1) {
        _player2winning++;
    }
    if (_gameBoard[1][2] != 1 && _gameBoard[2][3] != 1
        && _gameBoard[3][4] != 1 && _gameBoard[4][5] != 1) {
        _player2winning++;
    }
    if (_gameBoard[2][3] != 1 && _gameBoard[3][4] != 1
        && _gameBoard[4][5] != 1 && _gameBoard[5][6] != 1) {
        _player2winning++;
    }
    if (_gameBoard[0][2] != 1 && _gameBoard[1][3] != 1
        && _gameBoard[2][4] != 1 && _gameBoard[3][5] != 1) {
        _player2winning++;
    }
    if (_gameBoard[1][3] != 1 && _gameBoard[2][4] != 1
        && _gameBoard[3][5] != 1 && _gameBoard[4][6] != 1) {
        _player2winning++;
    }
    if (_gameBoard[0][3] != 1 && _gameBoard[1][4] != 1
        && _gameBoard[2][5] != 1 && _gameBoard[3][6] != 1) {
        _player2winning++;
    }

    if (_gameBoard[0][3] != 1 && _gameBoard[1][2] != 1
        && _gameBoard[2][1] != 1 && _gameBoard[3][0] != 1) {
        _player2winning++;
    }
    if (_gameBoard[0][4] != 1 && _gameBoard[1][3] != 1
        && _gameBoard[2][2] != 1 && _gameBoard[3][1] != 1) {
        _player2winning++;
    }
    if (_gameBoard[1][3] != 1 && _gameBoard[2][2] != 1
        && _gameBoard[3][1] != 1 && _gameBoard[4][0] != 1) {
        _player2winning++;
    }
    if (_gameBoard[0][5] != 1 && _gameBoard[1][4] != 1
        && _gameBoard[2][3] != 1 && _gameBoard[3][2] != 1) {
        _player2winning++;
    }
    if (_gameBoard[1][4] != 1 && _gameBoard[2][3] != 1
        && _gameBoard[3][2] != 1 && _gameBoard[4][1] != 1) {
        _player2winning++;
    }
    if (_gameBoard[2][3] != 1 && _gameBoard[3][2] != 1
        && _gameBoard[4][1] != 1 && _gameBoard[5][0] != 1) {
        _player2winning++;
    }
    if (_gameBoard[0][6] != 1 && _gameBoard[1][5] != 1
        && _gameBoard[2][4] != 1 && _gameBoard[3][3] != 1) {
        _player2winning++;
    }
    if (_gameBoard[1][5] != 1 && _gameBoard[2][4] != 1
        && _gameBoard[3][3] != 1 && _gameBoard[4][2] != 1) {
        _player2winning++;
    }
    if (_gameBoard[2][4] != 1 && _gameBoard[3][3] != 1
        && _gameBoard[4][2] != 1 && _gameBoard[5][1] != 1) {
        _player2winning++;
    }
    if (_gameBoard[1][6] != 1 && _gameBoard[2][5] != 1
        && _gameBoard[3][4] != 1 && _gameBoard[4][3] != 1) {
        _player2winning++;
    }
    if (_gameBoard[2][5] != 1 && _gameBoard[3][4] != 1
        && _gameBoard[4][3] != 1 && _gameBoard[5][2] != 1) {
        _player2winning++;
    }
    if (_gameBoard[2][6] != 1 && _gameBoard[3][5] != 1
        && _gameBoard[4][4] != 1 && _gameBoard[5][3] != 1) {
        _player2winning++;
    }

    //check player 2
    if (_gameBoard[2][0] != 2 && _gameBoard[3][1] != 2
        && _gameBoard[4][2] != 2 && _gameBoard[5][3] != 2) {
        _player1winning++;
    }
    if (_gameBoard[1][0] != 2 && _gameBoard[2][1] != 2
        && _gameBoard[3][2] != 2 && _gameBoard[4][3] != 2) {
        _player1winning++;
    }
    if (_gameBoard[2][1] != 2 && _gameBoard[3][2] != 2
        && _gameBoard[4][3] != 2 && _gameBoard[5][4] != 2) {
        _player1winning++;
    }
    if (_gameBoard[0][0] != 2 && _gameBoard[1][1] != 2
        && _gameBoard[2][2] != 2 && _gameBoard[3][3] != 2) {
        _player1winning++;
    }
    if (_gameBoard[1][1] != 2 && _gameBoard[2][2] != 2
        && _gameBoard[3][3] != 2 && _gameBoard[4][4] != 2) {
        _player1winning++;
    }
    if (_gameBoard[2][2] != 2 && _gameBoard[3][3] != 2
        && _gameBoard[4][4] != 2 && _gameBoard[5][5] != 2) {
        _player1winning++;
    }
    if (_gameBoard[0][1] != 2 && _gameBoard[1][2] != 2
        && _gameBoard[2][3] != 2 && _gameBoard[3][4] != 2) {
        _player1winning++;
    }
    if (_gameBoard[1][2] != 2 && _gameBoard[2][3] != 2
        && _gameBoard[3][4] != 2 && _gameBoard[4][5] != 2) {
        _player1winning++;
    }
    if (_gameBoard[2][3] != 2 && _gameBoard[3][4] != 2
        && _gameBoard[4][5] != 2 && _gameBoard[5][6] != 2) {
        _player1winning++;
    }
    if (_gameBoard[0][2] != 2 && _gameBoard[1][3] != 2
        && _gameBoard[2][4] != 2 && _gameBoard[3][5] != 2) {
        _player1winning++;
    }
    if (_gameBoard[1][3] != 2 && _gameBoard[2][4] != 2
        && _gameBoard[3][5] != 2 && _gameBoard[4][6] != 2) {
        _player1winning++;
    }
    if (_gameBoard[0][3] != 2 && _gameBoard[1][4] != 2
        && _gameBoard[2][5] != 2 && _gameBoard[3][6] != 2) {
        _player1winning++;
    }

    if (_gameBoard[0][3] != 2 && _gameBoard[1][2] != 2
        && _gameBoard[2][1] != 2 && _gameBoard[3][0] != 2) {
        _player1winning++;
    }
    if (_gameBoard[0][4] != 2 && _gameBoard[1][3] != 2
        && _gameBoard[2][2] != 2 && _gameBoard[3][1] != 2) {
        _player1winning++;
    }
    if (_gameBoard[1][3] != 2 && _gameBoard[2][2] != 2
        && _gameBoard[3][1] != 2 && _gameBoard[4][0] != 2) {
        _player1winning++;
    }
    if (_gameBoard[0][5] != 2 && _gameBoard[1][4] != 2
        && _gameBoard[2][3] != 2 && _gameBoard[3][2] != 2) {
        _player1winning++;
    }
    if (_gameBoard[1][4] != 2 && _gameBoard[2][3] != 2
        && _gameBoard[3][2] != 2 && _gameBoard[4][1] != 2) {
        _player1winning++;
    }
    if (_gameBoard[2][3] != 2 && _gameBoard[3][2] != 2
        && _gameBoard[4][1] != 2 && _gameBoard[5][0] != 2) {
        _player1winning++;
    }
    if (_gameBoard[0][6] != 2 && _gameBoard[1][5] != 2
        && _gameBoard[2][4] != 2 && _gameBoard[3][3] != 2) {
        _player1winning++;
    }
    if (_gameBoard[1][5] != 2 && _gameBoard[2][4] != 2
        && _gameBoard[3][3] != 2 && _gameBoard[4][2] != 2) {
        _player1winning++;
    }
    if (_gameBoard[2][4] != 2 && _gameBoard[3][3] != 2
        && _gameBoard[4][2] != 2 && _gameBoard[5][1] != 2) {
        _player1winning++;
    }
    if (_gameBoard[1][6] != 2 && _gameBoard[2][5] != 2
        && _gameBoard[3][4] != 2 && _gameBoard[4][3] != 2) {
        _player1winning++;
    }
    if (_gameBoard[2][5] != 2 && _gameBoard[3][4] != 2
        && _gameBoard[4][3] != 2 && _gameBoard[5][2] != 2) {
        _player1winning++;
    }
    if (_gameBoard[2][6] != 2 && _gameBoard[3][5] != 2
        && _gameBoard[4][4] != 2 && _gameBoard[5][3] != 2) {
        _player1winning++;
    }
}

int Game::heuristic(int **gameBoard, int player) {
    int p1_score, p2_score;
    int p1_winning_row, p2_winning_row;
    int p1_threat, p2_threat;
    int p1_immed, p2_immed;
    int total = 0;

    // part 1: score of future board conf of both sides.
    countScore(gameBoard);
    p1_score = _player1Score;
    p2_score = _player2Score;

    // part 2: count winning rows
    numWinningRow(gameBoard, p1_winning_row, p2_winning_row);

    // part 3: threats
    p1_threat = calcThreatScore(gameBoard, 1);
    p2_threat = calcThreatScore(gameBoard, 2);

    // part 4: immediate
    p1_immed = calcImmedScore(gameBoard, 1);
    p2_immed = calcImmedScore(gameBoard, 2);

    total = (p1_score + p1_winning_row + p1_threat - 2 * p1_immed) -
            (p2_score + p2_winning_row + p2_threat - 2 * p2_immed);

    return total;
}

int Game::alphabeta(int node[], int depth, int player, int a, int b) {
    if (depth == 0 || totalPiece(node) == 42)
        return heuristic(gameDataTOgameBoard(node), player);

    int value, i;
    int **arrBoard = new int *[7];
    allValidChildConf(arrBoard, node, player);

    if (player == 1) { // define player 1 is the maximize player, so this equilvant to if maximizingPlayer
        value = INT_MIN;
        for (i = 0; i < 7; ++i)
            if (arrBoard[i] != NULL) {
                value = max(value, alphabeta(arrBoard[i], depth - 1, 2, a, b));
                a = max(value, a);
                if (b <= a) {
                    break;
                }
            }
    } else {
        value = INT_MAX;
        for (i = 0; i < 7; ++i)
            if (arrBoard[i] != NULL) {
                value = min(value, alphabeta(arrBoard[i], depth - 1, 1, a, b));
                b = min(value, b);
                if (b <= a) {
                    break;
                }
            }
    }

    freeDynmBoard(arrBoard);
    return value;
}