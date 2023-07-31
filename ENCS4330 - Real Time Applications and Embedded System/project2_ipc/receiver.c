#include "local.h"

int flag = 1;
int wait_parent = 1;
void start();
void parent_handler();
void decoding(int linesNum, int colNum, char **fullColumn);
void reconstruct_file(COLUMN columns[], int column, int rows);
int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("[Receiver] missing arguments\n");
		exit(EXIT_FAILURE);
	}

	int ppid = getppid();
	int indices = atoi(argv[0]);
	int rows = atoi(argv[1]);
	int sleep_limit = atoi(argv[2]);

	int randomization_factor = 1;
	int column_num = 0;
	int num_of_received_cols = 0;

	curr_pid = getpid();
	parent_pid = getppid();
	signal(SIGUSR1, start);
	signal(SIGUSR2, parent_handler);
	COLUMN columns[indices];
	for (int i = 0; i < indices; i++)
	{
		columns[i].content = NULL;
	}

	printf(GREEN "This is the [Receiver] process\n" RESET);

	/*
	 * Access, attach and reference the shared memory
	 */
	if ((shmid = shmget((int)parent_pid, 0, 0)) != -1)
	{
		if ((shmptr = (char *)shmat(shmid, (char *)0, 0)) == (char *)-1)
		{
			perror("shmat -- [Receiver] -- attach");
			exit(1);
		}
		memptr = (struct MEMORY *)shmptr;
	}
	else
	{
		perror("shmget -- [Receiver] -- access");
		exit(2);
	}
	/*
	 * Access the semaphore set
	 */
	if ((semid = semget((int)parent_pid, 1, 0)) == -1)
	{
		perror("semget -- [Receiver] -- access");
		exit(3);
	}
	while (1)
	{
		srand(time(NULL) * (int)curr_pid * randomization_factor);

		int range = (indices - 1) - 0 + 1;
		int random_index = 0 + rand() % range;
		if (num_of_received_cols == indices)
		{
			printf(GREEN "Receiver got the msg.\n" RESET);
			reconstruct_file(columns, indices, rows);
			kill(parent_pid, SIGALRM);
			while (wait_parent)
			{
				pause();
			}
			wait_parent = 1;
			num_of_received_cols = 0;
			randomization_factor = 1;
			for (int i = 0; i < indices; i++)
			{
				columns[i].content = NULL;
			}
		}
		// printf("Receiver stuck here.\n");
		if (semop(semid, &acquire, 1) == -1)
		{
			perror("semop -- [Receiver] -- acquire");
			exit(4);
		}
		COLUMN temp_col;
		int cell_size = sizeof(memptr->column[0][0]) / sizeof(memptr->column[0][0][0]);
		temp_col.content = malloc(sizeof(char **) * rows);

		for (int j = 0; j < rows; j++)
		{
			temp_col.content[j] = malloc(sizeof(char *) * cell_size);
			strcpy(temp_col.content[j], memptr->column[random_index][j]);
		}
		column_num = atoi(temp_col.content[0]) - 1;
		if (columns[column_num].content == NULL)
		{
			decoding(rows, column_num + 1, temp_col.content);
			columns[column_num].content = malloc(sizeof(char *) * rows);
			for (int j = 0; j < rows; j++)
			{
				columns[column_num].content[j] = malloc(sizeof(char) * WORD_SIZE);
				strcpy(columns[column_num].content[j], temp_col.content[j]);
			}

			printf(GREEN "[Receiver]: " RESET);
			for (int i = 0; i < rows; i++)
			{
				printf("%s ", columns[column_num].content[i]);
			}
			printf(GREEN "\n[Receiver]: num of received [%d]\n" RESET, num_of_received_cols);
			num_of_received_cols++;
		}
		else
		{
			printf(GREEN "[Receiver]: column [%d] dropped.\n" RESET, column_num + 1);
		}

		randomization_factor += 1000;

		if (semop(semid, &release, 1) == -1)
		{
			perror("semop -- [Receiver] -- release");
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
void reconstruct_file(COLUMN columns[], int column, int rows)
{
	FILE *file = fopen(RECEIVER_FILE, "w");
	if (file == NULL)
	{
		printf("Failed to open the file.\n");
		return;
	}

	char line[BUFSIZ];
	for (int i = 1; i < rows; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (strcmp(columns[j].content[i], "alright") == 0)
				continue;
			if (j != 0)
				strcat(line, " ");
			strcat(line, columns[j].content[i]);
			//if (j < rows)
				
		}
		if (i < column - 1)
			strcat(line, "\n");
		fputs(line, file);
		memset(line, 0x0, BUFSIZ);
	}

	fclose(file);
}

/*
	This method is used to decode the Full column
	all details is the opposite of the encoding method
*/
void decoding(int linesNum, int colNum, char **fullColumn)
{
	// go through all the words in the column
	for (int i = 1; i < linesNum; i++)
	{
		char *tempString = (char *)malloc(sizeof(char) * strlen(fullColumn[i]));
		// go through all characters in each word
		int counter = 1;
		for (int j = 0; j < strlen(fullColumn[i]); j++)
		{
			int tmp;
			// if the char was Upper case alphabet
			if (fullColumn[i][j] >= 65 && fullColumn[i][j] <= 90)
			{
				tmp = fullColumn[i][j];
				tmp = 65 + (((tmp - 65 - counter * colNum) % 26) + 26) % 26;
			}
			// if the char was Lower case alphabet
			else if (fullColumn[i][j] >= 97 && fullColumn[i][j] <= 122)
			{
				tmp = fullColumn[i][j];
				tmp = 97 + (((tmp - 97 - counter * colNum) % 26) + 26) % 26;
			}
			// if the char was 9, which means it was a digit so we will go to the +5 character and
			// check the orignal value
			else if (fullColumn[i][j] == 57)
			{
				tmp = 58 - fullColumn[i][j + 5] + 48;
				j += 5;
			}
			// if the char was 1 and the next char is 0, it means the value is 1,000,000.
			// which means it was 0 digit
			else if (fullColumn[i][j] == 49 && j + 1 < strlen(fullColumn[i]) && fullColumn[i][j + 1] == 48)
			{
				tmp = 48;
				j += 6;
			}
			// if the char was other 6 possible characters (%?,!;:)
			else
			{
				switch (fullColumn[i][j])
				{
				case '1':
					tmp = 33;
					break;
				case '2':
					tmp = 63;
					break;
				case '3':
					tmp = 44;
					break;
				case '4':
					tmp = 59;
					break;
				case '5':
					tmp = 58;
					break;
				case '6':
					tmp = 37;
					break;
				default:
					tmp = 32;
				}
			}
			char result[2];
			sprintf(result, "%c", tmp);
			strcat(tempString, result);
			counter++;
		}

		// to save back the encoded result in the orignal text
		fullColumn[i] = tempString;
	}
}