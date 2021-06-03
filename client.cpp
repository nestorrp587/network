#include <iostream>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[]) {
    std::cout << "Hola mundo\n";

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(10004);
    serv_addr.sin_addr.s_addr = inet_addr("10.26.104.187");

    sockaddr_in local_addr;
    memset(&local_addr, 0, sizeof(sockaddr_in));
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(10004);
    local_addr.sin_addr.s_addr = inet_addr("172.17.0.1");

    std::string message = "I am sending this message with my test app";

    if (bind(sockfd, (struct sockaddr *) &local_addr, sizeof(local_addr)) < 0) {
        std::cerr << "ERROR binding";
        exit(1);
    }

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "ERROR connecting";
        exit(1);
    }

    if (send(sockfd, message.c_str(), sizeof(message), 0) < 0) 
    {
        std::cerr << "send error\n";
        exit(1);
    }else{
        std::cout << "CLI: sent something...\n"; 
    }

    return 0;
}