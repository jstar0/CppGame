// ... thread started here
#include <thread>
#include <condition_variable>
#include <mutex>
// ... thread ended here

#include "startScene.h"
#include "console.h"

// when the startScene is ready to run
extern mutex startSceneLock;
extern condition_variable startSceneCV;

void startSceneMainLoop()
{
    
}