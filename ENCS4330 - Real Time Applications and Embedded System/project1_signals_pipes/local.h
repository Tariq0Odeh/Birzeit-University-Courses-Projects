
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
#include <signal.h>
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */

void read_pipe_str(int fd_read, int fd_write, char *read_value, long length);
void write_pipe_str(int fd_read, int fd_write, char *write_value, long length);

#endif
