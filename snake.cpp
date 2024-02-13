#include <iostream>
#include <conio.h> //console input/output
#include <windows.h>

#include "engine.h"

using namespace std;

int main(){
    extern bool gameOver;
    extern bool pause;
    extern int curScore;

    bool playing = true;
    int highScore = 0;
    //Will make cout much faster
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    // system("MODE con cols=100 lines=100");

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
                // system("pause");
                // pause = false;
            }
            Sleep(100); //sleep in milliseconds to slow game down
        }
        cout << "Score: " << curScore << endl;
        cout << "Play again? Press y for yes or q for quit" << endl;
        
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

        highScore = curScore > highScore ? curScore : highScore;
    }
    
    cout << "\nYour high score: " << highScore << endl
         << "Shutting down...";

    return 0;
}