#include <iostream>
#include <vector>

using namespace std;

namespace TicTacToe {
    class Render {
        public:
            size_t sizeX {0}, sizeY {0};
        
        public:
            void run(vector<vector<size_t*>> * pointerMap, size_t sizeX, size_t sizeY) {
                for (size_t i = 0; i < sizeX; i++)
                {
                    for (size_t j = 0; j < sizeY; j++)
                    {
                        cout << i << j << " ";
                    }
                    cout << endl;
                }
            }
    };
}
