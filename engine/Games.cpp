#include <iostream>
#include <vector>

#include "Menu.cpp"
#include "Render.cpp"

#define CLEAR u8"\033[2J\033[1;1H"

using namespace std;

namespace TicTacToe {
    class Games {
        public:
            size_t sizeMapX {0}, sizeMapY {0};
            enum crossZero {cross, zero};
            struct player {
                uint8_t numberPlayer : 2;
                char nameGamer[255] {""};
                bool isPC {false};
            };
            vector<vector<size_t*>> map;
            bool isStartGame {false};

        public:
            Games() = default;
            
            void play() {
                if (!isStartGame) {
                    Menu menu;
                    menu.globalMenu();
                    menu.sizeMapMenu();
                    this->sizeMapX = menu.sizeMapX;
                    this->sizeMapY = menu.sizeMapY;
                    vector<vector<size_t*>> map{sizeMapX,vector<size_t*>{sizeMapY,nullptr}};
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

    };
}