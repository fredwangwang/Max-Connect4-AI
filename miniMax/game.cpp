#include "game.h"
#include <iostream>

using namespace std;

// initialize an empty game board
Game::Game() {
    gameBoard[0] = &(gameData[0]);
    gameBoard[1] = &(gameData[7]);
    gameBoard[2] = &(gameData[14]);
    gameBoard[3] = &(gameData[21]);
    gameBoard[4] = &(gameData[28]);
    gameBoard[5] = &(gameData[35]);

    for (int i = 0; i < 42; i++)
        gameData[i] = 0;

    currentTurn = 1;
    pieceCount = 0;
    player1Score = 0;
    player2Score = 0;
    gamemode = NOTSET;
}

// print out the board given a ostream
void Game::printGameBoard(ostream & out)
{
    out << " -----------------" << endl;
    for (int i = 0; i < 6; i++) {
        out << " | ";
        for (int j = 0; j < 7; j++)
            out << gameBoard[i][j];
        out << endl;
    }
    out << " -----------------" << endl;
}

// Given a column and which player it is, 
// place that player's piece in the requested column
bool Game::playPiece(int column) {
    if (gameBoard[0][column] != 0)
        return false;

    for (int i = 5; i >= 0; i--) {
        if (gameBoard[i][column] == 0) {
            gameBoard[i][column] = currentTurn;
            pieceCount++;
            return true;
        }
    }

    // never reach, add for safety
    return false;
}

// TODO: The AI section.  Currently plays randomly. 
void Game::aiPlay() {
    int randColumn = (int)rand() % 7;
    bool result = 0;
    result = playPiece(randColumn);
    if (result == 0)
        aiPlay();
    else
    {
        printf("\n\nmove %i: Player %li, column %i\n",
            pieceCount, currentTurn, randColumn + 1);
        if (currentTurn == 1)
            currentTurn = 2;
        else
            currentTurn = 1;
    }
}

void Game::countScore() {
     player1Score = 0;
     player2Score = 0;

    //check horizontally
    int i;
    for (i = 0; i < 6; i++)
    {
        //check player 1
        if ( gameBoard[i][0] == 1 &&  gameBoard[i][1] == 1
            &&  gameBoard[i][2] == 1 &&  gameBoard[i][3] == 1)
        {
             player1Score++;
        }
        if ( gameBoard[i][1] == 1 &&  gameBoard[i][2] == 1
            &&  gameBoard[i][3] == 1 &&  gameBoard[i][4] == 1)
        {
             player1Score++;
        }
        if ( gameBoard[i][2] == 1 &&  gameBoard[i][3] == 1
            &&  gameBoard[i][4] == 1 &&  gameBoard[i][5] == 1)
        {
             player1Score++;
        }
        if ( gameBoard[i][3] == 1 &&  gameBoard[i][4] == 1
            &&  gameBoard[i][5] == 1 &&  gameBoard[i][6] == 1)
        {
             player1Score++;
        }
        //check player 2
        if ( gameBoard[i][0] == 2 &&  gameBoard[i][1] == 2
            &&  gameBoard[i][2] == 2 &&  gameBoard[i][3] == 2)
        {
             player2Score++;
        }
        if ( gameBoard[i][1] == 2 &&  gameBoard[i][2] == 2
            &&  gameBoard[i][3] == 2 &&  gameBoard[i][4] == 2)
        {
             player2Score++;
        }
        if ( gameBoard[i][2] == 2 &&  gameBoard[i][3] == 2
            &&  gameBoard[i][4] == 2 &&  gameBoard[i][5] == 2)
        {
             player2Score++;
        }
        if ( gameBoard[i][3] == 2 &&  gameBoard[i][4] == 2
            &&  gameBoard[i][5] == 2 &&  gameBoard[i][6] == 2)
        {
             player2Score++;
        }
    }

    //check vertically
    int j;
    for (j = 0; j < 7; j++)
    {
        //check player 1
        if ( gameBoard[0][j] == 1 &&  gameBoard[1][j] == 1
            &&  gameBoard[2][j] == 1 &&  gameBoard[3][j] == 1)
        {
             player1Score++;
        }
        if ( gameBoard[1][j] == 1 &&  gameBoard[2][j] == 1
            &&  gameBoard[3][j] == 1 &&  gameBoard[4][j] == 1)
        {
             player1Score++;
        }
        if ( gameBoard[2][j] == 1 &&  gameBoard[3][j] == 1
            &&  gameBoard[4][j] == 1 &&  gameBoard[5][j] == 1)
        {
             player1Score++;
        }
        //check player 2
        if ( gameBoard[0][j] == 2 &&  gameBoard[1][j] == 2
            &&  gameBoard[2][j] == 2 &&  gameBoard[3][j] == 2)
        {
             player2Score++;
        }
        if ( gameBoard[1][j] == 2 &&  gameBoard[2][j] == 2
            &&  gameBoard[3][j] == 2 &&  gameBoard[4][j] == 2)
        {
             player2Score++;
        }
        if ( gameBoard[2][j] == 2 &&  gameBoard[3][j] == 2
            &&  gameBoard[4][j] == 2 &&  gameBoard[5][j] == 2)
        {
             player2Score++;
        }
    }

    //check diagonally

    //check player 1
    if ( gameBoard[2][0] == 1 &&  gameBoard[3][1] == 1
        &&  gameBoard[4][2] == 1 &&  gameBoard[5][3] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[1][0] == 1 &&  gameBoard[2][1] == 1
        &&  gameBoard[3][2] == 1 &&  gameBoard[4][3] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[2][1] == 1 &&  gameBoard[3][2] == 1
        &&  gameBoard[4][3] == 1 &&  gameBoard[5][4] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[0][0] == 1 &&  gameBoard[1][1] == 1
        &&  gameBoard[2][2] == 1 &&  gameBoard[3][3] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[1][1] == 1 &&  gameBoard[2][2] == 1
        &&  gameBoard[3][3] == 1 &&  gameBoard[4][4] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[2][2] == 1 &&  gameBoard[3][3] == 1
        &&  gameBoard[4][4] == 1 &&  gameBoard[5][5] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[0][1] == 1 &&  gameBoard[1][2] == 1
        &&  gameBoard[2][3] == 1 &&  gameBoard[3][4] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[1][2] == 1 &&  gameBoard[2][3] == 1
        &&  gameBoard[3][4] == 1 &&  gameBoard[4][5] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[2][3] == 1 &&  gameBoard[3][4] == 1
        &&  gameBoard[4][5] == 1 &&  gameBoard[5][6] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[0][2] == 1 &&  gameBoard[1][3] == 1
        &&  gameBoard[2][4] == 1 &&  gameBoard[3][5] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[1][3] == 1 &&  gameBoard[2][4] == 1
        &&  gameBoard[3][5] == 1 &&  gameBoard[4][6] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[0][3] == 1 &&  gameBoard[1][4] == 1
        &&  gameBoard[2][5] == 1 &&  gameBoard[3][6] == 1)
    {
         player1Score++;
    }

    if ( gameBoard[0][3] == 1 &&  gameBoard[1][2] == 1
        &&  gameBoard[2][1] == 1 &&  gameBoard[3][0] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[0][4] == 1 &&  gameBoard[1][3] == 1
        &&  gameBoard[2][2] == 1 &&  gameBoard[3][1] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[1][3] == 1 &&  gameBoard[2][2] == 1
        &&  gameBoard[3][1] == 1 &&  gameBoard[4][0] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[0][5] == 1 &&  gameBoard[1][4] == 1
        &&  gameBoard[2][3] == 1 &&  gameBoard[3][2] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[1][4] == 1 &&  gameBoard[2][3] == 1
        &&  gameBoard[3][2] == 1 &&  gameBoard[4][1] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[2][3] == 1 &&  gameBoard[3][2] == 1
        &&  gameBoard[4][1] == 1 &&  gameBoard[5][0] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[0][6] == 1 &&  gameBoard[1][5] == 1
        &&  gameBoard[2][4] == 1 &&  gameBoard[3][3] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[1][5] == 1 &&  gameBoard[2][4] == 1
        &&  gameBoard[3][3] == 1 &&  gameBoard[4][2] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[2][4] == 1 &&  gameBoard[3][3] == 1
        &&  gameBoard[4][2] == 1 &&  gameBoard[5][1] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[1][6] == 1 &&  gameBoard[2][5] == 1
        &&  gameBoard[3][4] == 1 &&  gameBoard[4][3] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[2][5] == 1 &&  gameBoard[3][4] == 1
        &&  gameBoard[4][3] == 1 &&  gameBoard[5][2] == 1)
    {
         player1Score++;
    }
    if ( gameBoard[2][6] == 1 &&  gameBoard[3][5] == 1
        &&  gameBoard[4][4] == 1 &&  gameBoard[5][3] == 1)
    {
         player1Score++;
    }

    //check player 2
    if ( gameBoard[2][0] == 2 &&  gameBoard[3][1] == 2
        &&  gameBoard[4][2] == 2 &&  gameBoard[5][3] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[1][0] == 2 &&  gameBoard[2][1] == 2
        &&  gameBoard[3][2] == 2 &&  gameBoard[4][3] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[2][1] == 2 &&  gameBoard[3][2] == 2
        &&  gameBoard[4][3] == 2 &&  gameBoard[5][4] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[0][0] == 2 &&  gameBoard[1][1] == 2
        &&  gameBoard[2][2] == 2 &&  gameBoard[3][3] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[1][1] == 2 &&  gameBoard[2][2] == 2
        &&  gameBoard[3][3] == 2 &&  gameBoard[4][4] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[2][2] == 2 &&  gameBoard[3][3] == 2
        &&  gameBoard[4][4] == 2 &&  gameBoard[5][5] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[0][1] == 2 &&  gameBoard[1][2] == 2
        &&  gameBoard[2][3] == 2 &&  gameBoard[3][4] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[1][2] == 2 &&  gameBoard[2][3] == 2
        &&  gameBoard[3][4] == 2 &&  gameBoard[4][5] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[2][3] == 2 &&  gameBoard[3][4] == 2
        &&  gameBoard[4][5] == 2 &&  gameBoard[5][6] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[0][2] == 2 &&  gameBoard[1][3] == 2
        &&  gameBoard[2][4] == 2 &&  gameBoard[3][5] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[1][3] == 2 &&  gameBoard[2][4] == 2
        &&  gameBoard[3][5] == 2 &&  gameBoard[4][6] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[0][3] == 2 &&  gameBoard[1][4] == 2
        &&  gameBoard[2][5] == 2 &&  gameBoard[3][6] == 2)
    {
         player2Score++;
    }

    if ( gameBoard[0][3] == 2 &&  gameBoard[1][2] == 2
        &&  gameBoard[2][1] == 2 &&  gameBoard[3][0] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[0][4] == 2 &&  gameBoard[1][3] == 2
        &&  gameBoard[2][2] == 2 &&  gameBoard[3][1] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[1][3] == 2 &&  gameBoard[2][2] == 2
        &&  gameBoard[3][1] == 2 &&  gameBoard[4][0] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[0][5] == 2 &&  gameBoard[1][4] == 2
        &&  gameBoard[2][3] == 2 &&  gameBoard[3][2] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[1][4] == 2 &&  gameBoard[2][3] == 2
        &&  gameBoard[3][2] == 2 &&  gameBoard[4][1] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[2][3] == 2 &&  gameBoard[3][2] == 2
        &&  gameBoard[4][1] == 2 &&  gameBoard[5][0] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[0][6] == 2 &&  gameBoard[1][5] == 2
        &&  gameBoard[2][4] == 2 &&  gameBoard[3][3] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[1][5] == 2 &&  gameBoard[2][4] == 2
        &&  gameBoard[3][3] == 2 &&  gameBoard[4][2] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[2][4] == 2 &&  gameBoard[3][3] == 2
        &&  gameBoard[4][2] == 2 &&  gameBoard[5][1] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[1][6] == 2 &&  gameBoard[2][5] == 2
        &&  gameBoard[3][4] == 2 &&  gameBoard[4][3] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[2][5] == 2 &&  gameBoard[3][4] == 2
        &&  gameBoard[4][3] == 2 &&  gameBoard[5][2] == 2)
    {
         player2Score++;
    }
    if ( gameBoard[2][6] == 2 &&  gameBoard[3][5] == 2
        &&  gameBoard[4][4] == 2 &&  gameBoard[5][3] == 2)
    {
         player2Score++;
    }
}

void Game::setGameMode(char * gamemode)
{
}

