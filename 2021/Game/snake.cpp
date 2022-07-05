#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>



using namespace std;


int n = 150;
bool gameOver;
const int width = 20;
const int height = 20;
int headX, headY, fruitX, fruitY, score;
int tailX[400], tailY[400], tail;
enum direction {STOP, LEFT, RIGHT, UP, DOWN};
direction dir;

void Setup() {
    headX = width / 2;
    headY = height / 2;
    fruitX = rand() % (width - 2);
    fruitY = rand() % (height - 2);
    score = 0;
}

void setcur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};


void Map() {
    setcur(0, 0);
    cout << "      Welcome to the game SNAKE" << endl;
    cout << "               Control" << endl << "w - UP; s - DOWN; a - LEFT; d - RIGHT" << endl;
    for (int i = 0; i < width + 1; i++)
        cout << "_";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width -1)
                cout << "|";
            if (i == headY && j == headX)
                cout << "0";
            else if (i == fruitY && j == fruitX)
                cout << "$";
            else {
               bool print = true;
                for (int k = 0; k < tail; k++) {
                    if (tailX[k] == j && tailY[k] == i) { 
                        print = false;
                        cout << "o";
                    }
                }
                if (print)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0 ; i <= width; i++)
        cout << "#";
    cout << endl;
    cout << "score: " << score << endl;
   
}

void Movement() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':

            if (dir != RIGHT)
                dir = LEFT;
            break;

        case 'd':

            if (dir != LEFT)
                dir = RIGHT;
            break;

        case 'w':
            if (dir != DOWN)
                dir = UP;
            break;

        case 's':
            if (dir != UP)
                dir = DOWN;
            break;

        }

    }
}



void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = headX;
    tailY[0] = headY;
    for (int i = 1; i <= tail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    }

    if (headX > width - 2 || headX < 0 || headY > height - 1 || headY < 0) 
            gameOver = true;
 
    for (int i = 1; i < tail; i++) {
        if (tailX[i] == headX && tailY[i] == headY)
            gameOver = true;
    }
    for (int i = 1; i < tail; i++) {
        if (tailX[i] == fruitX && tailY[i] == fruitY) {
            fruitX = rand() % (width - 2);
            fruitY = rand() % (height - 2);
           
        }
    }
    if (headX == fruitX && headY == fruitY ) {
            score++;
            fruitX = rand() % (width-2);
            fruitY = rand() % (height-2);
            tail ++;
            if (tail >= width * height) {
                gameOver = true;
                cout << "You WON!!!" << endl;
            }
            if (n > 10) 
                n = n - 2;
        }
    
   
}


int main() {
    srand(time(0));
    Setup();
    while (!gameOver) {
        Sleep(n);
        Map();
        Movement();
        Logic();       
    }
   // system("cls");
   // cout << "score: " << score << endl;
    cout << "GAMEOVER" << endl;
    system("pause");
    return 0;
}
