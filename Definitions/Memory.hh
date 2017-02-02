#pragma once

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

#include "../Definitions/MemoryBlockTable.hh"
#include "../Definitions/PageTable.hh"
#define MEMORY_SIZE 128
#define FREE true
#define ALLOCATED false

class Memory {

private:
  MBT  _mbt;

public:
  Memory();
  ~Memory();

public:
  int *allocate(int size);
  void free(PageTable *pageTable);
  void displayMemoryBlockTable() const;

};
