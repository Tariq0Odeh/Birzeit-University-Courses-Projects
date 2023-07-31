
/*
 * local header file for pipe client-server
 */

#ifndef __LOCAL_H_
#define __LOCAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <wait.h>
#include <signal.h>
#include <sys/msg.h>
#include <ctype.h>
#include <stdbool.h>
#include <GL/glut.h>


#define RESET "\033[0m"
#define RED "\033[31m"   /* Red */
#define GREEN "\033[32m" /* Green */
#define BLUE "\033[34m" /*Blue*/
#define YELLOW "\033[33m"
#define PURPLE "\033[35m" 

//#define N_SLOTS 6
#define SENDER_FILE "sender.txt"
#define RECEIVER_FILE "receiver.txt"
#define SPY_FILE "spy.txt"
#define COL 100
#define ROW 100
#define WORD_SIZE 50
#define LINE_MAX_LENGTH 1000


#define SEED 'g'  /* seed for ftok */
#define SENDER 1L /* message for the server */

typedef struct
{
  long msg_to;         /* Placed in the queue for */
  long msg_fm;         /* Placed in the queue by  */
  char buffer[BUFSIZ]; /* Column */
} MESSAGE;

union semun
{
  int val;
  struct semid_ds *buf;
  ushort *array;
};

struct MEMORY
{
  char column[COL][ROW][WORD_SIZE];
  int head, tail;
  int size;
};

struct sembuf acquire = {0, -1, SEM_UNDO},
              release = {0, 1, SEM_UNDO};

enum
{
  AVAIL_SLOTS,
  TO_CONSUME
};

typedef struct
{
  char **content;
} COLUMN;

int semid, shmid, queid;
char *shmptr;
struct MEMORY *memptr;
pid_t parent_pid, curr_pid;
#endif