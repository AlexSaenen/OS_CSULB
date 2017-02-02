#include <string>
#include <stdexcept>

#include "../Definitions/Interrupts.hh"
#include "../Definitions/Application.hh"
#include "../Definitions/ProcessControlBlock.hh"

Initiate::Initiate() {
  srand(time(0));
}

Initiate::~Initiate() {}

void Initiate::handle() const {
  // Generate a random number of required memory blocks
  int memoryBlocksRequired = (rand() % 20) + 1;
  // Initiate the new process
  Self.instantiate(memoryBlocksRequired);
}


Print::Print() {}
Print::~Print() {}

void Print::handle() const {
  // Get the ready queue
  PCB *process = Self.processes.first();

  // Display all process ids while iterating over the ready queue
  while (process) {
    cout << "Process (pid=" << process->pid << ")" << endl;
    process = process->next;
  }
}


Terminate::Terminate() {}
Terminate::~Terminate() {}

void Terminate::handle() const {
  cout << "Select the pid of a process to terminate: ";

  string input = 0;
  cin >> input;

  try {
    int pid = stoi(string);

    // Find a process with the given pid
    PCB *process = Self.processes.find(pid);
    if (process) {
      if (process->pageTable) {
        // Free the allocated memory blocks from the Page Table
        Self.memory.free(process->pageTable);
      }

      // Kill the process and remove it from the ready queue
      Self.processes.kill(process, true);
    } else {
      cout << "Cannot kill process with pid=" << pid << ", no such process" << endl;
    }
  } catch (invalid_argumemt) {
    cout << "Please enter a correct number" << endl;
  }
}


Exit::Exit() {}
Exit::~Exit() {}

void Exit::handle() const {
  Self.stop(); // Tell the Main Application to stop execution and exit nicely
}
