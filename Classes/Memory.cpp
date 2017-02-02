#include "../Definitions/Memory.hh"

Memory::Memory() {
  _mbt.available = MEMORY_SIZE;
  memset(_mbt.blocks, true, sizeof _mbt.blocks);
}

Memory::~Memory() {}

int   *Memory::allocate(int size) {
  if (_mbt.available < size) {
    cout << "Cannot allocate " << size << " blocks (" << _mbt.available << " available)" << endl;
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

void  Memory::free(PageTable *pageTable) {
  if (blocks == 0) {
    return ;
  }

  for (int index = 0; index < pageTable->numberOfBlocks; index++) {
    int blockId = pageTable->blocks[index];

    if (blockId > 0 && blockId < MEMORY_SIZE) {
      _mbt.blocks[blockId] = FREE;
    }
  }

  this->displayMemoryBlockTable();
}

void  Memory::displayMemoryBlockTable() const {
  cout << "Memory Block Table" << endl;

  int displayedBlockNumber = 0;

  while (displayedBlockNumber < MEMORY_SIZE) {
    int lineLimit = displayedBlockNumber + 8;
    cout << setw(15) << "blocks (" << displayedBlockNumber << "-" << lineLimit - 1 << ")";

    while (displayedBlockNumber < lineLimit) {
      cout << "\t" << (_mbt.blocks[displayedBlockNumber] ? "free" : "used");
      displayedBlockNumber++;
    }

    cout << endl;
  }
}
