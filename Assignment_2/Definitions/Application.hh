#pragma once

#include "MessageQueue.hh"
#include "Child.hh"

// Main Program Class, handles the program execution flow
class   Application {

public:
  MessageQueue messages;

public:
  Application();
  ~Application();

public:
  void execute();

};

// Here we make available the singleton instance of the Main Application
extern Application *app;

// And rename it as Self
#define Self (*app)
