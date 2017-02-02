#pragma once

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

#include "../Definitions/MemoryBlockTable.hh"
#include "../Definitions/PageTable.hh"

// Define a few MACROS to make the code more readable
#define MEMORY_SIZE 128
#define FREE true
#define ALLOCATED false

// This Class will handle the allocation, free and display of the memory blocks of the System
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
