#pragma once

class   Handler {

public:
  Handler();
  virtual ~Handler();

public:
  virtual void handle(void) const = 0;

};
