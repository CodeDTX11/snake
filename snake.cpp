#include <iostream>
#include <conio.h> //console input/output
#include <windows.h>
#include <time.h>
#include <deque>
using namespace std;

bool gameOver;
const int displayWidth = 40;
const int displayHeight = 20;

int snakeHeadX, snakeHeadY, mouseX, mouseY, score;
int tailX[100], tailY[100];
int nTail;

deque<pair<int,int>> snakeTail;

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
                auto tailItr = snakeTail.begin();
                
                for ( ; tailItr != snakeTail.end(); ++tailItr) { // iterate through tail to see if needs printing
    
                    if (tailItr->first == col && (*tailItr).second == row) { // print tail
                        cout << "o";
                        ++tailPrint;
                        break; // break out of loop once tail found for particular grid location
                    } 
                }
                if (tailItr == snakeTail.end()){ // if tail not printed, print space for grid
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

    bool snakeExtend = false;
    if (snakeHeadX == mouseX && snakeHeadY == mouseY) { //logic when snake eats the mouse
        srand(time(0)); // Random seed value for rand based on time
        ++score;
        mouseX = rand() % displayWidth;
        mouseY = rand() % displayHeight;
        ++nTail;
        snakeExtend = true;
    }


    if(nTail){
        snakeTail.push_front({snakeHeadX, snakeHeadY});

        if(snakeExtend == false){
            snakeTail.pop_back();
        }
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
    
    for (auto& tailItr : snakeTail){ // check for snake eating self
        if (snakeHeadX == tailItr.first && snakeHeadY == tailItr.second){
            gameOver = true;
            break;
        }
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
        
        char resp; // user response
        cin >> resp;

        if(!(resp == 'y' || resp == 'Y')) {
            playing = false;
        }
    }

    cout << "Shutting down...";
    return 0;
}