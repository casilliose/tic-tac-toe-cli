#include <iostream>
#include <vector>
#include "Render.h"

using namespace std;

void TicTacToe::Render::run(vector<vector<uint64_t*>> * pointerMap, size_t sizeX, size_t sizeY)
{
    for (size_t i = 0; i < sizeX; i++)
    {
        for (size_t j = 0; j < sizeY; j++)
        {
            cout << i << j << " ";
        }
        cout << endl;
    }
}