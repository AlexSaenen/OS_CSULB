#include "../Definitions/ProcessManager.hh"

ProcessManager::ProcessManager() : _pidCounter(0), _readQueue(0) {}
ProcessManager::~ProcessManager() {
  while (this->_readQueue) {
    this->kill(this->_readQueue, true);
  }
}

PCB   *ProcessManager::spawn() {
  PCB *process = new PCB;
  process->pid = _pidCounter++;
  process->next = 0;
  process->pageTable = 0;
  return process;
}

void  ProcessManager::kill(PCB *process, bool isTracked) {
  if (process == 0) {
    return ;
  }

  if (isTracked) {
    this->untrack(process);
  }

  process->next = 0;
  if (process->pageTable) {
    cout << "removing " << process->pageTable->blocks << endl;
    delete process->pageTable->blocks;
  }

  delete process;
}

void  ProcessManager::track(PCB *process) {
  PCB *node = this->last();

  if (node) {
    node->next = process;
  } else {
    this->_readQueue = process;
  }
}

void  ProcessManager::untrack(PCB *process) {
  PCB *node = this->first();

  if (node == process) {
    this->_readQueue = process->next;
  } else {
    while (node->next != 0 && node->next != process) {
      node = node->next;
    }

    if (node->next) {
      node->next = process->next;
    }
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

PCB   *ProcessManager::last() const {
  if (this->_readQueue == 0) {
    return this->_readQueue;
  }

  PCB *iterator = this->_readQueue;
  while (iterator->next) {
    iterator = iterator->next;
  }

  return iterator;
}

PCB   *ProcessManager::first() const {
  return this->_readQueue;
}
