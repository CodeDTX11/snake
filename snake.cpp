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

void setup(){ //set up initial snake and mouse location on gamed display
    gameOver = false;
    snakeHeadX = displayWidth/2;
    snakeHeadY = displayHeight/2;
    mouseX = rand() % displayWidth;
    mouseY = rand() % displayHeight;
    score = 0;
    dir = STOP;
}

void draw(){ // print 2d game display
   
    system("cls"); // clears ouput
    cout << endl;
    // cout << " ";
    for(int i = 0; i < displayWidth + 2; i++){
        cout << "=";
    }
    cout << endl;
    int tailPrint = 0;
    for (int row = 0; row < displayHeight; row++) {
        cout << "|";

        for (int col = 0; col < displayWidth; col++) {

            if (row == snakeHeadY && col == snakeHeadX){
                cout << "0";
            } else if (row == mouseY && col == mouseX){
                cout << "@";
            } else if(tailPrint < nTail){ // checks if tail needs to be printed
                int i = 0;
                for ( ; i < nTail; i++) { // iterate through tail to see if needs printing

                    if (tailX[i] == col && tailY[i] == row) { // print tail
                        cout << "o";
                        ++tailPrint;
                        break;
                    } 
                }
                if (i == nTail){ // if tail not printed, print space for grid
                    cout << " ";
                }
            } else { 
                cout << " ";
            }
        }
        cout << "|" << endl;
    }

    for(int i = 0; i < displayWidth + 2; i++){
        cout << "=";
    }
    cout << endl;
}
void input() {

    if (_kbhit()) { //keyboard hit, returns boolean if keyboard pressed
    // enter is not needed for user input
    
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
void logic () {

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = snakeHeadX;
    tailY[0] = snakeHeadY;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT:
            --snakeHeadX;
            break;
        case RIGHT:
            ++snakeHeadX;
            break;
        case UP:
            --snakeHeadY;
            break;
        case DOWN:
            ++snakeHeadY;
            break;
        default:
            break;
    }
    //check for out of bounds
    if(snakeHeadX < 0 || snakeHeadX >= displayWidth || snakeHeadY < 0 || snakeHeadY >= displayHeight){ 
        gameOver = true;
    }
    
    // for (int i = 0; i < nTail; i++){ // check for snake eating self
    //     if (snakeHeadX == tailX[i] && snakeHeadY == tailY[i]){
    //         gameOver = true;
    //     }
    // }

    if (snakeHeadX == mouseX && snakeHeadY == mouseY) { //logic when snake eats the mouse
        srand(time(0)); // Random seed value for rand based on time
        ++score;
        mouseX = rand() % displayWidth;
        mouseY = rand() % displayHeight;
        ++nTail;
    }
}

int main(){
    bool playing = true;
    //Will make cout much faster
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    system("MODE con cols=60 lines=25");

    while(playing){
        setup();

        while(!gameOver){
            draw();
            input();
            logic();
            Sleep(100); //sleep in milliseconds
        }
        cout << "Your final score: " << score << endl;
        cout << "Play again? Press y for yes or anything else for no" << endl;
        
        char ans;
        cin >> ans;

        if(!(ans == 'y' || ans == 'Y')) {
            playing = false;
        }
    }

    cout << "Shutting down...";
    return 0;
}