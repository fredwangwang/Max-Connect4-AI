#pragma once

#include <string>

enum game_mode {
    INTERACTIVE,
    ONEMOVE,
    NOTSET,
};

class Game
{
public:
    Game();

    void printGameBoard(ostream & out = cout);
    bool playPiece(int column);
    void aiPlay();
    void countScore();
    void setGameMode(char * gamemode);

    int * gameBoard[6];
    long currentTurn;
    int player1Score;
    int player2Score;
    int pieceCount;
    char * filename;

    game_mode gamemode;
private:
    int gameData[42];
};
