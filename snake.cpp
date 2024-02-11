#include <iostream>
#include <conio.h> //console input/output
#include <windows.h>
#include <time.h>
using namespace std;

bool gameOver;
const int displayWidth = 40;
const int displayHeight = 20;

int snakeHeadX, snakeHeadY, mouseX, mouseY, score;
int tailX[100], tailY[100];
int nTail;

enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN};
direction dir; //direction the snake moves in

void Setup(){ //set up initial snake and mouse location on gamed display
    gameOver = false;
    snakeHeadX = displayWidth/2;
    snakeHeadY = displayHeight/2;
    mouseX = rand() % displayWidth;
    mouseY = rand() % displayHeight;
    score = 0;
}

void Draw(){ // print to scree 2d matrix display for game
   
    system("cls"); // clears ouput
    cout << endl;
    // cout << " ";
    for(int i = 0; i < displayWidth + 2; i++){
        cout << "=";
    }
    cout << endl;
    
    for (int row = 0; row < displayHeight; row++) {
        cout << "|";
        for (int col = 0; col < displayWidth; col++) {

            if (row == snakeHeadY && col == snakeHeadX){
                cout << "0";
            } else if (row == mouseY && col == mouseX){
                cout << "@";
            } else {
                bool print = false;
                cout << " ";
                // for (int k = 0; k < nTail; k++)
                // {
                //     if (tailX[k] == j && tailY[k] == i)
                //     {
                //         cout << "*";
                //         print = true;
                //     }
                // }
                // if (!print)
                //     cout << " ";
            }
        }
        cout << "|" << endl;
    }
    // cout << " ";
    for(int i = 0; i < displayWidth + 2; i++){
        cout << "=";
    }
    cout << endl;
}
void Input() {

    if (_kbhit()) { //keyboard hit, returns boolean if keyboard pressed
    
        switch (_getch()) { //get char from keyboard if pressed
            case 'a':
            case 'A':
                dir = LEFT;
                break;
            case 'd':
            case 'D':
                dir = RIGHT;
                break;
            case 'w':
            case 'W':
                dir = UP;
                break;
            case 's':
            case 'S':
                dir = DOWN;
                break;
            case 'x':
            case 'X':
                gameOver = true;
                break;
            default:
                break;
        }
    }
}

int main(){

    Setup();
    Draw();
    Sleep(500); //sleep in milliseconds

    cout << " Your final score:" << score << endl;
    return 0;
}