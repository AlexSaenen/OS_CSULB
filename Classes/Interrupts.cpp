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


Terminate::Terminate() {}
Terminate::~Terminate() {}

void Terminate::handle() const {
  cout << "Select the pid of a process to terminate: ";

  int pid = 0;
  cin >> pid;
  if (pid == 0) {
    cout << "Cannot kill process with pid=0, since it's the OS" << endl;
  } else {
    PCB *process = Self.processes.find(pid);
    if (process) {
      if (process->pageTable) {
        Self.memory.free(process->pageTable->blocks);
      }

      Self.processes.kill(process, true);
    } else {
      cout << "Cannot kill process with pid=" pid << ", no such process" << endl;
    }
  }
}


Exit::Exit() {}
Exit::~Exit() {}

void Exit::handle() const {
  Self.stop();
}
