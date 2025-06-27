#include <iostream>
#include <vector>
#include <conio.h> // For _getch()
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;
struct Point {
    int x, y;
};

vector<vector<char>> grid(HEIGHT, vector<char>(WIDTH, '.'));
vector<Point> currentPiece;
int pieceX = WIDTH / 2, pieceY = 0;

void init() {
    srand(time(0));
    // Simple I-shaped tetromino (vertical)
    currentPiece = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
}

void draw() {
    system("cls"); // Clear screen
    vector<vector<char>> tempGrid = grid;
    for (Point p : currentPiece) {
        int x = pieceX + p.x;
        int y = pieceY + p.y;
        if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
            tempGrid[y][x] = 'O'; // Tetromino block
        }
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cout << tempGrid[i][j];
        }
        cout << endl;
    }
}

bool canMove(int newX, int newY) {
    for (Point p : currentPiece) {
        int x = newX + p.x;
        int y = newY + p.y;
        if (x < 0 || x >= WIDTH || y >= HEIGHT || (y >= 0 && grid[y][x] != '.')) {
            return false;
        }
    }
    return true;
}

void mergePiece() {
    for (Point p : currentPiece) {
        int x = pieceX + p.x;
        int y = pieceY + p.y;
        if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
            grid[y][x] = 'O';
        }
    }
}

void newPiece() {
    pieceX = WIDTH / 2;
    pieceY = 0;
    currentPiece = {{0, 0}, {1, 0}, {2, 0}, {3, 0}}; // New I-shaped piece
    if (!canMove(pieceX, pieceY)) {
        cout << "Game Over!\n";
        exit(0);
    }
}

int main() {
    init();
    while (true) {
        draw();
        if (_kbhit()) {
            char key = _getch();
            int newX = pieceX;
            if (key == 'a' && canMove(newX - 1, pieceY)) pieceX--; // Left
            else if (key == 'd' && canMove(newX + 1, pieceY)) pieceX++; // Right
        }
        if (canMove(pieceX, pieceY + 1)) {
            pieceY++;
        } else {
            mergePiece();
            newPiece();
        }
        // Simple delay for visibility
        for (int i = 0; i < 100000000; i++); // Basic delay
    }
    return 0;
}