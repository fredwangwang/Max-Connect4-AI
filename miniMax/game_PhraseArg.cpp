#include "game.h"
#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

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

void Game::setDepthLimit(char * depth) {
    if (depth[0] < ASCII_0 || depth[0] > ASCII_9) {// this is not a valid number
        cerr << depth << " is not a valid depth limit value" << endl;
        exit(EXIT_FAILURE);
    }
    _depthLim = atoi(depth);
}
