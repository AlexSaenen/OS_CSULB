#pragma once

class Child {

private:
  int _pid;

public:
  Child(string binaryName);
  ~Child();

private:
  bool isParent();

};
