#include "game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdlib.h>

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
void Game::printGameBoardToFile(const char * outfilename) {
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
    countScore();
    cout << "Score: Player 1 = " << _player1Score << ", Player 2 = " << _player2Score << endl;
}

// Given a column and which player it is, 
// place that player's piece in the requested column
bool Game::playPiece(int column) {
    if (_gameBoard[0][column] != 0)
        return false;

    for (int i = 5; i >= 0; i--) {
        if (_gameBoard[i][column] == 0) {
            _gameBoard[i][column] = _currentTurn;
            _pieceCount++;
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
        printf("move %i: Player %i, column %i\n\n\n",
            _pieceCount, _currentTurn, randColumn + 1);
        if (_currentTurn == 1)
            _currentTurn = 2;
        else
            _currentTurn = 1;
    }
}

void Game::humanPlay() {
    cout << "Which column do you want to play: ";
    int col;
    cin >> col;
    --col;
    while (!playPiece(col)) {
        cout << "That is not a valid move, retry: ";
        cin >> col;
        --col;
    }
    if (_currentTurn == 1)
        _currentTurn = 2;
    else
        _currentTurn = 1;
}

// this serves its job... but too long
void Game::countScore() {
    _player1Score = 0;
    _player2Score = 0;

    //check horizontally
    int i;
    for (i = 0; i < 6; i++)
    {
        //check player 1
        if (_gameBoard[i][0] == 1 && _gameBoard[i][1] == 1
            && _gameBoard[i][2] == 1 && _gameBoard[i][3] == 1)
        {
            _player1Score++;
        }
        if (_gameBoard[i][1] == 1 && _gameBoard[i][2] == 1
            && _gameBoard[i][3] == 1 && _gameBoard[i][4] == 1)
        {
            _player1Score++;
        }
        if (_gameBoard[i][2] == 1 && _gameBoard[i][3] == 1
            && _gameBoard[i][4] == 1 && _gameBoard[i][5] == 1)
        {
            _player1Score++;
        }
        if (_gameBoard[i][3] == 1 && _gameBoard[i][4] == 1
            && _gameBoard[i][5] == 1 && _gameBoard[i][6] == 1)
        {
            _player1Score++;
        }
        //check player 2
        if (_gameBoard[i][0] == 2 && _gameBoard[i][1] == 2
            && _gameBoard[i][2] == 2 && _gameBoard[i][3] == 2)
        {
            _player2Score++;
        }
        if (_gameBoard[i][1] == 2 && _gameBoard[i][2] == 2
            && _gameBoard[i][3] == 2 && _gameBoard[i][4] == 2)
        {
            _player2Score++;
        }
        if (_gameBoard[i][2] == 2 && _gameBoard[i][3] == 2
            && _gameBoard[i][4] == 2 && _gameBoard[i][5] == 2)
        {
            _player2Score++;
        }
        if (_gameBoard[i][3] == 2 && _gameBoard[i][4] == 2
            && _gameBoard[i][5] == 2 && _gameBoard[i][6] == 2)
        {
            _player2Score++;
        }
    }

    //check vertically
    int j;
    for (j = 0; j < 7; j++)
    {
        //check player 1
        if (_gameBoard[0][j] == 1 && _gameBoard[1][j] == 1
            && _gameBoard[2][j] == 1 && _gameBoard[3][j] == 1)
        {
            _player1Score++;
        }
        if (_gameBoard[1][j] == 1 && _gameBoard[2][j] == 1
            && _gameBoard[3][j] == 1 && _gameBoard[4][j] == 1)
        {
            _player1Score++;
        }
        if (_gameBoard[2][j] == 1 && _gameBoard[3][j] == 1
            && _gameBoard[4][j] == 1 && _gameBoard[5][j] == 1)
        {
            _player1Score++;
        }
        //check player 2
        if (_gameBoard[0][j] == 2 && _gameBoard[1][j] == 2
            && _gameBoard[2][j] == 2 && _gameBoard[3][j] == 2)
        {
            _player2Score++;
        }
        if (_gameBoard[1][j] == 2 && _gameBoard[2][j] == 2
            && _gameBoard[3][j] == 2 && _gameBoard[4][j] == 2)
        {
            _player2Score++;
        }
        if (_gameBoard[2][j] == 2 && _gameBoard[3][j] == 2
            && _gameBoard[4][j] == 2 && _gameBoard[5][j] == 2)
        {
            _player2Score++;
        }
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

void Game::startOneMove() {
    if (_pieceCount == 42) {
        cout << "The board is full" << endl;
        exit;
    }
    cout << "Computer is playing..." << endl;
    aiPlay();
    printGameBoard();
    printPlayerScore();
    printGameBoardToFile(_outfilename);
}

void Game::startInteractive() {
    while (_pieceCount != 42) {
        if (_comNext) {
            _comNext = false;
            cout << "Computer is playing..." << endl;
            aiPlay();
            printGameBoardToFile(_comOutputFile);
            printGameBoard();
            printPlayerScore();
        }
        else {
            _comNext = true;
            cout << "It is your turn." << " You are playing: \"" << ((_currentTurn == 1) ? "O\"" : "X\"") << endl;
            humanPlay();
            printGameBoardToFile(_humOutputFile);
        }

    }
    
    int winner = 0;
    if (_player1Score > _player2Score)
        winner = 1;
    else if (_player1Score < _player2Score)
        winner = 2;
    cout << "\n\n\nGAME OVER\n\n\n";
    if (winner)
        cout << "WINNER IS PLAYER " << winner << endl;
    else
        cout << "THIS IS A DRAW" << endl;
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
    const int ASCII_0 = 48;
    for (int i = 0; i < 6; ++i) {
        getline(fin, oneline);
        for (int j = 0; j < 7; ++j) {
            _gameBoard[i][j] = (int)oneline[j] - ASCII_0;
            if (_gameBoard[i][j])
                ++_pieceCount;
        }
    }

    fin >> _currentTurn;
    fin.close();
}

void Game::start() {
    readInputFile();
    cout << "MaxConnect-4 game" << endl << endl;
    cout << "game state before move:" << endl;
    printGameBoard();
    printPlayerScore();

    if (_gamemode == INTERACTIVE) startInteractive();
    else startOneMove();
}

void Game::init(int argc, char ** argv) {
    if (argc != 5) {
        cout << "Four command-line arguments are needed:\n";
        cout << "Usage: Program interactive [input_file] [computer-next/human-next] [depth]\n";
        cout << "or: Program one-move [input_file] [output_file] [depth]\n";
        exit(EXIT_SUCCESS);
    }

    setGameMode(argv[1]);
    setInputfile(argv[2]);
    if (_gamemode == INTERACTIVE) setNextPlayer(argv[3]);
    else setOutputfile(argv[3]);
}

void Game::setGameMode(char * mode) {
    if (strcmp(mode, "interactive") == 0 || strcmp(mode, "i") == 0)
        this->_gamemode = INTERACTIVE;
    else if (strcmp(mode, "one-move") == 0 || strcmp(mode, "o") == 0)
        this->_gamemode = ONEMOVE;
    else {
        cerr << mode << " is an unrecognized game mode\n";
        exit(EXIT_FAILURE);
    }
}

void Game::setInputfile(char * infile) {
    _infilename = infile;
}

void Game::setOutputfile(char * outfile) {
    _outfilename = outfile;
}

void Game::setNextPlayer(char * next) {
    if (strcmp(next, "computer-next") == 0 || strcmp(next, "c") == 0)
        this->_comNext = true;
    else if (strcmp(next, "human-next") == 0 || strcmp(next, "h") == 0)
        this->_comNext = false;
    else {
        cerr << next << " is an unrecognized command\n";
        exit(EXIT_FAILURE);
    }
}

