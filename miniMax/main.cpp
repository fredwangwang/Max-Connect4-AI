#include <iostream>
#include <time.h>
#include "game.h"

using namespace std;

int main(int argc, char ** argv) {
    srand(time(0));

    Game game;
    game.init(argc, argv);
    game.start();
}