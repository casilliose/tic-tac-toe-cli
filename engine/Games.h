#include <vector>

using namespace std;

namespace TicTacToe {
    class Games {
        public:
            uint8_t sizeMapX {0}, sizeMapY {0};
            enum crossZero {cross, zero};
            struct player {
                uint8_t numberPlayer : 2;
                char nameGamer[255] {""};
                bool isPC {false};
            };
            vector<vector<uint64_t*>> map;
            bool isStartGame {false};

        public:
            Games() = default;
            ~Games() {
                cout << "Игра закончена !!!";   
            }
            void play();
    };
}