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

int getMessageQueue(int identifier, msqid_ds *queue) {
  return msgctl(identifier, IPC_STAT, queue);
}

int main() {
  string input;
  msqid_ds queue;

  cout << "Hi, I'm the sender (PID: " << getpid() << "), ";
  cout << "Let me send something : ";
  cin >> input;

  if (getMessageQueue(IPC_PRIVATE, &queue) == -1) {
    cout << "Sender failed to get message queue" << endl;
  }

  message newMsg;
  newMsg.mtype = REGULAR;
  newMsg.mtext = new char [input.length() + 1];
  strcpy(newMsg.mtext, input.c_str());

  msgsnd(IPC_PRIVATE, &newMsg, input.length(), 0);

  delete [] newMsg.mtext;

  return 0;
}
