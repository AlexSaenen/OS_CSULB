#pragma once

#include <iostream>
using namespace std;

#include "../Definitions/ProcessControlBlock.hh"

// Class that offers routines to handle a process life cycle more easily
// it also handles all the processes running in our System
class   ProcessManager {

private:
  int   _pidCounter;
  PCB   *_readyQueue;

public:
  ProcessManager();
  ~ProcessManager();

public:
  PCB *spawn(void);
  void kill(PCB *process, bool isTracked = false);
  void track(PCB *process);
  void untrack(PCB *process);
  PCB *last(void) const;
  PCB *first(void) const;
  PCB *find(int pid) const;
  void displayPageTable(PCB *process) const;

};
