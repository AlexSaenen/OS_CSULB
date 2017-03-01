#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
#include "Child.hh"

Child::Child(string binaryName) {
  _pid = fork();

  if (_pid == -1) {
    throw "Failed to fork";
  }

  if (this->isParent() == false) {
    string pathToBinary("./" + binaryName);
    char *pathArgument = new char[pathToBinary.length() + 1];
    strcpy(pathArgument, pathToBinary.c_str());
    char *arguments[] = { pathArgument, 0 };
    execv(pathArgument, arguments);
    delete [] pathArgument;
    throw "Failed to exec";
  }
}

Child::~Child() {
  int status;

  waitpid(_pid, &status, 0);
}

bool Child::isParent() {
  return _pid != 0;
}
