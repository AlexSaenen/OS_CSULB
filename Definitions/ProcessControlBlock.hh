#pragma once

#include "../Definitions/PageTable.hh"

typedef struct PCB {
  int pid;
  PageTable *pageTable;
  PCB *next;
} PCB;
