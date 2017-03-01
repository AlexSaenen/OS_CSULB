#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define REGULAR 1
#define MSGSIZE 255

using namespace std;

typedef struct message {
  long mtype;
  char mtext[MSGSIZE];
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
  strncpy(newMsg.mtext, input.c_str(), MSGSIZE);

  msgsnd(messageQueueID, &newMsg, sizeof(newMsg.mtext), 0);

  return 0;
}
