#include <string>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;

int createMessageQueue(msqid_ds *queue) {
  int identifier = msgget((key_t)4242, 0666 | IPC_CREAT);

  if (identifier == -1) {
    cout << "Failed to get the message queue for identifier (" << identifier << ")" << endl;
  } else {
    msgctl(identifier, IPC_STAT, queue);
  }

  return identifier;
}

void deleteMessageQueue(int identifier, msqid_ds *queue) {
  msgctl(identifier, IPC_RMID, queue);
}

int instantiateChild(string binaryName, string messageID) {
  int pid = fork();

  if (pid == -1) {
    throw "Failed to fork";
  }

  if (pid == 0) {
    string pathToBinary("./" + binaryName);
    char *pathArgument = new char[pathToBinary.length() + 1];
    char *messageArgument = new char[24];
    strcpy(pathArgument, pathToBinary.c_str());
    strcpy(messageArgument, messageID.c_str());
    char *arguments[] = { pathArgument, messageArgument, 0 };
    execv(pathArgument, arguments);
    throw "Failed to exec";
  }

  cout << "Created a " << binaryName << " with PID (" << pid << ")" << endl;
  return pid;
}

void waitOnChild(int childPID) {
  int status;

  waitpid(childPID, &status, 0);
}


int main() {
  msqid_ds queue;
  int messageID = createMessageQueue(&queue);

  if (messageID == -1) {
    return 1;
  }

  int senderPID = instantiateChild("sender", to_string(messageID));
  int receiverPID = instantiateChild("receiver", to_string(messageID));
  waitOnChild(senderPID);
  waitOnChild(receiverPID);

  deleteMessageQueue(messageID, &queue);
  return 0;
}
