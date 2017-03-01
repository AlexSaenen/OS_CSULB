#include <unistd.h>
#include <sys/wait.h>
#include "Child.hh"

Child::Child(string binaryName) {
  _pid = fork();

  if (_pid == -1) {
    throw "Failed to fork";
  }

  if (this->isParent() == false) {
    string pathToBinary("./" + binaryName);

    char arguments = [2][7] = {
      pathToBinary.c_str(),
      0,
    };

    execv(pathToBinary.c_str(), arguments);
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
