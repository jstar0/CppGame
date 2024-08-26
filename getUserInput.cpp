#include <conio.h>
#include "getUserInput.h"
using namespace std;

extern bool willGetUserInput, startSceneOver;
extern short targetThread, UITarget;

void getUserInput()
{
    while(willGetUserInput)
    {
        char playerInput = getch();
        if(UITarget == 0);
        else if(UITarget == 1)
        {
            if(playerInput == 'w' || playerInput == 'W')
            {

            }
            else if(playerInput == 's' || playerInput == 'S')
            {

            }
            else if(playerInput == 'e' || playerInput == 'E')
            {


                startSceneOver = true;
            }
        }
    }
}