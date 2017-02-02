#pragma once

#include <iostream>
using namespace std;

#include "Handler.hh"

// Class that helps us handle the Menu selection flow
class   Menu {

private:
  Handler* _interruptVector[4];
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
