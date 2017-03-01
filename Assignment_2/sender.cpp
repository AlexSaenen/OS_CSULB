#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define REGULAR 1

using namespace std;

typedef struct message {
  long mtype;
  char *mtext;
} message;

int main(int argc, char *argv[]) {
  string input;
  if (argc != 2) {
    return 1;
  }

  int messageQueueID = atoi(argv[1]);

  cout << "Hi, I'm the sender (PID: " << getpid() << "), ";
  cout << "Let me send something : ";
  cin >> input;

  message newMsg;
  newMsg.mtype = REGULAR;
  newMsg.mtext = new char [input.length() + 1];
  strcpy(newMsg.mtext, input.c_str());

  msgsnd(messageQueueID, &newMsg, input.length(), 0);

  delete [] newMsg.mtext;

  return 0;
}
