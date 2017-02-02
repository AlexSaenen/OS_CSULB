#include "../Definitions/Application.hh"

Application *app = 0;

Application::Application() : _menu() {
  app = this;
  Self.instantiate(10); // Instantiate a new Process that represents the OS
}

Application::~Application() {}

void Application::run() {
  _menu.run();
}

void Application::stop() {
  _menu.quit();
}

void Application::instantiate(int memoryRequired) {
  PCB *process = Self.processes.spawn();
  int *allocatedBlocks = Self.memory.allocate(memoryRequired);

  if (allocatedBlocks == 0) {
    Self.processes.kill(process);
  } else {
    process->pageTable = new PageTable;
    process->pageTable->numberOfBlocks = memoryRequired;
    process->pageTable->blocks = allocatedBlocks;
    Self.processes.track(process);
    Self.processes.displayPageTable(process);
    Self.memory.displayMemoryBlockTable();
  }
}
