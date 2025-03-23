
#include <stdexcept>
#include <sys/ptrace.h 
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <unordered_map>
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


class detection {
    public: 
    detection(); 
    ~detection(); 

    virtual pid_t* whoIsActive()
    { 

        
    }

    bool isProcessRunning(pid_t pid)
    { 
        if(ptrace(PTRACE_ATTACH, pid, nullptr, nullptr) == -1)
        {
            if(errno == ESRCH)
            {
                return false; 
            }
            else if (errno == EPERM)
            { 
                return true; 
            }
            else{
                perror("ptrace attach"); 
                return false; 
            }
        }

        int status; 
        waitpid(pid, &status, 0); 
        ptrace(PTRACE_DETACH, pid, nullptr, nullptr); 

        return true; 
    }
    private: 
    pid_t process;
    int status; 
    std::string nameOfProcees;  
    detection* left; 
    detection* right; 

}


class stageDetect : detection
{
    public: 


}


class department : detection
{

}