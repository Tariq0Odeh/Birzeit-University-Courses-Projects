#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void read_pipe_str(int fd_read, int fd_write, char *read_value, long length)
{
	close(fd_write);
	if (read(fd_read, &(*read_value), length) == -1)
	{
		perror("Read pipe");
		exit(-11);
	}
}
void write_pipe_str(int fd_read, int fd_write, char *write_value, long length)
{
	close(fd_read);
	if (write(fd_write, &(*write_value), length) == -1)
	{
		perror("Write pipe");
		exit(-12);
	}
}
