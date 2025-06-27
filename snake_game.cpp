#include <iostream>
#include <conio.h>     // For _kbhit() and _getch()
#include <windows.h>   // For Sleep()

using namespace std;

// Game dimensions
const int width = 20;
const int height = 20;

// Game state
int x, y, foodX, foodY, score;
int tailX[100], tailY[100];
int nTail;
bool gameOver;

// Directions
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

// Setup function
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    foodX = rand() % width;
    foodY = rand() % height;
    score = 0;
    nTail = 0;
}

// Draw the game
void Draw() {
    system("cls");

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";

            if (i == y && j == x)
                cout << "O";
            else if (i == foodY && j == foodX)
                cout << "F";
            else {
                bool printed = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        printed = true;
                        break;
                    }
                }
                if (!printed)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}

// Handle input
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

// Game logic
void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT: x--; break;
    case RIGHT: x++; break;
    case UP: y--; break;
    case DOWN: y++; break;
    default: break;
    }

    if (x < 0 || x >= width || y < 0 || y >= height)
        gameOver = true;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    if (x == foodX && y == foodY) {
        score += 10;
        foodX = rand() % width;
        foodY = rand() % height;
        nTail++;
    }
}

// Wait for 's' to start the game
void ShowStartMenu() {
    system("cls");
    cout << "=========================" << endl;
    cout << "     SNAKE GAME (C++)    " << endl;
    cout << "=========================" << endl;
    cout << " Press 's' to Start Game " << endl;
    cout << " Use W A S D to move     " << endl;
    cout << " Press 'x' to Exit Game  " << endl;
    cout << "=========================" << endl;

    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 's' || ch == 'S')
                break;
        }
    }
}

int main() {
    ShowStartMenu();
    Setup();

    int frameCount = 0;
    int maxFrames = 10000;

    while (!gameOver && frameCount < maxFrames) {
        Draw();
        Input();
        Logic();
        Sleep(100);
        frameCount++;
    }

    cout << "\nGame Over! Final Score: " << score << endl;
    return 0;
}
