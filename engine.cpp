#include <iostream>
#include <conio.h> //console input/output
#include <time.h>
#include <deque>

#include "engine.h"

using namespace std;

#define WIDTH 40
#define HEIGHT 20

bool gameOver, pause, quit;

const int displayWidth = WIDTH;
const int displayHeight = HEIGHT;

pair<int,int> head;
int curScore;

char mode;

char hd = '0'; //snake head display
char bd = 'o'; //snake body display
char ms = '@'; //mouse display

// deque<pair<int,int>> snake;

enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN} dir;
// direction dir; //direction the snake moves in

char grid[HEIGHT][WIDTH] = {};

void setup(){ //set up initial snake and mouse location on gamed display
    gameOver = false;
    quit = false;
    pause = false;
    // snake.clear();
    srand(time(0));
    // snake.push_front({displayWidth/2, displayHeight/2}); // initiate head of snake

    for(int row = 0; row < HEIGHT; row++){
        for(int col = 0; col < WIDTH; col++){
            grid[row][col] = ' ';
        }
    }

    head = {displayWidth/2, displayHeight/2}; // retain snake head for processing

    grid[head.second][head.first] = hd;// seed snake head

    // mouseX = rand() % displayWidth;
    // mouseY = rand() % displayHeight;

    grid[rand() % displayHeight][rand() % displayWidth] = ms; // seed mouse

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
            cout << grid[row][col];
        }
        cout << '|' << endl;
    }
    for(int i = 0; i < WIDTH + 2; i++){
        cout << "=";
    }
    cout << endl;
}

// void draw(){ // print 2d game display
   
//     system("cls"); // clears ouput of previous draw
//     cout << endl;
    
//     for(int i = 0; i < displayWidth + 2; i++){
//         cout << "=";
//     }
//     cout << endl;
//     int snakePrint = 0; // reset for each draw
//     for (int row = 0; row < displayHeight; row++) {
//         cout << "|";

//         for (int col = 0; col < displayWidth; col++) {

//             if (row == mouseY && col == mouseX){
//                 cout << "@";
//             } else if (snakePrint < snake.size()) { // checks if tail needs to be printed
                
//                 int i = 0;
//                 for ( ; i < snake.size(); i++) { // iterate through snake to see if needs printing
//                     if (snake[i].first == col && snake[i].second == row) { 
//                         if(i == 0){
//                             cout << "0";
//                         } else {
//                             cout << "o";
//                         }
//                         ++snakePrint;
//                         break; // break out of loop once snake found for particular grid location
//                     } 
//                 }
//                 if (i == snake.size()){ // if tail not printed, print space for grid
//                     cout << " ";
//                 }
//             } else { 
//                 cout << " ";
//             }
//         }
//         cout << "|" << endl;
//     }
//     for(int i = 0; i < displayWidth + 2; i++){
//         cout << "=";
//     }
//     cout << endl;
// }

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

    pair<int,int> tail = {head.first, head.second}; 
    
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
    if (grid[head.second][head.first] == ms) { //logic when snake eats the mouse
        // srand(time(0)); // Random seed value for rand based on time
        
        // grid[head.second][head.first] = hd; // replace ? TODO
        
        ++curScore;

        grid[rand() % displayHeight][rand() % displayWidth] = ms; // mouse

        // mouseX = rand() % displayWidth;
        // mouseY = rand() % displayHeight;
        
        snakeExtend = true; // if mouse is eaten then the snake will grow/extend
    }
    
    // pair<int,int> snakeHead = snake.front(); // create new snakehead variable


    // if(snake.size() > 1 && snake[1] == snakeHead){ // check for snake eating self
    //     gameOver = true;
    //     cout << "\nCollison occured" << endl;
    // }

    // snake.push_front(snakeHead); //deque for snake, push current head position onto dq

    // if(snakeExtend == false){
    //     snake.pop_back(); //pop back if snake not extended to simulate snake advancing
    //     // if snake does extend, do not pop back since that is where the snake grows
    // } 

    if(mode == '1'){
        //check if snake head hits out of bounds (harder)
        if(head.first < 0 || head.first == displayWidth  || head.second < 0 || head.second == displayHeight ){ 
            gameOver = true;
            grid[head.second][head.first] = 'X';
            cout << "\nOut of bounds" << endl;
        }
    } else {
        //alternatively the code below wraps the snake around borders instead of hitting out of bounds (easier)
        if(head.first < 0){
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

    if (grid[head.second][head.first] == bd){ // check for snake eating self TODO
        gameOver = true;
        grid[head.second][head.first] = 'X';
        cout << "\nYou bit yourself" << endl;
    }
    
    
    if(snakeExtend == false){
        grid[tail.second][tail.first] = ' ';
    }
    grid[head.second][head.first] = hd;
}