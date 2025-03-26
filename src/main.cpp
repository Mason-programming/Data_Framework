

#include <thread>
#include <mutex>
#include <chrono>
#include "notification.cpp"
#include "notification_ui.h"

void backgroundCheck(){ 

    running = isProcessRunning(); 

    if(running){ 


    }


}

int maim(){

    std::thread backgroundTask(backgroundCheck); 

    backgroundTask.detach(); 


    return 0; 
}