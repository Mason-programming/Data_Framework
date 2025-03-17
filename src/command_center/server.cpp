#include <sys/server.h> 
#include <netinet/in.h> 
#include <cstdlib>
#include <iostream>


int main(){

    int sockfd = socket(AF_INET, SOCK_STREAM, 0); 

    if (sockfd == -1){ 
        std::cout << "Failed to create a socket" << std::endl; 
        exit(EXIT_FAILURE); 
    }

    sockaddr_in sockaddr; 

    sockaddr.sin_family = AF_INET; 
    sockaddr.sin_addr.s_addr = INADDR_ANY; 
    sockaddr.sin_port = htons(5556);              

    if (bind(sockfd, (struct sockaddr* ()))
}