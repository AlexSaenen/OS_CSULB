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
  } else {
    process->pageTable = new PageTable;
    process->pageTable->numberOfBlocks = memoryBlocksRequired;
    process->pageTable->blocks = allocatedBlocks;
    Self.processes.track(process);
    Self.processes.displayPageTable(process);
    Self.memory.displayMemoryBlockTable();
  }
}


Print::Print() {}
Print::~Print() {}

void Print::handle() const {
  PCB *process = Self.processes.first();

  while (process) {
    cout << "Process (pid=" << process->pid << ")" << endl;
    process = process->next;
  }
}


Exit::Exit() {}
Exit::~Exit() {}

void Exit::handle() const {
  Self.stop();
}
