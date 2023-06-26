#ifndef LOAD_H
#define LOAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <linux/kernel.h>

typedef struct {
  unsigned long freeRam;
  unsigned long usedRam;
  unsigned long totalRam;

  unsigned long freeSwap;
  unsigned long usedSwap;
  unsigned long totalSwap;

  unsigned long freeHigh;
  unsigned long usedHigh;
  unsigned long totalHigh;
} memInfo;

#define CPU_LOAD_COMMAND "mpstat 1 1 | awk '$3 ~ /CPU/ { for(i=1;i<=NF;i++) { if ($i ~ /%idle/) field=i } } $3 ~ /all/ { printf(\"%d\",100 - $field) }'"

int getCpuLoad(void);
void getMemInfo(memInfo*);
unsigned long getProcessCount(void);
int createJSON(unsigned int, unsigned long, memInfo, char*);

#endif
