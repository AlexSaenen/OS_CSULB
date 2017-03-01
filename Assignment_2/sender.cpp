#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
  string input;

  cout << "Hi, I'm the sender (PID: " << getpid() << "), ";
  cout << "Let me send something : ";
  cin >> input;
  return 0;
}
