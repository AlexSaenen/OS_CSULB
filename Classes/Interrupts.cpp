#include "../Definitions/Interrupts.hh"
#include "../Definitions/Application.hh"
#include "../Definitions/ProcessControlBlock.hh"

Initiate::Initiate() {
  srand(time(0));
}

Initiate::~Initiate() {}

void Initiate::handle() const {
  int memoryBlocksRequired = (rand() % 20) + 1;
  Self.instantiate(memoryBlocksRequired);
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
