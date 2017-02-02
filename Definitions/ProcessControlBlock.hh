#pragma once

#include "../Definitions/PageTable.hh"

// Structure that defines our Process Control Block
// it will be used with the next pointer to create a linked list
// instead of using the queue data structure offered by the CPP STL
typedef struct PCB {
  int pid;
  PageTable *pageTable;
  PCB *next;
} PCB;
