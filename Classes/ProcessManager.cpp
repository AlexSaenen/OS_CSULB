#include "../Definitions/ProcessManager.hh"

ProcessManager::ProcessManager() : _pidCounter(0), _readQueue(0) {}
ProcessManager::~ProcessManager() {}

PCB   *ProcessManager::spawn() {
  PCB *process = new PCB;
  process->pid = _pidCounter++;
  process->next = 0;
  process->pageTable = 0;
  return process;
}

void  ProcessManager::kill(PCB *process) {
  // first verify that no pageTable exist
  // else free memory blocks stored in page table
  // verify that it isn't a node that is tracked, else remove it
  // then free process
  process->next = 0;
  cout << "delete process" << endl;
  delete process->pageTable;
  delete process;
}

void  ProcessManager::track(PCB *process) {
  PCB *node = this->tail();

  if (node) {
    node->next = process;
  } else {
    node = process;
  }
}

void  ProcessManager::displayPageTable(PCB *process) const {
  cout << "Process (pid=" << process->pid << ")" << endl;
  cout << "\t";

  PageTable *pageTable = process->pageTable;

  for (int index = 0; index < pageTable->numberOfBlocks; index++) {
    cout << pageTable->blocks[index] << " ";
  }

  cout << endl;
}

PCB   *ProcessManager::tail() const {
  if (this->_readQueue == 0) {
    return this->_readQueue;
  }

  PCB *iterator = this->_readQueue;
  while (iterator->next) {
    iterator = iterator->next;
  }

  return iterator;
}

PCB   *ProcessManager::head() const {
  return this->_readQueue;
}
