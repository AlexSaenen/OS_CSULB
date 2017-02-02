#pragma once

#include "../Definitions/Menu.hh"
#include "../Definitions/ProcessManager.hh"
#include "../Definitions/Memory.hh"

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

};

extern Application *app;

#define Self (*app)
