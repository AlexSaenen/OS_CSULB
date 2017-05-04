// use_msgQ.cpp
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
using namespace std;

// declare my global message buffer
struct buf {
  long mtype; // required
  char greeting[50]; // message content
};

// function that child one executes
void child_proc_one(int qid) {
  buf msg; // initialize a new message buffer
  // define the size to be the length of the greeting string
  int size = sizeof(msg) - sizeof(long);
  // prepare to receive or find the first message with message type 113
  // and tell that the max message length is 50 characters long
  msgrcv(qid, (struct msgbuf *)&msg, size, 113, 0);
  cout << getpid() << ": gets message" << endl; // identify child one's pid
  cout << "message: " << msg.greeting << endl; // and display the message content
  // take the received message content and add a string at the end
  strcat(msg.greeting, " and Adios.");
  // identify child one's pid
  cout << getpid() << ": sends reply" << endl;
  msg.mtype = 114; // prepare message with type mtype = 114
  msgsnd(qid, (struct msgbuf *)&msg, size, 0); // send the modified message
  // identify child one's pid and announce termination of process
  cout << getpid() << ": now exits" << endl;
}

void child_proc_two(int qid) {
  buf msg; // initialize a new message buffer
  // define the size to be the length of the greeting string
  int size = sizeof(msg) - sizeof(long);
  // sending a message that will never be read
  msg.mtype = 12; // set message type to 12
  // Copy a string to new message's content variable 'greeting'
  strcpy(msg.greeting, "Fake message");
  msgsnd(qid, (struct msgbuf *)&msg, size, 0); // send the message with type 12
  // prepare my message to send
  strcpy(msg.greeting, "Hello there");
  // identify child two's pid
  cout << getpid() << ": sends greeting" << endl;
  msg.mtype = 113; // set message type mtype = 113
  msgsnd(qid, (struct msgbuf *)&msg, size, 0); // send the message
  // prepare to receive or find the first message with message type 114
  // and tell that the max message length is 50 characters long
  msgrcv(qid, (struct msgbuf *)&msg, size, 114, 0);
  // identify child two's pid
  cout << getpid() << ": gets reply" << endl;
  // display the received message's content
  cout << "reply: " << msg.greeting << endl;
  // identify child two's pid and announce termination of process
  cout << getpid() << ": now exits" << endl;
}

int main() {
  // create a new private message queue with permissions 0600
  // fail if the queue already exists
  int qid = msgget(IPC_PRIVATE, IPC_EXCL|IPC_CREAT|0600);
  //spawning two child processes
  pid_t cpid = fork();

  if (cpid == 0) {
    // we are in the child process, execute the corresponding code
    child_proc_one(qid);
    exit(0);
  }

  // second spawn
  cpid = fork();

  if (cpid == 0) {
    // this is part of second's child process' code
    // call the corresponding function with code destined for child two
    child_proc_two(qid);
    exit(0);
  }

  while(wait(NULL) != -1); // waiting for both children to terminate

  // both children exited, we can now safely delete the message queue
  msgctl(qid, IPC_RMID, NULL);
  // identify the master process' pid and announce termination of process
  cout << "parent proc: " << getpid() << " now exits" << endl;

  exit(0);
}
