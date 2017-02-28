#pragma once

#define MEMORY_SIZE 128
#define OS_SIZE 10

// Structure that represents our Memory Block Table
typedef struct MBT {
  int available;
  bool blocks[MEMORY_SIZE];
} MBT;
