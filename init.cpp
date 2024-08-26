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

// when the main thread is OK to continue
mutex startSceneLock;
condition_variable startSceneCV;
bool startSceneOver = false;

// targeting what thread to run
short targetThread = 0;
short UITarget = 0; // 0 means void since UserInput has no UI
// 0 = UserInput
// 1 = StartScene
bool willGetUserInput = true;

// NOTE: thread start and thread destroy MUST be IN PAIR in the main function

int main()
{
    thread getUserInputThread(&getUserInput);

    // Start the game: run the startScene
    UITarget = 1;
    thread startSceneThread(&startSceneMainLoop);
    this_thread::sleep_for(chrono::milliseconds(500));
    {
        unique_lock<std::mutex> mainLock(startSceneLock);
        startSceneCV.wait(mainLock, [] { return startSceneOver; });
        startSceneThread.join();
    }

    getUserInputThread.join();

    return 0;
}