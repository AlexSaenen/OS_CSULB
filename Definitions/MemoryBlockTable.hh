#pragma once

// Structure that represents our Memory Block Table
typedef struct MBT {
  int available;
  bool blocks[128];
} MBT;
