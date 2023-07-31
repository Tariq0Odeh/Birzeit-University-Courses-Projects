#include "local.h"

int flag = 1;
int wait_parent = 1;
void start();
void parent_handler();

int main(int argc, char **argv){

	//printf("This is one of the spy Processes\n");

	if (argc != 4)
	{
		printf("[Spy] missing arguments\n");
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, start);
	signal(SIGUSR2, parent_handler);
	
	int indices = atoi(argv[0]);
	int rows = atoi(argv[1]);
	queid = atoi(argv[2]);
	int sleep_limit = atoi(argv[3]);
	//rows++;
	

	int randomization_factor = 1;
	int column_num = 0;
	int num_of_received_cols = 0;

	curr_pid = getpid();
	parent_pid = getppid();


	/*
	 * Access, attach and reference the shared memory
	 */
	if ((shmid = shmget((int)parent_pid, 0, 0)) != -1)
	{
		if ((shmptr = (char *)shmat(shmid, (char *)0, 0)) == (char *)-1)
		{
			perror("shmat -- [Spy] -- attach");
			exit(1);
		}
		memptr = (struct MEMORY *)shmptr;
	}
	else
	{
		perror("shmget -- [Spy] -- access");
		exit(2);
	}
	
	/*
	 * Access the semaphore set
	 */
	if ((semid = semget((int)parent_pid, 1, 0)) == -1)
	{
		perror("semget -- [Spy] -- access");
		exit(3);
	}

	char **randomColumn;
	MESSAGE msg;


	while (1)
	{
		srand(time(NULL) * (int)curr_pid * randomization_factor);

		int range = (indices - 1) - 0 + 1;
		int random_index = 0 + rand() % range;
		if (flag == 0){
			while(wait_parent){
				pause();
			}	
			wait_parent = flag = 1;
		}
		if (semop(semid, &acquire, 1) == -1)
		{
			perror("semop -- [Spy] -- acquire");
			exit(4);
		}
		
		//printf("Test 1.\n");
		randomColumn = malloc(sizeof(char *) * rows);
		//printf("Rows %d\n",rows);
		for (int j = 0; j < rows; j++)
		{
			randomColumn[j] = malloc(sizeof(char) * 50);
		}

		COLUMN temp_col;
		int cell_size = sizeof(memptr->column[0][0]) / sizeof(memptr->column[0][0][0]);
		temp_col.content = malloc(sizeof(char **) * rows);

		for (int j = 0; j < rows; j++)
		{
			temp_col.content[j] = malloc(sizeof(char *) * cell_size);
			strcpy(temp_col.content[j], memptr->column[random_index][j]);
		}
		//printf("Test 3.\n");
		column_num = atoi(temp_col.content[0]);
		//decoding(column_num, 0, temp_col.content);
		//printf("Test 4.\n");
		for (int j = 0; j < rows; j++)
		{
			strcpy(randomColumn[j], temp_col.content[j]);
		}
		//printf("Test 5.\n");
		/*printf("Spy [%d].\n",curr_pid);
		for (int i = 0; i < rows; i++)
		{
			printf("%s\t", randomColumn[i]);
		}
		printf("\n");/**/

		msg.msg_fm = getpid();
		msg.msg_to = SENDER;
		memset(msg.buffer, 0x0, BUFSIZ);

		int n = 11;
		for (int j = 0; j < rows; j++)
		{
			strcat(msg.buffer, randomColumn[j]);
			strcat(msg.buffer, " ");
			n += strlen(randomColumn[j]) * sizeof(char);
			n += sizeof(char);
		}
		//printf("spy.c: %s \n", msg.buffer);
		n += sizeof(msg.msg_fm);

		if (msgsnd(queid, &msg, n, 0) == -1)
		{
			perror("[Spy] msgsend");
			exit(-4);
		}
		
		randomization_factor += 10;

		if (semop(semid, &release, 1) == -1)
		{
			perror("semop -- [Spy] -- release");
			exit(5);
		}

		sleep(sleep_limit);
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