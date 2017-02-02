#include "../Definitions/Memory.hh"

Memory::Memory() {
  _mbt.available = MEMORY_SIZE;
  memset(_mbt.blocks, true, sizeof _mbt.blocks);
}

Memory::~Memory() {}

int   *Memory::allocate(int size) {
  if (_mbt.available < size) {
    return 0;
  }

  int *allocatedBlocks = new int[size];
  int allocatedNumber = 0;

  for (int block = 0; block < MEMORY_SIZE && allocatedNumber < size; block++) {
    if (_mbt.blocks[block] == FREE) {
      _mbt.blocks[block] = ALLOCATED;
      allocatedBlocks[allocatedNumber] = block;
      allocatedNumber++;
      _mbt.available--;
    }
  }

  return allocatedBlocks;
}

void  Memory::free(int *blocks) {
  if (blocks == 0) {
    return ;
  }

  // End free function
}

void  Memory::displayMemoryBlockTable() const {
  cout << "Memory Block Table" << endl;

  int displayedBlockNumber = 0;

  while (displayedBlockNumber < MEMORY_SIZE) {
    int lineLimit = displayedBlockNumber + 8;
    cout << "blocks (" << displayedBlockNumber << "-" << lineLimit << ")";

    while (displayedBlockNumber < lineLimit) {
      cout << "\t" << (_mbt.blocks[displayedBlockNumber] ? "free" : "allocated");
      displayedBlockNumber++;
    }

    cout << endl;
  }
}
