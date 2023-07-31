#include "local.h"

int flag = 1;
int wait_parent = 1;
void start();
void parent_handler();
int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("[Helper] missing arguments\n");
		exit(EXIT_FAILURE);
	}

	int ppid = getppid();
	int indices = atoi(argv[0]);
	int rows = atoi(argv[1]);
	int sleep_limit = atoi(argv[2]);
	int randomization_factor = 1;
	curr_pid = getpid();
	signal(SIGUSR1, start);
	signal(SIGUSR2, parent_handler);

	printf(YELLOW "This is the helper Process %s\n" RESET, argv[0]);

	parent_pid = getppid();

	/*
	 * Access, attach and reference the shared memory
	 */
	if ((shmid = shmget((int)parent_pid, 0, 0)) != -1)
	{

		if ((shmptr = (char *)shmat(shmid, (char *)0, 0)) == (char *)-1)
		{
			perror("shmat -- [Helper] -- attach");
			exit(1);
		}
		memptr = (struct MEMORY *)shmptr;
	}
	else
	{
		perror("shmget -- [Helper] -- access");
		exit(2);
	}
	/*
	 * Access the semaphore set
	 */
	if ((semid = semget((int)parent_pid, 1, 0)) == -1)
	{
		perror("semget -- [Helper] -- access");
		exit(3);
	}
	while (1)
	{
		srand(time(NULL) * (int)curr_pid * randomization_factor);

		int range = (indices - 1) - 0 + 1;
		int firstRandomNumber = 0 + rand() % range;
		int updatedRange = range - 1;
		int secondRandomNumber = 0 + rand() % updatedRange;

		if (secondRandomNumber >= firstRandomNumber)
		{
			secondRandomNumber++;
		}
		if (flag == 0)
		{
			while (wait_parent)
			{
				pause();
			}
			wait_parent = flag = 1;
		}
		sleep(sleep_limit);
		if (semop(semid, &acquire, 1) == -1)
		{
			perror("semop -- [Helper] -- acquire");
			exit(4);
		}

		COLUMN temp_col;
		int cell_size = sizeof(memptr->column[0][0]) / sizeof(memptr->column[0][0][0]);
		temp_col.content = malloc(sizeof(char **) * rows);

		for (int j = 0; j < rows; j++)
		{
			temp_col.content[j] = malloc(sizeof(char *) * cell_size);
			strcpy(temp_col.content[j], memptr->column[firstRandomNumber][j]);
			strcpy(memptr->column[firstRandomNumber][j], memptr->column[secondRandomNumber][j]);
			strcpy(memptr->column[secondRandomNumber][j], temp_col.content[j]);
		}

		printf(YELLOW "[Helper]: swapping [%d] - [%d]\n" RESET, firstRandomNumber, secondRandomNumber);

		randomization_factor += 10;
		if (semop(semid, &release, 1) == -1)
		{
			perror("semop -- [Helper] -- release");
			exit(5);
		}
	}
	exit(EXIT_SUCCESS);
}

void start()
{
	flag = 0;
}

void parent_handler()
{
	wait_parent = 0;
}