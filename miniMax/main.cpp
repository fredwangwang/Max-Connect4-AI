#include <iostream>
#include "game.h"

using namespace std;

int main(int argc, char ** argv) {
    if (argc != 5) {
        cout << "Four command-line arguments are needed:\n";
        cout << "Usage: Program interactive [input_file] [computer-next/human-next] [depth]\n";
        cout << "or: Program one-move [input_file] [output_file] [depth]\n";
        return 0;
    }

    Game game;
    game.filename = argv[2];

    char * game_mode = argv[1];
    char * input = argv[2];
    char * output = argv[3];
}