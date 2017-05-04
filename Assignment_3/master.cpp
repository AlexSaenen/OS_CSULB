// master.cpp
#include <string>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;

// subroutine called to create a message queue
int createMessageQueue(msqid_ds *queue) {
  int identifier = msgget((key_t)4242, 0600 | IPC_CREAT); // create the queue with key 4242

  if (identifier == -1) {
    cout << "Failed to get the message queue for identifier (" << identifier << ")" << endl;
  } else {
    // creation succeeded, get info about the queue
    msgctl(identifier, IPC_STAT, queue);
  }

  // return queue identifier for later deletion
  return identifier;
}

// subroutine called to delete the message queue
void deleteMessageQueue(int identifier, msqid_ds *queue) {
  // system call to delete a queue with a certain identifier
  msgctl(identifier, IPC_RMID, queue);
}

// subroutine called to instantiate a new child and execute a binary
int instantiateChild(string binaryName, string messageID) {
  // spawn a child process
  int pid = fork();

  if (pid == -1) {
    throw "Failed to fork";
  }

  if (pid == 0) {
    // this is the child process' code flow
    string pathToBinary("./" + binaryName); // create a valid binary path string
    char *pathArgument = new char[pathToBinary.length() + 1];
    char *messageArgument = new char[24];
    // convert string to char array for binary path and argument to send to the process
    strcpy(pathArgument, pathToBinary.c_str());
    strcpy(messageArgument, messageID.c_str());
    // create array to contain process arguments, especially the message queue id
    char *arguments[] = { pathArgument, messageArgument, 0 };
    // replace current process code by the binary sent as parameter
    execv(pathArgument, arguments);
    // if code goes until here: execv failed
    throw "Failed to exec";
  }

  // master process announces the new process, with pid and the binary it executes
  cout << "Created a " << binaryName << " with PID (" << pid << ")" << endl;
  return pid;
}

// make parent process wait for a child to terminate
void waitOnChild(int childPID) {
  int status;

  // use waitpid to wait for a specific process to terminate
  waitpid(childPID, &status, 0);
}


int main() {
  msqid_ds queue; // initiate a new message queue structure
  // create a new message queue and store info in our structure
  // remember the queue id
  int messageID = createMessageQueue(&queue);

  if (messageID == -1) {
    // creation of queue failed, exit
    return 1;
  }

  // create two childs, one to execute binary sender, and the other for receiver
  int senderPID = instantiateChild("sender", to_string(messageID));
  int receiverPID = instantiateChild("receiver", to_string(messageID));
  waitOnChild(receiverPID); // use receiver pid to wait for it's termination
  waitOnChild(senderPID); // use sender pid to wait for it's termination

  // both children terminated, we can safely delete the message queue
  deleteMessageQueue(messageID, &queue);
  return 0;
}
