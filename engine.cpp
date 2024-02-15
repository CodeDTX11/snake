#include <iostream>
#include <conio.h> //console input/output
#include <time.h>
// #include <deque>

#include "engine.h"

using namespace std;

#define WIDTH 40
#define HEIGHT 20

bool gameOver, pause, quit;

const int displayWidth = WIDTH;
const int displayHeight = HEIGHT;

pair<int,int> head;
pair<int,int> tail;
int curScore;

char mode;

char hd = '0'; //snake head display
char bd = 'o'; //snake body display
char ms = '@'; //mouse display

enum direction {LEFT, RIGHT, UP, DOWN, STOP} dir;
// direction dir; //direction the snake moves in

pair<int,int> moveMnt[] = {{-1,0}, {1,0}, {0,-1}, {0,1}, {0,0}}; // used for snake movement

pair<char, direction> grid[HEIGHT][WIDTH] = {}; // game board grid

pair<int,int> operator +=(pair<int,int> &a, pair<int,int> &b) { // overload operator for pair
    // return {a.first + b.first, a.second + b.second};
    a.first = a.first + b.first;
    a.second = a.second + b.second;
}
pair<int,int> operator +(pair<int,int> &a, pair<int,int> &b) { // overload op for pair
    return {a.first + b.first, a.second + b.second};
}

void setup(){ //set up initial snake and mouse location on gamed display
    gameOver = false;
    quit = false;
    pause = false;
    srand(time(0));

    for(int row = 0; row < HEIGHT; row++){ // initialize grid with spaces
        for(int col = 0; col < WIDTH; col++){
            grid[row][col].first = ' ';
        }
    }

    head = {displayWidth/2, displayHeight/2}; // retain snake head for processing
    tail = {head.first, head.second}; // start out tail pointer/coordinates same as head

    grid[head.second][head.first].first = hd;// seed snake head

    grid[rand() % displayHeight][rand() % displayWidth].first = ms; // seed mouse

    curScore = 0;
    dir = STOP;
}

void grid_prnt(){
    
    system("cls"); // clears ouput of previous draw

    for(int i = 0; i < WIDTH + 2; i++){
        cout << "=";
    }
    cout << endl;

    for(int row = 0; row < HEIGHT; row++){
        cout << '|';
        for(int col = 0; col < WIDTH; col++){
            cout << grid[row][col].first;
        }
        cout << '|' << endl;
    }
    for(int i = 0; i < WIDTH + 2; i++){
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
            case 'q': // q to quit
            case 'Q':
                quit = true;
                break;
            case 'P': //p for pause
            case 'p':
                pause = true;
                break;
            default:
                break;
        }
    }
}

void logic () {
    if(dir != STOP){
        // pair<int,int> tail = {head.first, head.second}; 

        grid[head.second][head.first] = {bd, dir};
        
        switch (dir) { //snake head advances under current direction
            case LEFT:
                --head.first;
                break;
            case RIGHT:
                ++head.first;
                break;
            case UP:
                --head.second;
                break;
            case DOWN:
                ++head.second;
                break;
            default:
                break;
        }

        bool snakeExtend = false;
        if (grid[head.second][head.first].first == ms) { //logic when snake eats the mouse
            
            ++curScore;

            grid[rand() % displayHeight][rand() % displayWidth].first = ms; // mouse

            snakeExtend = true; // if mouse is eaten then the snake will grow/extend
        }

        if(mode == '1'){
            //check if snake head hits out of bounds (harder)
            if(head.first < 0 || head.first == displayWidth  || head.second < 0 || head.second == displayHeight ){ 
                gameOver = true;
                grid[head.second][head.first].first = 'X';
                cout << "\nOut of bounds" << endl;
            }
        } else {
            //alternatively the code below wraps the snake around borders instead of hitting out of bounds (easier)
            if(head.first < 0) {
                head.first = displayWidth - 1;
            } else if (head.first == displayWidth ){
                // gameOver = true;
                head.first = 0;
            } else if (head.second < 0){
                head.second = displayHeight - 1;
            } else if (head.second >= displayHeight){ 
                head.second = 0;
            }
        }
        
        if(snakeExtend == false){  // advance tail pointer/coordinates if extend did not occur
            direction tailDirection = grid[tail.second][tail.first].second;
            
            grid[tail.second][tail.first].first = ' ';
            grid[tail.second][tail.first].second = {STOP};

            // tail = tail + moveMnt[tailDirection];
            tail += moveMnt[tailDirection];

            if(mode == '2'){ // check for snake tail wrapping around while following head
                if(tail.first < 0) {
                    tail.first = displayWidth - 1;
                } else if (tail.first == displayWidth ){
                    tail.first = 0;
                } else if (tail.second < 0){
                    tail.second = displayHeight - 1;
                } else if (tail.second >= displayHeight){ 
                    tail.second = 0;
                }
            }
        } // if extend did occur then tail pointer remains the same

        if (grid[head.second][head.first].first == bd){ // check for snake eating self
            gameOver = true;
            grid[head.second][head.first].first = 'X';
            cout << "\nYou bit yourself" << endl;
        }

        grid[head.second][head.first].first = hd; // reasign head display value
    }
}