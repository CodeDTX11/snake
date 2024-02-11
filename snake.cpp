#include <iostream>
#include <conio.h> //console input/output
#include <windows.h>
#include <time.h>
#include <deque>
using namespace std;

bool gameOver;
bool pause;
const int displayWidth = 40;
const int displayHeight = 20;

int snakeHeadX, snakeHeadY, mouseX, mouseY, curScore;
int nTail;

deque<pair<int,int>> snakeTail;

enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN};
direction dir; //direction the snake moves in

void setup(){ //set up initial snake and mouse location on gamed display
    gameOver = false;
    pause = false;
    nTail = 0;
    snakeHeadX = displayWidth/2;
    snakeHeadY = displayHeight/2;
    mouseX = rand() % displayWidth;
    mouseY = rand() % displayHeight;
    curScore = 0;
    dir = STOP;
    snakeTail.clear();
}

void draw(){ // print 2d game display
   
    system("cls"); // clears ouput of previous draw
    cout << endl;
    // cout << " ";
    for(int i = 0; i < displayWidth + 2; i++){
        cout << "=";
    }
    cout << endl;
    int tailPrint = 0; // reset for each draw
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
            case 'q': // q to quit
            case 'Q':
                gameOver = true;
                break;
            case 'P':
            case 'p':
                pause = true;
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
        ++curScore;
        mouseX = rand() % displayWidth;
        mouseY = rand() % displayHeight;
        ++nTail;
        snakeExtend = true; // if mouse is eaten then the snake will grow/extend
    }


    if(nTail){
        snakeTail.push_front({snakeHeadX, snakeHeadY}); //deque for snake tail, push current head position onto dq

        if(snakeExtend == false){
            snakeTail.pop_back(); //pop back if snake not extended to simulate snake advancing
        }
        // if snake does extend do not pop back since that is where the snake grows
    }

    switch (dir) { //snake head advances under current direction
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
    int highScore = 0;
    //Will make cout much faster
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    system("MODE con cols=60 lines=45");

    while(playing){
        setup();

        while(gameOver == false){
            draw();
            input();
            logic();
            Sleep(100); //sleep in milliseconds
            if(pause){
                cout << "Game paused...\n"
                     << "Current score: " << curScore << endl
                     << "Press p to unpause or q to quit" << endl;

                char in = _getch();
                while(!(in == 'p' || in == 'P' || in == 'q' || in == 'Q')){
                    Sleep(500);
                }

                if(in == 'q' || in == 'Q'){
                    gameOver = true;
                } else {
                    if(in == 'p')
                        cout << "Game unpaused...";
                    pause = false;
                }
                Sleep(1000);
            }
        }
        cout << "Score: " << curScore << endl;
        cout << "Play again? Press y for yes or anything else for no" << endl;
        
        highScore = curScore > highScore ? curScore : highScore;

        char resp = _getch();
        // cin >> resp;
        if(!(resp == 'y' || resp == 'Y')) {
            playing = false;
        }
    }

    cout << "\nYour high score: " << highScore << endl
         << "Shutting down...";
         
    return 0;
}