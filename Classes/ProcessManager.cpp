#include "../Definitions/ProcessManager.hh"

ProcessManager::ProcessManager() : _pidCounter(0), _readQueue(0) {}
ProcessManager::~ProcessManager() {
  // Empty the ready queue and kill all processes
  while (this->last()) {
    this->kill(this->last(), true);
  }
}

PCB   *ProcessManager::spawn() {
  // Create a new Process with a unique pid
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
    // The process isTracked (is in the ready queue), we remove it
    this->untrack(process);
  }

  process->next = 0;

  // Free all process related dynamic resources
  if (process->pageTable) {
    delete[] process->pageTable->blocks;
    delete process->pageTable;
  }

  delete process;
}

void  ProcessManager::track(PCB *process) {
  // Get the end of the ready queue
  PCB *node = this->last();

  // Append the new process to the queue
  if (node) {
    node->next = process;
  } else {
    // The queue is empty
    this->_readQueue = process;
  }
}

void  ProcessManager::untrack(PCB *process) {
  PCB *node = this->first();

  if (node == process) {
    // The process we want to remove from queue is the first element
    // we extract it and reset the ready queue starting point
    this->_readQueue = process->next;
  } else {
    // Find our the node pointing to our process in the linked list
    while (node->next != 0 && node->next != process) {
      node = node->next;
    }

    // Extract our process and relink the list
    if (node->next) {
      node->next = process->next;
    }
  }
}

// Display the process Page Table
void  ProcessManager::displayPageTable(PCB *process) const {
  cout << "Process (pid=" << process->pid << ")" << endl;
  cout << "\t";

  PageTable *pageTable = process->pageTable;

  for (int index = 0; index < pageTable->numberOfBlocks; index++) {
    cout << pageTable->blocks[index] << " ";
  }

  cout << endl;
}

// Get the last process in the ready queue
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

// Get the first process in the ready queue
PCB   *ProcessManager::first() const {
  return this->_readQueue;
}

// Get the process in the ready queue with the corresponding pid
PCB   *ProcessManager::find(int pid) const {
  PCB *process = this->first();

  while (process && process->pid != pid) {
    process = process->next;
  }

  return process;
}
