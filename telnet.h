#ifndef TELNET_H
#define TELNET_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

#define SERVER 1
#define CLIENT 2

#define INET_PTON_ERROR 1
#define SOCKET_CREATE_ERROR 2
#define SOCKET_SET_OPTIONS_ERROR 3
#define BIND_ERROR 4
#define LISTEN_ERROR 5

typedef int SOCKET;

SOCKET newServerSocket(char*, int, int*);
SOCKET acceptClient(SOCKET, char*, int*);
int sendData(SOCKET, char*);
int recvData(SOCKET, char*);
int getSocketState(SOCKET);

#endif
