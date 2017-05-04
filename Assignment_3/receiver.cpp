// receiver.cpp
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;

// define max message size
#define MSGSIZE 255

// our global message structure
typedef struct message {
  long mtype; // required, defines our message type
  char mtext[MSGSIZE]; // message content
} message;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    // we didn't receive the master's created message queue identifier
    return 1;
  }

  // get message queue identifier from arguments
  int messageQueueID = atoi(argv[1]);
  message newMsg; // initialize a new message structure

  // wait for the next message in the queue and store it in our structure
  msgrcv(messageQueueID, &newMsg, sizeof(newMsg.mtext), 0, 0);
  // identify the receiver's pid and display message content
  cout << "I'm the receiver (PID: " << getpid() << "), and got a new message:" << endl;
  cout << newMsg.mtext << endl;

  return 0;
}
