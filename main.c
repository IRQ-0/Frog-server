#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "telnet.h"
#include "load.h"

#define BUFFER_SIZE 1000

void error(char*);
int checkNumber(char*);

int main(int argc, char** argv) {
 if (argc < 3) {
	 puts("usage: forg <listen ip> <listen port>");
	 return 2;
 }

 if (checkNumber(argv[2])) {
	puts("Invalid port value");
	return 2;
 }

 int port = atoi(argv[2]);

 printf("Starting at %s:%d\n", argv[1], port);

 int err = 0;
 SOCKET serverSock = newServerSocket(argv[1], port, &err);

  // Check if error
  switch (err) {
    case INET_PTON_ERROR:
      error("inet_pton() error");
      exit(1);
    break;

    case SOCKET_CREATE_ERROR:
      error("socket() error");
      exit(1);
    break;

    case SOCKET_SET_OPTIONS_ERROR:
      error("setsockopt() error");
      exit(1);
    break;

    case BIND_ERROR:
      error("bind() error");
      exit(1);
    break;

    case LISTEN_ERROR:
      error( "listen() error");
      exit(1);
    break;

    default:
      __asm__("nop");
  }

  puts("Started");

  char cliIp[BUFFER_SIZE];
  int cliPort = 0;
  
  char buffer[BUFFER_SIZE]; 
  char jsonBuffer[BUFFER_SIZE];
  memInfo mem;

  
  while (1) {
    memset(buffer, 0, sizeof(buffer));

    puts("Waiting for client...");

    SOCKET cliSock = acceptClient(serverSock, cliIp, &cliPort);
    printf("Client: %s:%d\n", cliIp, cliPort); 
 
    for ( ; ; ) {
       	if (recvData(cliSock, buffer) <= 0) {
		puts("Client disconnected");
		break;
	}

	if (strcmp(buffer, "R") == 0) {
		getMemInfo(&mem);
		createJSON(getCpuLoad(), getProcessCount(), mem, jsonBuffer);
		sendData(cliSock, jsonBuffer);
	}
    }
  }
  
  return 0;

}

void error(char* in) {
	printf("Error: %s\n", in);
}

int checkNumber(char* in) {
	for (int i = 0; i < strlen(in); i++) {
		if (!isdigit(in[i])) {
			return 1;
		}
	}

	return 0;
}
