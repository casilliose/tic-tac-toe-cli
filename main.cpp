#include <iostream>
#include "engine/Games.cpp"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    TicTacToe::Games game;
    while(true) {
        game.play();
    }
    return EXIT_SUCCESS;
}