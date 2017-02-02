#include "../Definitions/Application.hh"

Application *app = 0;

Application::Application() : _menu() {
  app = this; // Initialize our global singleton instance pointer
  int *allocatedBlocks = Self.memory.allocate(10); // Allocate 10 blocks for OS
  delete[] allocatedBlocks; // We don't need to store the Page Table
}

Application::~Application() {}

void Application::run() {
  _menu.run(); // Run the main program flow by giving control to the menu
}

void Application::stop() {
  _menu.quit(); // Tell the menu to give back control to the Application Class
}

// Instantiate a new Process and allocate the required number of memory blocks
void Application::instantiate(int memoryRequired) {
  PCB *process = Self.processes.spawn(); // Spawn a new process
  // Attempte to reserve required number of memory blocks
  int *allocatedBlocks = Self.memory.allocate(memoryRequired);

  if (allocatedBlocks == 0) {
    // No memory was allocated, kill the process
    Self.processes.kill(process);
  } else {
    // Give the process a Page Table that beholds the allocated blocks
    process->pageTable = new PageTable;
    process->pageTable->numberOfBlocks = memoryRequired;
    process->pageTable->blocks = allocatedBlocks;
    // Tell the Process Manager to add the process to the ready queue
    Self.processes.track(process);
    // Display the new process' Page Table and the current MBT status
    Self.processes.displayPageTable(process);
    Self.memory.displayMemoryBlockTable();
  }
}
