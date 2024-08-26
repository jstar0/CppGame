#include <conio.h>
#include "getUserInput.h"

// ... thread started here
#include <thread>
// ... thread ended here

using namespace std;

// targeting what thread to run
extern short targetThread, UITarget;

// when the screen is changed and need to be updated
extern bool screenChanged;

// when getUserInput is needed
extern bool willGetUserInput;

void getUserInput()
{
    while(willGetUserInput)
    {
        char playerInput = getch();
        if(UITarget == 0);
        else if(UITarget == 1)
        {
            extern short startSceneChoice;
            extern bool isSelected;
            if(playerInput == 'w' || playerInput == 'W')
            {
                if(startSceneChoice == 0)
                {
                    startSceneChoice = 3;
                }
                else
                {
                    startSceneChoice--;
                }
            }
            else if(playerInput == 's' || playerInput == 'S')
            {
                if(startSceneChoice == 3)
                {
                    startSceneChoice = 0;
                }
                else
                {
                    startSceneChoice++;
                }
            }
            else if(playerInput == 'e' || playerInput == 'E')
            {
                isSelected = true;
            }
        }
        else if (UITarget == 2)
        {
            if(playerInput == 'w' || playerInput == 'W')
            {

            }
            else if(playerInput == 's' || playerInput == 'S')
            {

            }
            else if(playerInput == 'e' || playerInput == 'E')
            {

            }
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}