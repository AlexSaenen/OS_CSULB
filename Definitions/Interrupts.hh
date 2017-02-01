#include "Handler.hh"

class Initiate : public Handler {

public:
  Initiate();
  virtual ~Initiate();

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
