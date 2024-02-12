#include <iostream>
#include <conio.h> //console input/output
#include <windows.h>
#include <time.h>
#include <deque>

#define WIDTH 40
#define HEIGHT 20

using namespace std;

bool gameOver;
bool pause;
const int displayWidth = WIDTH;
const int displayHeight = HEIGHT;

int mouseX, mouseY, curScore;
int nTail; // length of tail (number of tail segments)

deque<pair<int,int>> snake;

enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN};
direction dir; //direction the snake moves in

void setup(){ //set up initial snake and mouse location on gamed display
    gameOver = false;
    pause = false;
    nTail = 0;
    snake.clear();
    snake.push_front({displayWidth/2, displayHeight/2}); // initiate head of snake
    mouseX = rand() % displayWidth;
    mouseY = rand() % displayHeight;
    curScore = 0;
    dir = STOP;
}

void draw(){ // print 2d game display
   
    system("cls"); // clears ouput of previous draw
    cout << endl;
    
    for(int i = 0; i < displayWidth + 2; i++){
        cout << "=";
    }
    cout << endl;
    int snakePrint = 1; // reset for each draw
    for (int row = 0; row < displayHeight; row++) {
        cout << "|";

        for (int col = 0; col < displayWidth; col++) {

            if (row == mouseY && col == mouseX){
                cout << "@";
            }else if (snake[0].first == col && snake[0].second == row) { // print distinct head of snake
                cout << "O";
            } else if (snakePrint < snake.size()) { // checks if tail needs to be printed
                
                auto snakeItr = snake.begin();
                ++snakeItr; // advance iterator since head printed with code above
                for ( ; snakeItr != snake.end(); ++snakeItr) { // iterate through tail to see if needs printing
    
                    if (snakeItr->first == col && (*snakeItr).second == row) { // print tail
                        cout << "o";
                        ++snakePrint;
                        break; // break out of loop once tail found for particular grid location
                    } 
                }
                if (snakeItr == snake.end()){ // if tail not printed, print space for grid
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

    bool snakeExtend = false;
    if (snake[0].first == mouseX && snake[0].second == mouseY) { //logic when snake eats the mouse
        srand(time(0)); // Random seed value for rand based on time
        ++curScore;
        mouseX = rand() % displayWidth;
        mouseY = rand() % displayHeight;
        ++nTail;
        snakeExtend = true; // if mouse is eaten then the snake will grow/extend
    }
    
    pair<int,int> snakeHead = snake.front(); 

    switch (dir) { //snake head advances under current direction
        case LEFT:
            --snakeHead.first;
            break;
        case RIGHT:
            ++snakeHead.first;
            break;
        case UP:
            --snakeHead.second;
            break;
        case DOWN:
            ++snakeHead.second;
            break;
        default:
            break;
    }

    if(snake.size() > 1 && snake[1] == snakeHead){
        gameOver = true;
    }

    snake.push_front(snakeHead); //deque for snake tail, push current head position onto dq

    if(snakeExtend == false){
            // help
        snake.pop_back(); //pop back if snake not extended to simulate snake advancing
    }
        // if snake does extend, do not pop back since that is where the snake grows

    //check for out of bounds
    if(snake[0].first < 0 || snake[0].first >= displayWidth || snake[0].second < 0 || snake[0].second >= displayHeight){ 
        gameOver = true;
    }
    // if(nTail == 1 && neck == pair<int,int>(snakeHeadX,snakeHeadY) ) { 
    //     gameOver = true;
    // }
    for (int i = 1; i < snake.size(); i++){ // check for snake eating self
        if (snake[0].first == snake[i].first && snake[0].second == snake[i].second){
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

        while(gameOver == false) {
            draw();
            input();
            logic();
            if(pause){
                cout << "Game paused...\n"
                     << "Current score: " << curScore << endl
                     << "Press p to unpause or q to quit" << endl;

                char in = _getch();
                while(!(in == 'p' || in == 'P' || in == 'q' || in == 'Q')){
                    Sleep(250);
                    in = _getch();
                }

                if(in == 'q' || in == 'Q'){
                    gameOver = true;
                } else {
                    cout << "Game unpaused..." << endl;
                    pause = false;
                    Sleep(1000);
                }
            }
            Sleep(100); //sleep in milliseconds
        }
        cout << "Score: " << curScore << endl;
        cout << "Play again? Press y for yes or q for quit" << endl;
        
        highScore = curScore > highScore ? curScore : highScore;

        char resp = _getch();
        while(!(resp == 'y' || resp == 'q')){
            Sleep(100);
            resp = _getch();
        }
        if(resp == 'q'){
            playing = false;
        } else {
            cout << "Starting new game..." << endl;
            Sleep(1000);
        }
    }

    cout << "\nYour high score: " << highScore << endl
         << "Shutting down...";

    return 0;
}