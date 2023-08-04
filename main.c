#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "telnet.h"
#include "load.h"
#include "static.h"

#define BUFFER_SIZE 1000

void error(char*);
int checkNumber(char*);

int main(int argc, char** argv) {
 if (argc < 3) {
	 puts("usage: frogd <listen ip> <listen port>");
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
  char* top;
  char* df;
  char* blk;
  char* interfaces;
  char* service;
 
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
	} else if (strcmp(buffer, "T") == 0) {
		err = 0;
		top = getTop(&err);

		switch (err) {
			case POPEN_ERROR:
				error("popen() error");
			break;

			case MALLOC_ERROR:
				error("malloc() error");
			break;

			case FREAD_ERROR:
				error("fread() error");
			break;
		}

		/*sprintf(intBuffer, "%ld", strlen(top));
		sendData(cliSock, intBuffer);*/

		sendData(cliSock, top);
	} else if (strcmp(buffer, "D") == 0) {
		err = 0;
		df = getDf(&err);

		switch (err) {
			case POPEN_ERROR:
				error("popen() error");
			break;

			case MALLOC_ERROR:
				error("malloc() error");
			break;
	
			case FREAD_ERROR:
				error("fread() error");
			break;
		}

		sendData(cliSock, df);
    	 } else if (strcmp(buffer, "B") == 0) {
		 err = 0;
		 blk = getBlk(&err);
		
	         switch (err) {
			case POPEN_ERROR:
				error("popen() error");
			break;

			case MALLOC_ERROR:
				error("malloc() error");
			break;
	
			case FREAD_ERROR:
				error("fread() error");
			break;
		 }

		 sendData(cliSock, blk);
       	} else if (strcmp(buffer, "I") == 0) {
		err = 0;
		interfaces = getIf(&err);
		
		switch (err) {
			case POPEN_ERROR:
				error("popen() error");
			break;

			case MALLOC_ERROR:
				error("malloc() error");
			break;
	
			case FREAD_ERROR:
				error("fread() error");
			break;
		 }
		sendData(cliSock, interfaces);
    } else if (buffer[0] == 'V') {
		err = 0;
		service = getService((buffer + 1), &err);
		
		switch (err) {
			case POPEN_ERROR:
				error("popen() error");
			break;

			case MALLOC_ERROR:
				error("malloc() error");
			break;
	
			case FREAD_ERROR:
				error("fread() error");
			break;
		 }
		sendData(cliSock, service);
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
