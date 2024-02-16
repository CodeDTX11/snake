#include <iostream>
#include <conio.h> //console input/output
#include <windows.h>

#include "engine.h"

using namespace std;

int main(){
    extern bool gameOver;
    extern bool pause;
    extern int curScore;
    extern char mode;
    extern bool quit;

    bool playing = true;
    int highScore = 0;
    //Will make cout much faster

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    // system("MODE con cols=100 lines=100");

    cout << "\nWelcome to classic snake\n\n"
         << "Enter [1] for Strict border mode\n"
         << "Enter [2] for wrap-around mode\n"
         << "Enter [q] to quit" << endl;
    
    mode = _getch();
    while(!(mode == '1' || mode == '2' || mode == 'q')){
        cout << "Enter [1], [2] or [q]" << endl;
        mode = _getch();
    }

    if(mode == '1'){
        cout << "\nStrict border mode activated" << endl;
    } else if (mode == '2') {
        cout << "\nWrap-around mode activated" << endl;
    } else {
        cout << "\nShutting down...." << endl << endl;
        return 0;
    }

    cout << "\nStarting game.." << endl;
    Sleep(1000);
    // cout << "2.." << endl;
    // Sleep(1000);
    // cout << "1.." << endl;
    // Sleep(1000);

    while(playing){

        setup();

        while(gameOver == false) {
            if(quit){
                cout << "Are you sure you want to quit?\n" 
                     << "[q] to quit / [n] to resume" << endl;
                
                char ans = _getch();
                while(!(ans == 'q' || ans == 'n')){
                    cout << "\n[q] to quit / [n] to resume" << endl;
                    ans = _getch();
                }
                if(ans == 'q'){
                    break;
                } else {
                    cout << "\nResuming game..." << endl;
                    Sleep(1000);
                    quit = false;
                }

            }
            grid_prnt();
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
                    cout << "\nGame unpaused..." << endl;
                    pause = false;
                    Sleep(1000);
                }
                // system("pause");
                // pause = false;
            }
            Sleep(100); //sleep in milliseconds to slow game down
        }

        cout << "\nScore: " << curScore << endl;
        cout << "Play again? [y] for yes / [q] to exit game" << endl;
        
        char resp = _getch();
        while(!(resp == 'y' || resp == 'q')){
            Sleep(100);
            resp = _getch();
        }
        if(resp == 'q'){
            playing = false;
        } else {
            cout << "\nSelect game mode...\n"
                 << "[1] for strict border mode\n"
                 << "[2] for wrap-around mode" << endl;

            mode = _getch();
            while(!(mode == '1' || mode == '2')){
                cout << "Enter [1] or [2]" << endl;
                mode = _getch();
            }

            if(mode == '1'){
                cout << "\nStrict border mode activated\n";
            } else {
                cout << "\nWrap-around mode activated\n";
            }
            cout << "\nStarting new game..." << endl;
            Sleep(1000);
        }

        highScore = curScore > highScore ? curScore : highScore;
    }
    
    cout << "\nYour high score: " << highScore << endl
         << "Shutting down..." << endl << endl;

    return 0;
}