#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

// Tetromino shapes
const std::vector<std::vector<std::vector<int>>> SHAPES = {
    {{1, 1, 1, 1}}, // I
    {{1, 1}, {1, 1}}, // O
    {{0, 1, 0}, {1, 1, 1}}, // T
    {{1, 1, 0}, {0, 1, 1}}, // S
    {{0, 1, 1}, {1, 1, 0}}, // Z
    {{1, 0, 0}, {1, 1, 1}}, // L
    {{0, 0, 1}, {1, 1, 1}}  // J
};

class Tetromino {
public:
    Tetromino() {
        shapeIndex = std::rand() % SHAPES.size();
        shapeData = SHAPES[shapeIndex];
        x = BOARD_WIDTH / 2;
        y = 0;
    }

    void rotate() {
        std::vector<std::vector<int>> rotated(shapeData[0].size(), std::vector<int>(shapeData.size()));
        for (size_t i = 0; i < shapeData.size(); i++)
            for (size_t j = 0; j < shapeData[i].size(); j++)
                rotated[j][shapeData.size() - i - 1] = shapeData[i][j];
        shapeData = rotated;
    }

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    const std::vector<std::vector<int>>& getShape() const {
        return shapeData;
    }

    int getX() const { return x; }
    int getY() const { return y; }

private:
    int shapeIndex;
    std::vector<std::vector<int>> shapeData;
    int x, y;
};

class TetrisGame {
public:
    TetrisGame() {
        std::srand(std::time(0));
        field = std::vector<std::vector<int>>(BOARD_HEIGHT, std::vector<int>(BOARD_WIDTH, 0));
        spawnTetromino();
    }

    void run() {
        while (!gameOver) {
            draw();
            input();
            if (!gameOver) update();
        }
        std::cout << "Game Over! Your score: " << score << std::endl;
    }

    const std::vector<std::vector<int>>& getField() const {
        return field;
    }

    bool isGameOver() const {
        return gameOver;
    }

    int getScore() const {
        return score;
    }

private:
    std::vector<std::vector<int>> field;
    Tetromino currentTetromino;
    bool gameOver = false;
    int score = 0;

public:
    void spawnTetromino() {
        currentTetromino = Tetromino();
        if (collides(currentTetromino))
            gameOver = true;
    }

    void draw() {
        system("clear"); // Clear console
        std::vector<std::vector<int>> displayField = field;
        const auto& shape = currentTetromino.getShape();
        int x = currentTetromino.getX();
        int y = currentTetromino.getY();

        for (int i = 0; i < shape.size(); i++) {
            for (int j = 0; j < shape[i].size(); j++) {
                if (shape[i][j]) {
                    displayField[y + i][x + j] = shape[i][j];
                }
            }
        }

        for (const auto& row : displayField) {
            for (const auto& cell : row)
                std::cout << (cell ? '#' : '.') << " ";
            std::cout << std::endl;
        }

        std::cout << "Score: " << score << std::endl;
    }

    void input() {
        if (kbhit()) {
            char ch;
            read(STDIN_FILENO, &ch, 1);
            switch (ch) {
                case 'a':
                    currentTetromino.move(-1, 0);
                    if (collides(currentTetromino)) currentTetromino.move(1, 0);
                    break;
                case 'd':
                    currentTetromino.move(1, 0);
                    if (collides(currentTetromino)) currentTetromino.move(-1, 0);
                    break;
                case 's':
                    currentTetromino.move(0, 1);
                    if (collides(currentTetromino)) {
                        currentTetromino.move(0, -1);
                        lockTetromino();
                    }
                    break;
                case 'w':
                    currentTetromino.rotate();
                    if (collides(currentTetromino)) {
                        // Attempt wall kick
                        currentTetromino.move(1, 0);
                        if (collides(currentTetromino)) {
                            currentTetromino.move(-2, 0);
                            if (collides(currentTetromino)) {
                                currentTetromino.move(1, 0); // Revert
                                currentTetromino.rotate(); // Revert rotation
                                currentTetromino.rotate();
                                currentTetromino.rotate();
                            }
                        }
                    }
                    break;
            }
        }
    }

    int kbhit() {
        struct termios oldt, newt;
        int ch;
        int oldf;
        
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
        
        ch = getchar();
        
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
        
        if(ch != EOF) {
            ungetc(ch, stdin);
            return 1;
        }
        
        return 0;
    }

    void update() {
        currentTetromino.move(0, 1);
        if (collides(currentTetromino)) {
            currentTetromino.move(0, -1);
            lockTetromino();
            clearLines();
            spawnTetromino();
        }
    }

    bool collides(const Tetromino& t) const {
        const auto& shape = t.getShape();
        int x = t.getX();
        int y = t.getY();

        for (size_t i = 0; i < shape.size(); i++) {
            for (size_t j = 0; j < shape[i].size(); j++) {
                if (shape[i][j]) {
                    int newX = x + j;
                    int newY = y + i;

                    if (newX < 0 || newX >= BOARD_WIDTH || newY >= BOARD_HEIGHT || field[newY][newX])
                        return true;
                }
            }
        }
        return false;
    }

    void lockTetromino() {
        const auto& shape = currentTetromino.getShape();
        int x = currentTetromino.getX();
        int y = currentTetromino.getY();

        for (size_t i = 0; i < shape.size(); i++) {
            for (size_t j = 0; j < shape[i].size(); j++) {
                if (shape[i][j]) {
                    field[y + i][x + j] = shape[i][j];
                }
            }
        }
    }

    void clearLines() {
        for (int i = 0; i < BOARD_HEIGHT; ++i) {
            bool fullLine = true;
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                if (field[i][j] == 0) {
                    fullLine = false;
                    break;
                }
            }

            if (fullLine) {
                field.erase(field.begin() + i);
                field.insert(field.begin(), std::vector<int>(BOARD_WIDTH, 0));
                score += 100;
            }
        }
    }
};

int main() {
    TetrisGame game;
    game.run();
    return 0;
}
