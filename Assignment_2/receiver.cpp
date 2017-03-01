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

  int ret = msgrcv(messageQueueID, &newMsg, sizeof(newMsg.mtext), 0, 0);

  cout << ret << endl;
  cout << "working ?" << endl;
  cout << newMsg.mtype << endl;
  cout << newMsg.mtext[0] << endl;

  newMsg.mtext[ret] = 0;

  // cout << "I'm the receiver (PID: " << getpid() << "), and got a new message:" << endl;
  cout << newMsg.mtext[0] << endl;
  cout << "text " << newMsg.mtext << " end text" << endl;
  // cout << "wtf is going onnnnnnnn" << endl;
  //
  // delete [] newMsg.mtext;

  return 0;
}
