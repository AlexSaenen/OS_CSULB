#include "Handler.hh"

class Initiate : public Handler {

public:
  Initiate();
  virtual ~Initiate();

public:
  virtual void handle(void) const;

};

class Print : public Handler {

public:
  Print();
  virtual ~Print();

public:
  virtual void handle(void) const;

};

class Terminate : public Handler {

public:
  Terminate();
  virtual ~Terminate();

public:
  virtual void handle(void) const;

};

class Exit : public Handler {

public:
  Exit();
  virtual ~Exit();

public:
  virtual void handle(void) const;

};
