#include <iostream>
#include <unistd.h>

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

enum AllPlayers {
    FIRST = 1,
    SECOND = 2
};

struct GameSetting {
    size_t countRows {3};
    size_t countCols {3};
    TypeGame currentTypeGame {YOU_VS_PC};
};

struct Player
{
    SceneValue typePlayer {ZERO};
    AllPlayers numberInGame;
    string name {""};
    bool isVin {false};
};

struct Game
{
    AllPlayers currentPlayerMove;
    bool isStartGame {false};
    size_t countMove {0};
};

size_t inputSizeGameScene() {
    size_t currentSizeScene;
    while (true) {
        cin >> currentSizeScene;
        if (cin.fail() || (currentSizeScene > 100 || currentSizeScene < 3)) {
            cout << BOLDRED << "Вы ввели не корректное количество, повторите ввод снова" << RESET << endl;
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
    cout << "Введите замер поля : " << endl;
    GameSetting.countRows = inputSizeGameScene();
    GameSetting.countCols = GameSetting.countRows;
    cout << CLEAR;
}

SceneValue ** initScene(const GameSetting GameSetting) {
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

void inputMove(SceneValue** const scene, const GameSetting GameSetting, const Player Player) {
    size_t currentCoordinateRow;
    size_t currentCoordinateCol;
    while (true) {
        while (true) {
            cout << "Введите номер строки : " << endl;
            cin >> currentCoordinateRow;
            if (cin.fail() || currentCoordinateRow > GameSetting.countRows || currentCoordinateRow < 1) {
                cout << BOLDRED << "Вы ввели неверный номер строки" << RESET << endl;
                cin.clear();
                cin.ignore(32767, '\n');
            } else {
                break;
            }
        }
        while (true) {
            cout << "Введите номер столбца : " << endl;
            cin >> currentCoordinateCol;
            if (cin.fail() || currentCoordinateCol > GameSetting.countRows || currentCoordinateCol < 1) {
                cout << BOLDRED << "Вы ввели неверный номер столбца" << RESET << endl;
                cin.clear();
                cin.ignore(32767, '\n');
            } else {
                break;
            }
        }
        currentCoordinateRow--;
        currentCoordinateCol--;
        if (scene[currentCoordinateRow][currentCoordinateCol] != 0) {
            cout << CLEAR;
            renderScene(scene, GameSetting);
            cout << endl;
            cout << BOLDRED << "В этой клетке уже занято введите другую позицию" << RESET << endl;
            continue;
        }
        break;
    }
    scene[currentCoordinateRow][currentCoordinateCol] = Player.typePlayer;
}

int randomFistPlayerMove() {
    srand(time(NULL));
    return rand() % 2;
}

void setNextPlayerForMove(Game &Game) {
    if (Game.currentPlayerMove == FIRST) {
        Game.currentPlayerMove = SECOND;
        return;
    }
    Game.currentPlayerMove = FIRST;
}

Player getCurrentMovePlayer(const Player First, const Player Second, const Game Game) {
    if (Game.currentPlayerMove == FIRST) {
        return First;
    }
    return Second;
}

void showPlayerMove(const Player Player) {
    cout << "Ходит " << Player.name << " играет за ";
    if (Player.typePlayer == ZERO) {
        cout << BOLDBLUE << '0' << RESET << endl;
    } else {
        cout << BOLDYELLOW << 'X' << RESET << endl;
    }
}

bool isWinMove(SceneValue** const Scene, const GameSetting GameSetting, const Player Player, const int x, const int y) {
    Scene[x][y] = Player.typePlayer;

    // check win line
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        bool flag = true;
        for (size_t j = 0; j < GameSetting.countCols; j++) {
            if (Scene[i][j] != Player.typePlayer || Scene[i][j] == EMPTY) {
                flag = false;
                break;
            }
        }
        if (flag) {
            Scene[x][y] = EMPTY;
            return true;
        }
    }

    // check win diagonal
    bool flag = true;
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        for (size_t j = 0; j < GameSetting.countCols; j++) {
            if (i == j) {
                if (Scene[i][j] != Player.typePlayer || Scene[i][j] == EMPTY) {
                    flag = false;
                    break;
                }
            }
        }
    }
    if (flag) {
        Scene[x][y] = EMPTY;
        return true;
    }

    // check win revert diagonal
    flag = true;
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        for (size_t j = 0; j < GameSetting.countCols; j++) {
            if(i + j == GameSetting.countRows - 1) {
                if (Scene[i][j] != Player.typePlayer || Scene[i][j] == EMPTY) {
                    flag = false;
                    break;
                }
            }
        }
    }
    if (flag) {
        Scene[x][y] = EMPTY;
        return true;
    }

    // check win colum
    int * winColums = new int[GameSetting.countRows];
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        winColums[i] = 1;
    }
    
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        for (size_t j = 0; j < GameSetting.countCols; j++) {
            if (Scene[i][j] != Player.typePlayer || Scene[i][j] == EMPTY) {
                winColums[j] = 0;
            }
        }
    }
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        if (winColums[i] == 1) {
            Scene[x][y] = EMPTY;
            delete[] winColums;
            return true;
        }
    }
    
    delete[] winColums;

    Scene[x][y] = EMPTY;
    
    return false;
}

bool isWinHumanMove(SceneValue** const Scene, const GameSetting GameSetting, const int x, const int y) {
    Scene[x][y] = ZERO;
    // check win line human
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        bool flag = true;
        for (size_t j = 0; j < GameSetting.countCols; j++) {
            if (Scene[i][j] != ZERO || Scene[i][j] == EMPTY) {
                flag = false;
                break;
            }
        }
        if (flag) {
            Scene[x][y] = EMPTY;
            return true;
        }
    }

    // check win diagonal
    bool flag = true;
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        for (size_t j = 0; j < GameSetting.countCols; j++) {
            if (i == j) {
                if (Scene[i][j] != ZERO || Scene[i][j] == EMPTY) {
                    flag = false;
                    break;
                }
            }
        }
    }
    if (flag) {
        Scene[x][y] = EMPTY;
        return true;
    }

    // check win revert diagonal
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        for (size_t j = 0; j < GameSetting.countCols; j++) {
            if(i + j == GameSetting.countRows - 1) {
                if (Scene[i][j] != ZERO || Scene[i][j] == EMPTY) {
                    flag = false;
                    break;
                }
            }
        }
    }
    if (flag) {
        Scene[x][y] = EMPTY;
        return true;
    }

    // check win colum
    int * winColums = new int[GameSetting.countRows];
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        winColums[i] = 1;
    }
    
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        for (size_t j = 0; j < GameSetting.countCols; j++) {
            if (Scene[i][j] != ZERO || Scene[i][j] == EMPTY) {
                winColums[j] = 0;
            }
        }
    }
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        if (winColums[i] == 1) {
            Scene[x][y] = EMPTY;
            delete[] winColums;
            return true;
        }
    }
    
    delete[] winColums;
    Scene[x][y] = EMPTY;
    return false;
}

bool isLineEmpty(SceneValue** const Scene, const int x, const int countLine) {
    bool flag {true};
    for (size_t i = 0; i < countLine; i++) {
        if (Scene[x][i] != ZERO) {
            flag = false;
        }
    }
    return flag;
}

bool isColumEmpty(SceneValue** const Scene, const int y, const int countLine) {
    bool flag {true};
    for (size_t i = 0; i < countLine; i++) {
        if (Scene[i][y] == ZERO) {
            flag = false;
        }
    }
    return flag;
}

bool isDiagonalEmpty(SceneValue** const Scene, const int x, const int y, const int countLine) {
    bool flag {true};
    for (size_t i = 0; i < countLine; i++) {
        for (size_t j = 0; j < countLine; j++) {
            if (i == j && Scene[i][j] == ZERO) {
                flag = false;
            }
        }
    }
    return flag;
}

bool isRevertDiagonalEmpty(SceneValue** const Scene, const int x, const int y, const int countLine) {
    bool flag {true};
    for (size_t i = 0; i < countLine; i++) {
        for (size_t j = 0; j < countLine; j++) {
            if (i + j == countLine - 1 && Scene[i][j] == ZERO) {
                flag = false;
            }
        }
    }
    return flag;
}

bool isBestMove(SceneValue** const Scene, const GameSetting GameSetting, const int i, const int j) {
    size_t x {0}, y {0};
    int currentScore {0}, maxScore {0};
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        for (size_t i = 0; i < GameSetting.countCols; i++) {
            currentScore = 0;
            if (Scene[i][j] == EMPTY) {
                if (isLineEmpty(Scene, i, GameSetting.countCols)) {
                    currentScore++;
                }
                if (isColumEmpty(Scene, j, GameSetting.countCols)) {
                    currentScore++;
                }
                if (i == j && isDiagonalEmpty(Scene, i, j, GameSetting.countCols)) {
                    currentScore++;
                }
                if (i + j == GameSetting.countRows - 1 && isRevertDiagonalEmpty(Scene, i, j, GameSetting.countCols)) {
                    currentScore++;
                }
            }
            if (currentScore > maxScore) {
                maxScore = currentScore;
                x = i;
                y = j;
            }
        }
    }
    return i == x && j == y;
}

void computerMove(SceneValue** const Scene, const GameSetting GameSetting, const Player Player) {
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        for (size_t j = 0; j < GameSetting.countCols; j++) {
            if (Scene[i][j] == EMPTY) {
                if (isWinMove(Scene, GameSetting, Player, i, j)) {
                    Scene[i][j] = Player.typePlayer;
                    return;
                }
            }
        }
    }
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        for (size_t j = 0; j < GameSetting.countCols; j++) {
            if (Scene[i][j] == EMPTY) {
                if (isWinHumanMove(Scene, GameSetting, i, j)) {
                    Scene[i][j] = Player.typePlayer;
                    return;
                }
            }
        }
    }
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        for (size_t j = 0; j < GameSetting.countCols; j++) {
            if (Scene[i][j] == EMPTY) {
                if (isBestMove(Scene, GameSetting, i, j)) {
                    Scene[i][j] = Player.typePlayer;
                    return;
                }
            }
        }
    }
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        for (size_t j = 0; j < GameSetting.countCols; j++) {
            if (Scene[i][j] == EMPTY) {
                Scene[i][j] = Player.typePlayer;
                return;
            }
        }
    }
}

bool isDraw(const Game Game, const GameSetting GameSetting) {
    if (Game.countMove >= GameSetting.countCols * GameSetting.countRows) {
        return true;
    }
    return false;
}

int getHorizontalScore(SceneValue** const scene, const GameSetting GameSetting, const int scoreForWinFirstPlayer, const int scoreForWinSecondPlayer) {
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        int sumHorizontal = 0;
        for (size_t j = 0; j < GameSetting.countCols; j++) {
            if (scene[i][j] == EMPTY) {
                sumHorizontal = 0;
                break;
            }
            sumHorizontal += scene[i][j];
        }
        if (sumHorizontal == scoreForWinFirstPlayer || sumHorizontal == scoreForWinSecondPlayer) {
            return sumHorizontal;
        }
    }
    return 0;
}

int getVerticalScore(SceneValue** const scene, const GameSetting GameSetting, const int scoreForWinFirstPlayer, const int scoreForWinSecondPlayer) {
    int * summCols = new int[GameSetting.countRows] {0};
    int * emptyCols = new int[GameSetting.countRows] {0};
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        for (size_t j = 0; j < GameSetting.countCols; j++) {
            if (scene[i][j] == EMPTY) {
                emptyCols[j] = 1;
            }
            summCols[j] += scene[i][j];
        }
    }
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        if (emptyCols[i] == 1) {
            continue;
        }
        if (summCols[i] == scoreForWinFirstPlayer || summCols[i] == scoreForWinSecondPlayer) {
            return summCols[i];
        }
    }
    
    delete[] summCols;
    delete[] emptyCols;
    return 0;
}

int getDiagonalScore(SceneValue** const scene, const GameSetting GameSetting, const int scoreForWinFirstPlayer, const int scoreForWinSecondPlayer) {
    int summDiagonal {0};
    bool flagZeroInDiagonal {false};
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        for (size_t j = 0; j < GameSetting.countCols; j++) {
            if (i == j) {
                summDiagonal += scene[i][j];
                if (scene[i][j] == EMPTY) {
                    flagZeroInDiagonal = true;
                }
            }
        }
    }
    if (flagZeroInDiagonal) {
        return 0;
    }
    if (summDiagonal == scoreForWinFirstPlayer || summDiagonal == scoreForWinSecondPlayer) {
        return summDiagonal;
    }
    return 0;
}

int getRevertDiagonalScore(SceneValue** const scene, const GameSetting GameSetting, const int scoreForWinFirstPlayer, const int scoreForWinSecondPlayer) {
    int summRevertDiagonal {0};
    bool flagZeroInRevertDiagonal {false};
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        for (size_t j = 0; j < GameSetting.countCols; j++) {
            if(i + j == GameSetting.countRows - 1) {
                summRevertDiagonal += scene[i][j];
                if (scene[i][j] == EMPTY) {
                    flagZeroInRevertDiagonal = true;
                }
            }
        }
    }
    if (flagZeroInRevertDiagonal) {
        return 0;
    }
    if (summRevertDiagonal == scoreForWinFirstPlayer || summRevertDiagonal == scoreForWinSecondPlayer) {
        return summRevertDiagonal;
    }
    return 0;
}

bool isWin(SceneValue** const scene, const GameSetting GameSetting, Player &PlayerFirst, Player &PlayerSecond) {
    int scoreForWinFirstPlayer = PlayerFirst.typePlayer * GameSetting.countRows;
    int scoreForWinSecondPlayer = PlayerSecond.typePlayer * GameSetting.countRows;
    int scoreHorizontal = getHorizontalScore(scene, GameSetting, scoreForWinFirstPlayer, scoreForWinSecondPlayer);
    int scoreVertical = getVerticalScore(scene, GameSetting, scoreForWinFirstPlayer, scoreForWinSecondPlayer);
    int scoreDiagonal = getDiagonalScore(scene, GameSetting, scoreForWinFirstPlayer, scoreForWinSecondPlayer);
    int scoreRevertDiagonal = getRevertDiagonalScore(scene, GameSetting, scoreForWinFirstPlayer, scoreForWinSecondPlayer);
    if (
        scoreHorizontal == scoreForWinFirstPlayer ||
        scoreDiagonal == scoreForWinFirstPlayer ||
        scoreVertical == scoreForWinFirstPlayer ||
        scoreRevertDiagonal == scoreForWinFirstPlayer
    ) {
        PlayerFirst.isVin = true;
        return true;
    }
    if (
        scoreHorizontal == scoreForWinSecondPlayer || 
        scoreDiagonal == scoreForWinSecondPlayer || 
        scoreVertical == scoreForWinSecondPlayer ||
        scoreRevertDiagonal == scoreForWinSecondPlayer
    ) {
        PlayerSecond.isVin = true;
        return true;
    }
    
    return false;
}

void freeMemory(SceneValue** Scene, const GameSetting GameSetting) {
    for (size_t i = 0; i < GameSetting.countRows; i++) {
        delete [] Scene[i];
    }
    delete[] Scene;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    bool isStartProgram {true};
    char y;
    while (isStartProgram) {
        cout << CLEAR;
        Game Game;
        Game.currentPlayerMove = randomFistPlayerMove() == 0 ? FIRST : SECOND;
        GameSetting GameSetting;

        Player PlayerFirst;
        PlayerFirst.name = "Первый игрок";
        PlayerFirst.typePlayer = ZERO;
        PlayerFirst.numberInGame = FIRST;

        Player PlayerSecond;
        PlayerSecond.name = "Второй игрок";
        PlayerSecond.typePlayer = CROSS;
        PlayerSecond.numberInGame = SECOND;

        inputSettingFromMenu(GameSetting);
        SceneValue ** Scene = initScene(GameSetting);
        renderScene(Scene, GameSetting);
        Game.isStartGame = true;
        while(Game.isStartGame) {
            Player currentPlayer = getCurrentMovePlayer(PlayerFirst, PlayerSecond, Game);
            showPlayerMove(currentPlayer);
            if (
                GameSetting.currentTypeGame == YOU_VS_PERSON || 
                (
                    GameSetting.currentTypeGame == YOU_VS_PC && 
                    currentPlayer.numberInGame == FIRST
                )
            ) {
                inputMove(Scene, GameSetting, currentPlayer);
            } else {
                computerMove(Scene, GameSetting, currentPlayer);
                sleep(1);
            }
            cout << CLEAR;
            Game.countMove++;
            if (isWin(Scene, GameSetting, PlayerFirst, PlayerSecond)) {
                if (PlayerFirst.isVin) {
                    cout << "Выйграл " << PlayerFirst.name << " №" << PlayerFirst.numberInGame << " играл за ";
                    cout << BOLDBLUE << '0' << RESET << endl;
                } else {
                    cout << "Выйграл " << PlayerSecond.name << " №" << PlayerSecond.numberInGame << " играл за ";
                    cout << BOLDYELLOW << 'X' << RESET << endl;
                }
                Game.isStartGame = false;
                renderScene(Scene, GameSetting);
                break;
            }
            if (isDraw(Game, GameSetting)) {
                cout << "Результат игры : Ничья" << endl;
                Game.isStartGame = false;
                renderScene(Scene, GameSetting);
                break;
            }
            renderScene(Scene, GameSetting);
            setNextPlayerForMove(Game);
        }
        freeMemory(Scene, GameSetting);
        Scene = nullptr;
        cout << "Хотите сыграть еще ? тогда введите y" << endl;
        cin >> y;
        if (y != 'y') {
            isStartProgram = false;
        }
    }

    return EXIT_SUCCESS;
}
