#include <iostream>

#ifdef __linux__
    #define CLEAR u8"\033[2J\033[1;1H" /* clear console for linux */
    #define RESET "\033[0m"
    #define BOLDRED "\033[1m\033[31m" /* Bold Red */
    #define BOLDCYAN "\033[1m\033[36m" /* Bold Cyan */
    #define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
    #define BOLDBLUE    "\033[1m\033[34m" /* Bold Blue */
    #define BOLDYELLOW  "\033[1m\033[33m" /* Bold Yellow */
#elif
    #define CLEAR "" /* clear console for windows */
    #define RESET ""
    #define BOLDRED "" /* Bold Red */
    #define BOLDCYAN "" /* Bold Cyan */
    #define BOLDMAGENTA "" /* Bold Magenta */
    #define BOLDBLUE    "" /* Bold Blue */
    #define BOLDYELLOW  "" /* Bold Yellow */
#endif

using namespace std;

enum TypeGame {
    YOU_VS_PC = 1,
    YOU_VS_PERSON = 2
};

enum SceneValue {
    EMPTY,
    ZERO,
    CROSS
};

struct GameSetting {
    bool isStartGame {false};
    size_t countRows {3};
    size_t countCols {3};
    TypeGame currentTypeGame {YOU_VS_PC};
};

struct Player
{

};

size_t inputSizeGameScene(string nameSizeScene) {
    size_t currentSizeScene;
    while (true) {
        cin >> currentSizeScene;
        if (cin.fail() || (currentSizeScene > 100 || currentSizeScene < 3)) {
            cout << BOLDRED << "Вы ввели не корректное количество " << nameSizeScene << ", повторите ввод снова" << RESET << endl;
            cin.clear();
            cin.ignore(32767, '\n');
        } else {
            return currentSizeScene;
        }
    }
}

size_t inputNumberTypeGameMenu() {
    size_t currentNumberMenu;
    while (true) {
        cin >> currentNumberMenu;
        if (cin.fail() || (currentNumberMenu != YOU_VS_PC && currentNumberMenu != YOU_VS_PERSON)) {
            cout << BOLDRED << "Вы ввели не корректное значение, повторите ввод снова" << RESET << endl;
            cin.clear();
            cin.ignore(32767, '\n');
        } else {
            return currentNumberMenu;
        }
    }
}

void inputSettingFromMenu(GameSetting &GameSetting) {
    cout << "Привет, это игра в крестики нолики" << endl;
    cout << "Выберите и введите номер пунка из меню : " << endl;
    cout << "Меню" << endl;
    cout << "№1 Вы против ПК" << endl;
    cout << "№2 Вы против Другого игрока" << endl;
    GameSetting.currentTypeGame = inputNumberTypeGameMenu() == YOU_VS_PC ? YOU_VS_PC : YOU_VS_PERSON;
    cout << CLEAR;
    cout << "Введите размер игрового поля от 3 и до 100 (по умолчанию 3 на 3)" << endl;
    cout << "Введите количество строк : " << endl;
    GameSetting.countRows = inputSizeGameScene("строк");
    cout << "Введите количество столбцов : " << endl;
    GameSetting.countCols = inputSizeGameScene("столбцов");
    cout << CLEAR;
}

SceneValue ** initScene(GameSetting const GameSetting) {
    SceneValue ** scene = new (std::nothrow) SceneValue * [GameSetting.countRows];
    if (scene == nullptr) {
        cout << BOLDRED << "Ошибка, недостаточно памяти" << RESET << endl;
        exit(0);
    }
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        scene[i] = new (std::nothrow) SceneValue[GameSetting.countCols] {EMPTY};
        if (scene[i] == nullptr) {
            cout << BOLDRED << "Ошибка, недостаточно памяти" << RESET << endl;
            exit(0);
        }
    }
    return scene;
}

void showHorizontalLine(const size_t countCols) {
    const size_t countElementForWightLine {4};
    const size_t countElementForDiffWight {5};
    const size_t countLineElement = countCols * countElementForWightLine + countElementForDiffWight;
    for (size_t i = 1; i <= countLineElement; i++) {
        cout << "―";
    }
}

void showHeadRows(const size_t countCols) {
    showHorizontalLine(countCols);
    cout << endl << "|" << BOLDMAGENTA << "X/O" << RESET << "|";
    for (size_t j = 1; j <= countCols; j++) {
        cout << " " << BOLDCYAN << j << RESET << " |";
    }
    cout << endl;
    showHorizontalLine(countCols);
    cout << endl;
}

void showHeadCol(const size_t indexCol) {
    cout << "| " << BOLDCYAN << indexCol + 1 << RESET << " |";
}

void showValueScene(const char value, const string color) {
    cout << " " << color << value << RESET << " |";
}

void renderScene(SceneValue** const scene, const GameSetting GameSetting) {
    showHeadRows(GameSetting.countCols);
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        for (size_t j = 0; j < GameSetting.countCols; j++) {
            if (j == 0) {
                showHeadCol(i);
            }
            if (scene[i][j] == 0) {
                showValueScene(' ', "");
            } else if (scene[i][j] == 1) {
                showValueScene('0', BOLDBLUE);
            } else {
                showValueScene('X', BOLDYELLOW);
            }
        }
        cout << endl;
        showHorizontalLine(GameSetting.countCols);
        cout << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    GameSetting GameSetting;
    inputSettingFromMenu(GameSetting);
    SceneValue ** scene = initScene(GameSetting);
    renderScene(scene, GameSetting);
    // while(isStartGame) {

    // }
    // // 3. Освобождение памяти
    // for (size_t i = 0; i < m; i++) {
    // delete [] ptrArr[i]; // Освобождаем i-тый одномерный int массив
    // }
    // delete[] ptrArr; // Удаляем массив указателей
    // ptrArr = nullptr;
    // return EXIT_SUCCESS;
}
