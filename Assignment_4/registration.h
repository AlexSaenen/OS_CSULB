
/*	Header file to be used with
*	shmp1.c and shmc1.c
*/

#include <semaphore.h>

struct CLASS { // data structure that will be shared between the children
  char class_number[6];
  char date[7];
  char title[50];
  int seats_left;
  sem_t semaphore; // added a semaphore variable in the data structure
};
