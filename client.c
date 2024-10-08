#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 1024

void compile_request(FILE *fp, int sockfd, char *name)
{
    char data[SIZE] = {0};
    char header[SIZE] = "arduino:avr:mega:cpu=atmega2560"; // Board
    // Send header
    if (send(sockfd, header, sizeof(header), 0) != -1)
    {
        if (send(sockfd, data, sizeof(data), 0) != -1)
        {
            while (fgets(data, SIZE, fp) != NULL)
            {
                if (send(sockfd, data, sizeof(data), 0) == -1)
                {
                    perror("[-] Error in sending data chunk");
                    exit(1);
                }
                bzero(data, SIZE);
            }
        }
    }
}

void recieve_data_from_server(int sockfd){ 

}

int main()
{
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;

    int sockfd;
    struct sockaddr_in server_addr;
    FILE *fp;
    char *filename = "./TestProject/TestProject.ino";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created. \n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (e == -1)
    {
        perror("[-]Error in Connecting");
        exit(1);
    }
    printf("[+]Connected to server.\n");
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("[-]Error in reading file.");
        exit(1);
    }
    compile_request(fp, sockfd);
    printf("[+] File data send successfully. \n");
    
    // Listen to binary
    // TODO; Move to recieve_data_from_server and separate thread
    // char buffer[SIZE];
    // int n;
    // n = recv(sockfd, buffer, SIZE, 0);
    // printf("Data: %s", buffer);
    // close(sockfd);
    // printf("[+]Disconnected from the server. \n");
    return 0;
}