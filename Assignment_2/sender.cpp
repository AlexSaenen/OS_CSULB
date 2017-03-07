#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// define our message type and message max size
#define REGULAR 1
#define MSGSIZE 255

using namespace std;

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
  newMsg.mtype = REGULAR; // set our message type to REGULAR

  // identify the sender's pid and wait on command prompt for user input
  // and store the input in our message structure's content, truncate at message max size
  cout << "Hi, I'm the sender (PID: " << getpid() << "), ";
  cout << "Let me send something : ";
  cin.getline(newMsg.mtext, MSGSIZE);
  // send the message and exit
  msgsnd(messageQueueID, &newMsg, sizeof(newMsg.mtext), 0);

  return 0;
}
