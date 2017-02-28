#pragma once

// Abstract Class from which all Menu Selection Handlers will inherit from
class   Handler {

public:
  Handler() {};
  virtual ~Handler() {};

public:
  virtual void handle(void) const = 0;

};
