#include <iostream>

using namespace std;

namespace TicTacToe {
    class Menu {
        public:
            size_t menuGlobal {1}, sizeMapX {3}, sizeMapY {3};
        public:
            void globalMenu() {
                cout << "Привет, это игра крестики нолики" << endl;
                cout << "Меню, введите номер выбранного пункта меню: " << endl;
                cout << "1. Человек против Человека" << endl;
                cout << "2. Человек против Компьютера" << endl;
                cin >> menuGlobal;
            }
            void sizeMapMenu() {
                cout << "Укажите размер карты от 3 на 3 до 100 на 100" << endl;
                cout << "Размер игры на X " << endl;
                cin >> sizeMapX;
                cout << "Размер игры на Y " << endl;
                cin >> sizeMapY;
            }
    };
}
