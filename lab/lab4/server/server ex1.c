#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int socket_desc, new_socket, c;
	struct sockaddr_in server, client;
	char *message, *ayat;

	//Create socket
	
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
	puts("Connection accepted");
	while ((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)))
	{

		recv(new_socket, ayat, 2000, 0);
		puts(ayat);
		//Reply to the client
		message = "Hello there, I have received your connection, Handsome ;)\n";
		write(new_socket, message, strlen(message));
	}

	if (new_socket < 0)
	{
		perror ("Accept Failed");
		return 1;
	}
	return 0;
}
