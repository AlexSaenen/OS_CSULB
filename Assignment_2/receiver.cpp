#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;

#define MSGSIZE 255

typedef struct message {
  long mtype;
  char mtext[MSGSIZE];
} message;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }

  int messageQueueID = atoi(argv[1]);
  message newMsg;

  msgrcv(messageQueueID, &newMsg, sizeof(newMsg.mtext), 0, 0);

  cout << "I'm the receiver (PID: " << getpid() << "), and got a new message:" << endl;
  printf("%s\n", newMsg.mtext);

  return 0;
}
