#include "local.h"



int flag = 1;
int wait_parent = 1;

void start();
void parent_handler();
void reconstruct_file(COLUMN columns[], int column, int rows);
void splitString(const char *str, const char *delimiter, char **ColNum, char ***result, int *count);
void decoding(int linesNum,int colNum,char ** fullColumn);


int main(int argc, char **argv)
{
	printf(RED "This is the [Master Spy] process\n" RESET);

	if (argc != 3)
	{
		printf("[Master Spy] missing arguments\n");
		exit(EXIT_FAILURE);
	}
    signal(SIGUSR1, start);
	signal(SIGUSR2, parent_handler);

	curr_pid = getpid();
	parent_pid = getppid();
	int indices = atoi(argv[0]);
	int rows = atoi(argv[1]);
	queid = atoi(argv[2]);
    int num_of_received_cols = 0;

	COLUMN columns[indices];
	for (int i = 0; i < indices; i++){
		columns[i].content = NULL;
	}
	int n;
	MESSAGE msg;
	

	while(1){
		if ((n = msgrcv(queid, &msg, BUFSIZ, SENDER, 0)) == -1)
		{
			perror("Master Spy: msgrcv");
			exit(-1);
		}

		//printf("Master Spy %d: %s\n", getpid(), msg.buffer);

		char *tempStr = strdup(msg.buffer);
		char *token = strtok(tempStr, " ");

		int ColNumber = atoi(token);
		char *temp;

		int count;

		if (columns[ColNumber-1].content == NULL){
			splitString(msg.buffer, " ", &temp, &columns[ColNumber-1].content, &count);
			decoding(count - 1, ColNumber, columns[ColNumber-1].content);
			/*for (int i = 0; i < count; i++)
			{
				printf("%d - %s\n", i, columns[ColNumber-1].content[i]);
			}*/

            printf(RED "[Master spy]: " RESET);
			for (int i = 0; i < rows; i++)
			{
				printf("%s ", columns[ColNumber-1].content[i]);
			}
            printf(RED "\n[Master spy]: num of received [%d]\n" RESET, num_of_received_cols);
            num_of_received_cols++;
		}
		else
		{
			printf(RED "[Master spy]: column [%d] dropped.\n" RESET, ColNumber-1);
		}

        if (num_of_received_cols == indices)
		{
			reconstruct_file(columns, indices, rows);
			kill(parent_pid, SIGUSR2);
			while (wait_parent)
			{
				pause();
			}
			wait_parent = 1;
			num_of_received_cols = 0;
			for (int i = 0; i < indices; i++)
			{
				columns[i].content = NULL;
			}
		}
	}
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
	FILE *file = fopen(SPY_FILE, "w");
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

void splitString(const char *str, const char *delimiter, char **ColNum, char ***result, int *count)
{
    char *tempStr = strdup(str); // Create a temporary copy of the original string

    // Count the number of tokens
    *count = 0;
    char *token = strtok(tempStr, delimiter);
    while (token != NULL)
    {
        (*count)++;
        token = strtok(NULL, delimiter);
    }

    // Allocate memory for the result array
    *(result) = (char **)malloc((*count) * sizeof(char *));

    // Tokenize the string and store each token in the result array
    int i = 0;
    token = strtok((char *)str, delimiter);
    while (token != NULL)
    {
        if (i == 0)
        {
            *(ColNum) = malloc(sizeof(char) * strlen(token));
            *(ColNum) = strdup(token);
        }
        
        (*result)[i] = malloc(sizeof(char) * strlen(token));
        (*result)[i] = strdup(token);
        
        i++;
        token = strtok(NULL, delimiter);
    }

    free(tempStr); // Free the temporary string copy
}

/*
    This method is used to decode the Full column
    all details is the opposite of the encoding method  
*/
void decoding(int linesNum,int colNum,char ** fullColumn){
    // go through all the words in the column
    for(int i=1;i<=linesNum;i++){
        char* tempString = (char*)malloc(sizeof(char) * strlen(fullColumn[i]));
        // go through all characters in each word
        int counter = 1;
        for(int j=0;j<strlen(fullColumn[i]);j++){
            int tmp;
            // if the char was Upper case alphabet
            if(fullColumn[i][j]>=65 && fullColumn[i][j] <= 90){
                tmp = fullColumn[i][j];
                tmp = 65 + (((tmp-65-counter*colNum)%26)+26)%26;
            }
            // if the char was Lower case alphabet
            else if(fullColumn[i][j]>=97 && fullColumn[i][j] <= 122){
                tmp = fullColumn[i][j];
                tmp = 97 + (((tmp-97-counter*colNum)%26)+26)%26;
            }
            // if the char was 9, which means it was a digit so we will go to the +5 character and 
            // check the orignal value
            else if(fullColumn[i][j] == 57){
                tmp = 58-fullColumn[i][j+5]+48;
                j+=5;
            }
            // if the char was 1 and the next char is 0, it means the value is 1,000,000. 
            // which means it was 0 digit
            else if(fullColumn[i][j] == 49 && j+1<strlen(fullColumn[i]) && fullColumn[i][j+1] == 48){
                tmp = 48;
                j+=6;
            }
            // if the char was other 6 possible characters (%?,!;:)
            else {
                switch(fullColumn[i][j]) {
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
                        tmp = 32 ;
                }
            }
            char result[2] ;
            sprintf(result, "%c", tmp);
            strcat(tempString, result);
            counter++;
        }
        
        // to save back the encoded result in the orignal text
        fullColumn[i] = tempString;
    }
}