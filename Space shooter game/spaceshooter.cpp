#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;

bool gameOver;
int x, y;
int bulletX, bulletY;
int enemyX, enemyY;
int score;

void Setup() {
    gameOver = false;
    x = WIDTH / 2;
    y = HEIGHT - 1;
    bulletX = -1;
    bulletY = -1;
    enemyX = rand() % WIDTH;
    enemyY = 0;
    score = 0;
}

void Draw() {
    system("cls");
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "A";
            else if (i == bulletY && j == bulletX)
                cout << "|";
            else if (i == enemyY && j == enemyX)
                cout << "E";
            else
                cout << " ";
            if (j == WIDTH - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                if (x > 0)
                    x--;
                break;
            case 'd':
                if (x < WIDTH - 1)
                    x++;
                break;
            case ' ':
                if (bulletY == -1)
                    bulletX = x;
                    bulletY = y - 1;
                break;
            case 'q':
                gameOver = true;
                break;
        }
    }
}

void Logic() {
    if (bulletY >= 0) {
        bulletY--;
        if (bulletY == enemyY && bulletX == enemyX) {
            score++;
            bulletY = -1;
            enemyX = rand() % WIDTH;
            enemyY = 0;
        }
        else if (bulletY < 0)
            bulletY = -1;
    }

    if (enemyY < HEIGHT) {
        enemyY++;
        if (enemyY == y && enemyX == x)
            gameOver = true;
    }
    else {
        enemyX = rand() % WIDTH;
        enemyY = 0;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    cout << "Game Over!" << endl;
    cout << "Your score: " << score << endl;
    return 0;
}
