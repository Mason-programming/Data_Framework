

#include <stdexcept>
#include <sys/ptrace.h 
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <unordered_map>
#include <vector>
// Filled with helper methods
#include "notification.cpp"


struct process
{
    std::string processName; 
    int status; 
    int waitingTime; 
    int turnAroundTime; 
    int burstTime; 
}


void roundRobin(vector<process>& processes, int timeQuantum)
{ 
    int n = process.size(): 
    
}
