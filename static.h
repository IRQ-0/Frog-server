#ifndef STATIC_H
#define STATIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POPEN_ERROR 1
#define MALLOC_ERROR 2
#define FREAD_ERROR 3

#define MAX_LINE_LENGTH 261

// TOP
#define TOP_COMMAND "top -b -n 1"

// DF
#define DF_COMMAND "df -H"

// Blk
#define BLK_COMMAND "lsblk"

//If
#define IF_COMMAND "ip a && echo -e '\n\n\n' && ifconfig"

// Service
#define SERVICE_COMMAND "systemctl status "

// Main function to get output of linux commands
char* getOut(int*, char*);

char* getTop(int*);
char* getDf(int*);
char* getBlk(int*);
char* getIf(int*);
char* getService(char*, int*);

#endif
