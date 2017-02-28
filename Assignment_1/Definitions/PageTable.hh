#pragma once

// Structure that represents a Page Table, where blocks is a pointer
// to the array that contains the ids of allocated memory blocks
// numberOfBlocks defines the length of this array
typedef struct PageTable {
  int numberOfBlocks;
  int *blocks;
} PageTable;
