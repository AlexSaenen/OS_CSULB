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

CLASS myclass = { "1001", "120186", "Operating Systems", 15 }; // Data for OS class that will be used concurrently

#define NCHILD	3

int	shm_init( void * );
void	wait_and_wrap_up( int [], void *, int );
void	rpterror( char *, char * );


int main(int argc, char *argv[]) {
  int child[NCHILD], i, shmid, semid;
  void	*shm_ptr;
  char	ascshmid[10], ascsemid[10], pname[14];

  // initializing the semaphore to 1 and setting it as shareable between processes
  if (sem_init(&(myclass.semaphore), 1, 1) < 0) {
    perror("Failed to create semaphore");
  }

  strcpy (pname, argv[0]); // extract child name parameter from arguments
  shmid = shm_init(shm_ptr); // initialize shared memory and store its id
  sprintf (ascshmid, "%d", shmid); // put semaphore id in string

  for (i = 0; i < NCHILD; i++) { // for every desired child
    // create a new process and if successful, replace child's code with the shmc1 program
    child[i] = fork();
    switch (child[i]) {
      case -1:
        rpterror ("fork failure", pname);
        exit(1);
      case 0:
        // child will have as name, the argument given to this program, append with nth child position
        sprintf (pname, "shmc%d", i+1);
        // replace code with shmc1 program code, send as arguments the child name, and shared memory section identifier
        execl("shmc1", pname, ascshmid, (char *)0);
        perror ("execl failed");
        exit (2);
    }
  }

  wait_and_wrap_up (child, shm_ptr, shmid); // call routine to handle wait and clean up
}

int shm_init(void *shm_ptr) {
  int	shmid;

  // create a shared memory section, with as identifier a key generated using current directory pathname
  // the memory section will have just enough size to store a CLASS data structure
  shmid = shmget(ftok(".",'u'), sizeof(CLASS), 0600 | IPC_CREAT);

  if (shmid == -1) {
    perror ("shmget failed");
    exit(3);
  }

  // get a pointer to the newly allocated shared memory section
  shm_ptr = shmat(shmid, (void * ) 0, 0);

  if (shm_ptr == (void *) -1) {
    perror ("shmat failed");
    exit(4);
  }

  // store our initialized data structure in our shared memory section
  memcpy (shm_ptr, (void *) &myclass, sizeof(CLASS) );
  // return identifier of the shared memory section we created
  return (shmid);
}

void wait_and_wrap_up(int child[], void *shm_ptr, int shmid) {
  int wait_rtn, w, ch_active = NCHILD;

  while (ch_active > 0) { // as long as some children are busy
    wait_rtn = wait( (int *)0 ); // wait for a child to finish

    for (w = 0; w < NCHILD; w++) // loop on children to find which one exited
      if (child[w] == wait_rtn) {
        ch_active--; // one less child to wait on
        break;
      }
  }

  cout << "Parent removing shm" << endl;
  shmdt (shm_ptr); // detach shared memory section so the pointer no longer points to that adress
  shmctl (shmid, IPC_RMID, (struct shmid_ds *) 0); // delete our shared memory section
  sem_destroy(&(myclass.semaphore)); // destroy the semaphore
  exit (0);
}

void rpterror(char *string, char *pname) {
  char errline[50];

  sprintf (errline, "%s %s", string, pname);
  perror (errline);
}
