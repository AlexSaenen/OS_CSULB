#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;

#define REGULAR 1
#define MAX_MESSAGE_SIZE 255

typedef struct message {
  long mtype;
  char *mtext;
} message;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }

  int messageQueueID = atoi(argv[1]);

  message newMsg;
  newMsg.mtext = new char [MAX_MESSAGE_SIZE + 1];

  cout << msgrcv(messageQueueID, &newMsg, MAX_MESSAGE_SIZE, REGULAR, MSG_NOERROR) << endl;

  // cout << "I'm the receiver (PID: " << getpid() << "), and got a new message:" << endl;
  // cout << "text " << newMsg.mtext << " end text" << endl;
  // cout << "wtf is going onnnnnnnn" << endl;
  //
  // delete [] newMsg.mtext;

  return 0;
}
