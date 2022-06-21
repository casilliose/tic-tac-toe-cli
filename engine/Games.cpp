#include <iostream>
#include <vector>
#include "Games.h"
#include "Menu.h"
#include "Render.h"

#define CLEAR u8"\033[2J\033[1;1H"

using namespace std;

void TicTacToe::Games::play() {
    if (!isStartGame) {
        Menu menu;
        menu.globalMenu();
        menu.sizeMapMenu();
        this->sizeMapX = menu.sizeMapX;
        this->sizeMapY = menu.sizeMapY;
        vector<vector<uint64_t*>> map{sizeMapX,vector<uint64_t*>{sizeMapY,nullptr}};
        isStartGame = true;
        cout << menu.sizeMapX << " " << menu.sizeMapY << endl;
        cout << this->sizeMapX << " " << this->sizeMapY << endl;
        exit(0);
        // cout << CLEAR;
    } else {
        for (size_t i = 0; i < sizeMapX; i++)
        {
            for (size_t j = 0; j < sizeMapY; j++)
            {
                cout << i << " ";
            }
            cout << endl;
        }
    }
}
