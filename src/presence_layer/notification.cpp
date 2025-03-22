
#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <sys/ptrace.h 
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <unordered_map>

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
