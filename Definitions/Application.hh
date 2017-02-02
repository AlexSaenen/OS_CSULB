#pragma once

#include "../Definitions/Menu.hh"
#include "../Definitions/ProcessManager.hh"
#include "../Definitions/Memory.hh"

// Main Program Class, handles the program execution flow and can instantiate a new process
class   Application {

private:
  Menu _menu;

public:
  ProcessManager processes;
  Memory memory;

public:
  Application();
  ~Application();

public:
  void run();
  void stop();
  void instantiate(int memoryRequired);

};

// Here we make available the singleton instance of the Main Application
extern Application *app;

// And rename it as Self
#define Self (*app)
