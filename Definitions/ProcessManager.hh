#pragma once

#include <iostream>
using namespace std;

#include "../Definitions/ProcessControlBlock.hh"

class   ProcessManager {

private:
  int   _pidCounter;
  PCB   *_readQueue;

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
  void displayPageTable(PCB *process) const;

};
