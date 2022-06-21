#include <iostream>
#include "Menu.h"

using namespace std;

void TicTacToe::Menu::globalMenu() {
    cout << "Привет, это игра крестики нолики" << endl;
    cout << "Меню, введите номер выбранного пункта меню: " << endl;
    cout << "1. Человек против Человека" << endl;
    cout << "2. Человек против Компьютера" << endl;
    cin >> menuGlobal;
}

void TicTacToe::Menu::sizeMapMenu() {
    cout << "Укажите размер карты от 3 на 3 до 100 на 100" << endl;
    cout << "Размер игры на X " << endl;
    cin >> sizeMapX;
    cout << "Размер игры на Y " << endl;
    cin >> sizeMapY;
}
