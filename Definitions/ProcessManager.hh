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
  void kill(PCB *process);
  void track(PCB *process);
  PCB *tail(void) const;
  PCB *head(void) const;
  void displayPageTable(PCB *process) const;

};
