#include "load.h"

int getCpuLoad(void) {
  FILE *fp;
  char buffer[4096];

  fp = popen(CPU_LOAD_COMMAND, "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit(1);
  }

  int ret = 0;
  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
     ret = atoi(buffer);
  }

  pclose(fp);

  return ret;
}

void getMemInfo(memInfo* info) {
  struct sysinfo sysinf;
  sysinfo(&sysinf);
  
  info->totalRam = sysinf.totalram * sysinf.mem_unit;
  info->freeRam = sysinf.freeram * sysinf.mem_unit;
  info->usedRam = (sysinf.totalram - sysinf.freeram) * sysinf.mem_unit;

  info->totalSwap = sysinf.totalswap * sysinf.mem_unit;
  info->freeSwap = sysinf.freeswap * sysinf.mem_unit;
  info->usedSwap = (sysinf.totalswap - sysinf.freeswap) * sysinf.mem_unit;

  info->totalHigh = sysinf.totalhigh * sysinf.mem_unit;
  info->freeHigh = sysinf.freehigh * sysinf.mem_unit;
  info->usedHigh = (sysinf.totalhigh - sysinf.freehigh) * sysinf.mem_unit;
}

unsigned long getProcessCount(void) {
  struct sysinfo sysinf;
  sysinfo(&sysinf);

  return sysinf.procs;
}

void addValue(char* key, unsigned long value, char* out) {
  char buffer[1000];
  memset(buffer, 0, sizeof(buffer));
  sprintf(buffer, "\"%s\":\"%ld\"", key, value);
  strcat(out, buffer);
}

int createJSON(unsigned int cpuload, unsigned long procs, memInfo mem, char* out) {
  memset(out, 0, sizeof(out));
  strcpy(out, "{");
  addValue("cpuload", cpuload, out);
  strcat(out, ",");
  
  addValue("freeram", mem.freeRam, out);
  strcat(out, ",");
  addValue("usedram", mem.usedRam, out);
  strcat(out, ",");
  addValue("totalram", mem.totalRam, out);
  strcat(out, ",");

  addValue("freeswap", mem.freeSwap, out);
  strcat(out, ",");
  addValue("usedswap", mem.usedSwap, out);
  strcat(out, ",");
  addValue("totalswap", mem.totalSwap, out);
  strcat(out, ",");

  addValue("freehigh", mem.freeHigh, out);
  strcat(out, ",");
  addValue("usedhigh", mem.usedHigh, out);
  strcat(out, ",");
  addValue("totalhigh", mem.totalHigh, out);
  strcat(out, ",");

  addValue("processcount", procs, out);
  
  strcat(out, "}");
  
  //  puts(out);
}
