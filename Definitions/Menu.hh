#pragma once

#include <iostream>
using namespace std;

#include "Handler.hh"

class   Menu {

private:
  Handler* _interruptVector[5];
  bool     _isRunning;

public:
  Menu();
  ~Menu();

public:
  void run(void);
  void quit(void);

private:
  void displayMain(void) const;
  void displayError(void) const;
  int getSelection(void) const;

};
