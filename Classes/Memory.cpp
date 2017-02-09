#include "../Definitions/Memory.hh"

Memory::Memory() {
  // Initiate the MBT
  _mbt.available = MEMORY_SIZE;
  memset(_mbt.blocks, true, sizeof _mbt.blocks);
}

Memory::~Memory() {}

// Allocate required memory blocks from the MBT
int   *Memory::allocate(int size) {
  // Check if required space is available
  if (_mbt.available < size) {
    cout << "Cannot allocate " << size << " blocks (" << _mbt.available << " available)" << endl;
    return 0;
  }

  int *allocatedBlocks = new int[size];
  int allocatedNumber = 0;

  // Mark progressively the free blocks inside MBT as allocated until we gathered required number of blocks
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

// Free memory blocks in MBT that are used in a Page Table
void  Memory::free(PageTable *pageTable) {
  if (pageTable->blocks == 0) {
    return ;
  }

  // Free all the MBT blocks that were reserved for this Page Table
  for (int index = 0; index < pageTable->numberOfBlocks; index++) {
    int blockId = pageTable->blocks[index];

    if (blockId >= OS_SIZE && blockId < MEMORY_SIZE) {
      _mbt.blocks[blockId] = FREE;
      _mbt.available++;
    }
  }

  // Display the updated MBT status
  this->displayMemoryBlockTable();
}

// Display the status of all the memory blocks inside the MBT
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
