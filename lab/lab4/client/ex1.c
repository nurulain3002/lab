#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
int socket_desc, new_socket;
struct sockaddr_in server;
char *message, server_reply[5000];

//Creating a scoket
socket_desc = socket (AF_INET, SOCK_STREAM, 0);
if (socket_desc == -1)
{
printf("Could not create socet");
}

server.sin_addr.s_addr = inet_addr("192.168.56.104");
server.sin_family = AF_INET;
server.sin_port = htons (8888);

//Connecting to remote server

if(connect(socket_desc, (struct sockaddr *)&server, sizeof(server))< 0)
{
	puts("Connect Error");
	return 1;
}

puts("Connected\n");
//Seding data
message = "Hi, saya darisha";
if (send(socket_desc, message, strlen(message), 0) < 0)
{
	puts("Send Failed");
	return 1;
}

puts("Data Send\n");
//Receiving a reply from the server
if (recv(socket_desc, server_reply, 2000, 0) < 0)
{
	puts("recv failed");
}
else
{
	puts("Reply received \n");
	puts(server_reply);
}

close(socket_desc);
return 0;
}
