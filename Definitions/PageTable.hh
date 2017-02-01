#pragma once

typedef struct PageTable {
  int numberOfBlocks;
  int *blocks;
} PageTable;
