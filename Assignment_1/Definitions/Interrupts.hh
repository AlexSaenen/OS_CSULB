#include "Handler.hpp"

// Initiates a Process
class Initiate : public Handler {

public:
  Initiate();
  virtual ~Initiate();

public:
  virtual void handle(void) const;

};

// Prints all runnning Processes
class Print : public Handler {

public:
  Print();
  virtual ~Print();

public:
  virtual void handle(void) const;

};

// Terminates a Process
class Terminate : public Handler {

public:
  Terminate();
  virtual ~Terminate();

public:
  virtual void handle(void) const;

};

// Exits the program
class Exit : public Handler {

public:
  Exit();
  virtual ~Exit();

public:
  virtual void handle(void) const;

};
