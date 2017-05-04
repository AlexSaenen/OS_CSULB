
#include "registration.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <memory.h>
using namespace std;

CLASS *class_ptr;
void *memptr;
char	*pname;
int	shmid, ret;

void rpterror(char *), srand(), perror(), sleep();
void sell_seats();

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf (stderr, "Usage:, %s shmid\n", argv[0]);
    exit(1);
  }

  // retrieve child name from arguments
  pname = argv[0];
  sscanf (argv[1], "%d", &shmid); // convert the shared memory section the parent sent us to an int
  // attach a pointer to the shared memory section of which we received its identifier
  memptr = shmat (shmid, (void *)0, 0);

  if (memptr == (char *)-1 ) {
    rpterror ("shmat failed");
    exit(2);
  }

  class_ptr = (struct CLASS *)memptr; // set a pointer to the data structure that is stored in memory
  sell_seats(); // call our consumer routine
  ret = shmdt(memptr); // detach our pointer from the shared memory section
  exit(0);
}

void sell_seats() {
  int all_out = 0;

  srand ( (unsigned) getpid() ); // generate a seed for random routine using our pid
  while ( !all_out) { /* loop to sell all seats */
    if (sem_wait(&(class_ptr->semaphore)) == -1) {
      rpterror ("sem_wait failed");
    }

    printf("Entered\n");

    if (class_ptr->seats_left > 0) { // if there are seats left in shared data structure
      sleep ( (unsigned)rand()%5 + 1); // wait a random amount of time between 1 and 5 seconds
      class_ptr->seats_left--; // sell a seat
      sleep ( (unsigned)rand()%5 + 1); // wait a random amount of time between 1 and 5 seconds
      cout << pname << " SOLD SEAT -- "
      << class_ptr->seats_left << " left" << endl; // display amount of seats left

    } else {
      all_out++; // no more seats left
      cout << pname << " sees no seats left" << endl;
    }

    if (sem_post(&(class_ptr->semaphore)) == -1) {
      rpterror ("sem_post failed");
    }
    printf("Left\n");

    sleep ( (unsigned)rand()%10 + 1); // wait a random amount of time between 1 and 10 seconds
  }
}

void rpterror(char* string) {
  char errline[50];
  sprintf (errline, "%s %s", string, pname);
  perror (errline);
}
