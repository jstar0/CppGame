#include <iostream>
// ... thread started here
#include <thread>
#include <condition_variable>
#include <mutex>
// ... thread ended here

// ... import self-defined headers
#include "console.h"
#include "gamemap.h"
#include "getUserInput.h"
#include "startScene.h"
// ... import self-defined headers ended

using namespace std;

// when the screen is ready to output
mutex screenOutputLock;
condition_variable screenOutputCV;
bool screenOutputReady = true;

// when the startScene is running
mutex startSceneLock;

// targeting what thread to run
short targetThread = 0;
short UITarget = 0; // 0 means void since UserInput has no UI
// 0 = UserInput
// 1 = StartScene

// when getUserInput is needed
bool willGetUserInput = true;

// when exit is triggered
bool willExit = false;

// NOTE: thread start and thread destroy MUST be IN PAIR in the main function

int main()
{
    // disable cursor
    setcursor(false);

    thread getUserInputThread(&getUserInput);

    // ==== Start the game: run the startScene ====
    UITarget = 1;
    targetThread = 1;
    // We MUST to set it everytime you start a new scene
    thread startSceneThread(&startSceneMainLoop);
    this_thread::sleep_for(chrono::milliseconds(500));
    {
        unique_lock<std::mutex> mainLock(startSceneLock);
        startSceneThread.join();
    }
    if(willExit)
    {
        getUserInputThread.join();
        return 0;
    }
    // ==== startScene ends here ====

    // 

    getUserInputThread.join();



    return 0;
}