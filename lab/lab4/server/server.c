#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


void calculate(int new_socket)
{
	int a, b, option, result = 0;
	char ayat[2000];

	strcpy(ayat, "\n1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\nWhich calculation to be done (Enter number): ");
	send(new_socket, ayat, strlen(ayat), 0);
	bzero(ayat, sizeof(ayat));
	recv(new_socket, ayat, 2000, 0);
	printf("Client: %s", ayat);
	option = ayat[0] - 48;
	bzero(ayat, sizeof(ayat));
	
	strcpy(ayat, "Enter the First value");
	send(new_socket, ayat, strlen(ayat), 0);
	bzero(ayat, sizeof(ayat));
	recv(new_socket, ayat, 2000, 0);
	printf("Client: %s", ayat);
	a = atoi(ayat);
	bzero(ayat, sizeof(ayat));
	
	strcpy(ayat, "Enter the Second value");
	send(new_socket, ayat, strlen(ayat), 0);
	bzero(ayat, sizeof(ayat));
	recv(new_socket, ayat, 2000, 0);
	printf("Client: %s", ayat);
	b = atoi(ayat);
	bzero(ayat, sizeof(ayat));
	
	switch(option){
		case 1:
			result = a + b;
			break;
		case 2:
			result = a - b;
			break;
		case 3:
			result = a * b;
			break;
		case 4:
			result = a / b;
			break;
	}
	sprintf(ayat, "Answer is: %d", result);
	send(new_socket, ayat, strlen(ayat), 0);
	bzero(ayat, sizeof(ayat));
}

int main(int argc, char *argv[])
{
	int socket_desc, new_socket, c;
	struct sockaddr_in server, client;
	char ayat[2000];
	pid_t pid;
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
		return 1;
	}
	//Prepare the sockaddr_in strcutire
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons (8888);

	//Bind
	if(bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0 )
	{
		puts("Bind Failed");
		return 1;
	}
	
	puts("Bind done");

	//Listen
	listen(socket_desc, 3);

	//Accept any incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	while(1)
	{
		new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		if (new_socket < 0)
		{
			perror ("Accept Failed");
			return 1;
		}
		puts("Connection accepted");
		if((pid = fork()) == 0)
		{
			close(socket_desc);
			while (1)
			{
				bzero(ayat, sizeof(ayat));
				recv(new_socket, ayat, 2000, 0);
				printf("\nClient: %s", ayat);
				if (strcmp(ayat, ":exit\n") == 0)
				{
					close(new_socket);
					printf("A user has disconnected\n");
					exit(1);
				}
				else if (strcmp(ayat, ":calculate\n") == 0)
				{
					calculate(new_socket);
				}
				else
				{
				send(new_socket, ayat, strlen(ayat), 0);
				}
			}
		}
	}
	close(new_socket);
	return 0;
}
