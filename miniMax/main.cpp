#include "game.h"

int main(int argc, char **argv) {
    Game game;
    game.init(argc, argv, true);
    game.start();
}