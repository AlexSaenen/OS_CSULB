#pragma once

#include <iostream>
using namespace std;

#include "../Definitions/MemoryBlockTable.hh"
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
  void free(int *blocks);

};
