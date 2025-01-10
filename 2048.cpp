#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <termios.h>
#include <unistd.h>

using namespace std;

// 用于 Mac/Linux 的键盘输入函数
// use it to replace the _getch() function in Windows
char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

// 清屏函数（跨平台）
// clear screen function (cross-platform)
void clearScreen() {
    cout << "\033[2J\033[1;1H";  // ANSI escape codes for clearing screen
}

class Game2048 {
private:
    int board[4][4];
    int score;

    // 初始化游戏板
    // initialize the game board
    void initBoard() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                board[i][j] = 0;
            }
        }
        score = 0;
        addNewNumber();
        addNewNumber();
    }

    // 在空位置随机添加新数字（2或4）
    // add a new number (2 or 4) to a random empty cell
    void addNewNumber() {
        int emptyCells = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == 0) emptyCells++;
            }
        }
        
        if (emptyCells == 0) return;

        int position = rand() % emptyCells;
        int value = (rand() % 2 + 1) * 2; // 生成2或4 (2 or 4)

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == 0) {
                    if (position == 0) {
                        board[i][j] = value;
                        return;
                    }
                    position--;
                }
            }
        }
    }

    // 移动并合并数字
    // move and merge numbers
    bool moveAndMerge(int direction) {
        bool moved = false;
        
        switch(direction) {
            case 0: // 上 up
                for (int j = 0; j < 4; j++) {
                    for (int i = 1; i < 4; i++) {
                        if (board[i][j] != 0) {
                            int row = i;
                            while (row > 0 && (board[row-1][j] == 0 || board[row-1][j] == board[row][j])) {
                                if (board[row-1][j] == board[row][j]) {
                                    board[row-1][j] *= 2;
                                    score += board[row-1][j];
                                    board[row][j] = 0;
                                    moved = true;
                                    break;
                                }
                                else if (board[row-1][j] == 0) {
                                    board[row-1][j] = board[row][j];
                                    board[row][j] = 0;
                                    moved = true;
                                    row--;
                                }
                            }
                        }
                    }
                }
                break;

            case 1: // 下 down
                for (int j = 0; j < 4; j++) {
                    for (int i = 2; i >= 0; i--) {
                        if (board[i][j] != 0) {
                            int row = i;
                            while (row < 3 && (board[row+1][j] == 0 || board[row+1][j] == board[row][j])) {
                                if (board[row+1][j] == board[row][j]) {
                                    board[row+1][j] *= 2;
                                    score += board[row+1][j];
                                    board[row][j] = 0;
                                    moved = true;
                                    break;
                                }
                                else if (board[row+1][j] == 0) {
                                    board[row+1][j] = board[row][j];
                                    board[row][j] = 0;
                                    moved = true;
                                    row++;
                                }
                            }
                        }
                    }
                }
                break;

            case 2: // 左 left
                for (int i = 0; i < 4; i++) {
                    for (int j = 1; j < 4; j++) {
                        if (board[i][j] != 0) {
                            int col = j;
                            while (col > 0 && (board[i][col-1] == 0 || board[i][col-1] == board[i][col])) {
                                if (board[i][col-1] == board[i][col]) {
                                    board[i][col-1] *= 2;
                                    score += board[i][col-1];
                                    board[i][col] = 0;
                                    moved = true;
                                    break;
                                }
                                else if (board[i][col-1] == 0) {
                                    board[i][col-1] = board[i][col];
                                    board[i][col] = 0;
                                    moved = true;
                                    col--;
                                }
                            }
                        }
                    }
                }
                break;

            case 3: // 右 right
                for (int i = 0; i < 4; i++) {
                    for (int j = 2; j >= 0; j--) {
                        if (board[i][j] != 0) {
                            int col = j;
                            while (col < 3 && (board[i][col+1] == 0 || board[i][col+1] == board[i][col])) {
                                if (board[i][col+1] == board[i][col]) {
                                    board[i][col+1] *= 2;
                                    score += board[i][col+1];
                                    board[i][col] = 0;
                                    moved = true;
                                    break;
                                }
                                else if (board[i][col+1] == 0) {
                                    board[i][col+1] = board[i][col];
                                    board[i][col] = 0;
                                    moved = true;
                                    col++;
                                }
                            }
                        }
                    }
                }
                break;
        }
        return moved;
    }

    // 检查游戏是否结束
    // check if the game is over
    bool isGameOver() {
        // 检查是否有空格
        // check if there is any empty cell
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == 0) return false;
            }
        }
        
        // 检查是否可以合并
        // check if there is any possible merge
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == board[i][j+1]) return false;
            }
        }
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 3; i++) {
                if (board[i][j] == board[i+1][j]) return false;
            }
        }
        
        return true;
    }

public:
    Game2048() {
        srand(time(0));
        initBoard();
    }

    // 显示游戏面板
    // display the game board
    void displayBoard() {
        clearScreen();
        cout << "Score: " << score << endl << endl;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == 0) {
                    cout << setw(5) << ".";
                } else {
                    cout << setw(5) << board[i][j];
                }
            }
            cout << endl << endl;
        }
        cout << "Use W/S/A/D to control direction, Q to quit" << endl;
    }

    // 处理用户输入
    // process user input
    bool processInput() {
        char input = getch();
        bool moved = false;

        switch(toupper(input)) {
            case 'W': moved = moveAndMerge(0); break;
            case 'S': moved = moveAndMerge(1); break;
            case 'A': moved = moveAndMerge(2); break;
            case 'D': moved = moveAndMerge(3); break;
            case 'Q': return false;
        }

        if (moved) {
            addNewNumber();
            if (isGameOver()) {
                displayBoard();
                cout << "Game Over! Final Score: " << score << endl;
                return false;
            }
        }

        return true;
    }
};

int main() {
    Game2048 game;
    while (true) {
        game.displayBoard();
        if (!game.processInput()) break;
    }
    return 0;
}