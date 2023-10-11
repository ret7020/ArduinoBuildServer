#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SIZE 1024

char *init_workspace()
{
	time_t rawtime;
	struct tm *timeinfo;
	char buffer[120];
	char *path = (char *)malloc(100 * sizeof(char));
	char *path_final;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 120, "./tmp/build_%Y_%m_%d_%H_%M_%S/", timeinfo);
	strcat(path, buffer);

	mkdir(path, 0777);
	path_final = strcat(path, "main");
	mkdir(path_final, 0777);
	return path_final;
}

void compile(int sockfd)
{

	int n;
	FILE *fp;
	char buffer[SIZE];
	char *workspace = init_workspace();
	char *board_name = "arduino:avr:mega:cpu=atmega2560"; // Fallback board fqbn
	char *file_to_save = strcat(workspace, "/main.ino");
	printf("Source location: %s\n", workspace);

	fp = fopen(file_to_save, "w");
	if (fp == NULL)
	{
		perror("[-]Error in creating file.");
		exit(1);
	}
	// Recieve compile task header
	n = recv(sockfd, buffer, SIZE, 0);
	if (n > 0)
	{

		for (;;)
		{
			n = recv(sockfd, buffer, SIZE, 0);
			if (n <= 0)
			{
				break;
				return;
			}
			fprintf(fp, "%s", buffer);
			bzero(buffer, SIZE);
		}
	}

	printf("File saved. Compiling...\n");
	// system("arduino-cli");
	return;
}

int main()
{
	char *ip = "127.0.0.1";
	int port = 8080;
	int e;

	int sockfd, new_sock;
	struct sockaddr_in server_addr, new_addr;
	socklen_t addr_size;
	char buffer[SIZE];

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

	e = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (e < 0)
	{
		perror("[-]Error in Binding");
		exit(1);
	}
	printf("[+]Binding Successfull.\n");

	e = listen(sockfd, 10);
	if (e == 0)
	{
		printf("[+]Listening...\n");
	}
	else
	{
		perror("[-]Error in Binding");
		exit(1);
	}
	addr_size = sizeof(new_addr);
	new_sock = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);

	compile(new_sock);
	printf("[+] Compiled");
}