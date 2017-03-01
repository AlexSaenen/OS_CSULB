#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;

int main() {
  cout << "Hi, I'm the receiver" << endl;
  return 0;
}
