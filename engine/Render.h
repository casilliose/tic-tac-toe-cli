#include <iostream>

using namespace std;

namespace TicTacToe {
    class Render {
        public:
            uint64_t sizeX {0}, sizeY {0};
        
        public:
            void run(vector<vector<uint64_t*>> * pointerMap, size_t sizeX, size_t sizeY);
    };
}
