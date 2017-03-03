#pragma once

#include <string>
#include <vector>

const int ASCII_0 = 48;
const int ASCII_9 = 57;

enum game_mode {
    INTERACTIVE,
    ONEMOVE,
    NOTSET,
};

class Game {
public:
    Game();

    // logic controll
    void init(int argc, char **argv, bool debug = false);

    void start();

private:
    const char *_comOutputFile = "computer.txt";
    const char *_humOutputFile = "human.txt";

    int *_gameBoard[6];
    int _gameData[42];
    int _currentTurn;
    int _pieceCount;
    int _player1Score;
    int _player2Score;
    int _depthLim;

    char *_infilename = NULL;
    char *_outfilename = NULL;

    game_mode _gamemode;
    bool _comNext;

    // PhraseArg
    void setGameMode(char *mode);

    void setInputfile(char *infile);

    void setOutputfile(char *outfile);

    void setNextPlayer(char *next);

    void setDepthLimit(char *depth);

    // I/O
    void printGameBoard();

    void printGameBoardToFile(const char *outfilename);

    void printPlayerScore();

    void readInputFile();

    // Logic control (general game flow)
    void startOneMove();

    void startInteractive();

    void aiPlay();

    void humanPlay();

    // Helper
    void countScore(int *_gamedata);

    void countScore(int **_gameBoard);

    bool isValidColumn(int column, int *gamedata);

    bool playPiece(int column, int *gamedata, int player);

    int totalPiece(int *gamedata);

    int **gameDataTOgameBoard(int *gamedata);

    bool getUserInputInt(int &in);

    // game AI functions
    void aiPlayABPruning();

    void allValidChildConf(int **arrBoard, int *currBoard, int player);

    int calcThreatScoreOf(int **gameBoard, int col, int row, int player);

    int calcThreatScore(int **gameBoard, int player);

    int calcImmedScore(int **gameBoard, int player);

    //int numWinningRowOf(int ** gameboard, int player);
    int heuristic(int **gameBoard, int player);

    int alphabeta(int node[], int depth, int player, int a, int b);

    void numWinningRow(int **_gameBoard, int &_player1winning, int &_player2winning);
};
