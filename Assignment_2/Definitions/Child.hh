#pragma once

#include <string>

using namespace std;

class Child {

private:
  int _pid;

public:
  Child(string binaryName);
  ~Child();

private:
  bool isParent();

};
