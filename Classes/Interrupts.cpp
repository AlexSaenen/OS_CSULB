#include "../Definitions/Interrupts.hh"
#include "../Definitions/Application.hh"
#include "../Definitions/ProcessControlBlock.hh"

Initiate::Initiate() {
  srand(time(0));
}

Initiate::~Initiate() {}

void Initiate::handle() const {
  PCB *process = Self.processes.spawn();
  int memoryBlocksRequired = (rand() % 20) + 1;
  int *allocatedBlocks = Self.memory.allocate(memoryBlocksRequired);

  if (allocatedBlocks == 0) {
    Self.processes.kill(process);
    // Should display message and give hand back to menu
  } else {
    process->pageTable = new PageTable;
    process->pageTable->numberOfBlocks = memoryBlocksRequired;
    process->pageTable->blocks = allocatedBlocks;
    delete process->pageTable->blocks;
    Self.processes.track(process);
    Self.processes.displayPageTable(process);
    Self.memory.displayMemoryBlockTable();
  }
}

Exit::Exit() {}
Exit::~Exit() {}

void Exit::handle() const {
  Self.stop();
}
