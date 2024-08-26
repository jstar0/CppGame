#include <string>

// ... thread started here
#include <thread>
#include <condition_variable>
#include <mutex>
// ... thread ended here

#include "startScene.h"
#include "console.h"

// when the screen is ready to output
extern mutex screenOutputLock;
extern condition_variable screenOutputCV;
extern bool screenOutputReady;

// when the startScene is ready to run
extern mutex startSceneLock;

extern short targetThread;

short startSceneChoice = 0;
bool isSelected = false;

void startSceneMainLoop()
{
    unique_lock<std::mutex> screenThreadLock(startSceneLock);
    unique_lock<std::mutex> screenOutput(screenOutputLock);
    screenOutputCV.wait(screenOutput, [] { return screenOutputReady && targetThread == 1; });
    setcolor(6, 0);
    print("Welcome to the game!", 0, 0);
    while(!isSelected)
    {
        if(startSceneChoice == 0)
            setcolor(15, 14);
        else
            setcolor(15, 0);
        print("开始游戏", 0, 2);
        if(startSceneChoice == 1)
            setcolor(15, 14);
        else
            setcolor(15, 0);
        print("读取存档", 0, 4);
        if(startSceneChoice == 2)
            setcolor(15, 14);
        else
            setcolor(15, 0);
        print("多人游戏", 0, 6);
        if(startSceneChoice == 3)
            setcolor(15, 14);
        else
            setcolor(15, 0);
        print("退出游戏", 0, 8);
    }
    if(startSceneChoice == 0)
    {
        // start the game
    }
    else if(startSceneChoice == 1)
    {
        // load the game
    }
    else if(startSceneChoice == 2)
    {
        // start the multiplayer game
    }
    else if(startSceneChoice == 3)
    {
        // exit the game
    }
}