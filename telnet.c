#include "telnet.h"

SOCKET newServerSocket(char* ip, int port, int* err) {
  struct sockaddr_in serverAddr;
  struct sockaddr_in secAddr;

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  
  if (inet_pton(AF_INET, ip, &serverAddr.sin_addr) <= 0)
    return INET_PTON_ERROR;

  int srvSock = socket(AF_INET, SOCK_STREAM, 0);
  if (srvSock < 0)
    return SOCKET_CREATE_ERROR;

  int yes = 1;
  if (setsockopt(srvSock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
    return SOCKET_SET_OPTIONS_ERROR;

  socklen_t len = sizeof(serverAddr);
  if (bind(srvSock, (struct sockaddr*) &serverAddr, len) < 0)
    return BIND_ERROR;

  if (listen(srvSock, 0) < 0)
    return LISTEN_ERROR;

  return srvSock;
}

SOCKET acceptClient(SOCKET srvSock, char* ip, int* port) {
  struct sockaddr_in cliAddr = {};
  socklen_t len = sizeof(cliAddr);
  int cliSock = accept(srvSock, (struct sockaddr*) &cliAddr, &len);

  if (cliSock <= 0)
    return 0;

  strcpy(ip, inet_ntoa(cliAddr.sin_addr));
  *port = cliAddr.sin_port;
  
  
  return cliSock;
}

int sendData(SOCKET sock, char* data) {
  int sent = send(sock, data, strlen(data), 0);

  return sent;
}

int recvData(SOCKET sock, char* data) {
  memset(data, 0, sizeof(data));

  int recived = recv(sock, data, sizeof(data), 0);

  return recived;
}

int getSocketState(SOCKET sock) {
  int errorCode;
  int errorCodeSize = sizeof(errorCode);
  getsockopt(sock, SOL_SOCKET, SO_ERROR, &errorCode, &errorCodeSize);

  return errorCode;
}
