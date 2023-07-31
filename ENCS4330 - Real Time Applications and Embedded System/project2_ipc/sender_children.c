#include "local.h"

void encoding(int linesNum, int colNum, char **fullColumn);
void splitString(const char *str, const char *delimiter, char **ColNum, char ***result, int *count);
int find_longest_word(COLUMN column, int len);
int main(int argc, char **argv)
{
    sleep(1);
    if (argc != 5)
    {
        printf("[Sender child] missing arguments\n");
        exit(EXIT_FAILURE);
    }
    parent_pid = atoi(argv[0]);
    int mid = atoi(argv[1]), n;
    int num_of_rows = atoi(argv[2]);
    int num_of_columns = atoi(argv[3]);
    int index = atoi(argv[4]);
    MESSAGE msg;
    int longest_word = 0;
    COLUMN columns[num_of_columns];
    COLUMN column;
    char *ColNumber;
    int count;

    /*printf("\n***********************************************************\n");
    printf("This is the sender children Process with the parent.c pid = %s\n", argv[0]);*/

    if ((n = msgrcv(mid, &msg, BUFSIZ, SENDER, 0)) == -1)
    {
        perror("Sender Children: msgrcv");
        exit(-1);
    }
    // kill(getppid(),SIGUSR2);

    printf("children.c: %s\n", msg.buffer);

    splitString(msg.buffer, " ", &ColNumber, &column.content, &count);

    encoding(count - 1, atoi(ColNumber), column.content);
    column.content[0] = malloc(10);
    strcat(column.content[0], ColNumber);
    /*for (int i = 0; i < count; i++)
    {
        printf("%d - %s\t", i, column.content[i]);
    }
    printf("\n***********************************************************\n");*/
    longest_word = find_longest_word(column, count);

    

    /*
     * Access, attach and reference the shared memory
     */
    if ((shmid = shmget((int)parent_pid, 0, 0)) != -1)
    {
        if ((shmptr = (char *)shmat(shmid, (char *)0, 0)) == (char *)-1)
        {
            perror("shmat -- [Sender child] -- attach");
            exit(1);
        }
        memptr = (struct MEMORY *)shmptr;
    }
    else
    {
        perror("shmget -- [Sender child] -- access");
        exit(2);
    }

    /*
     * Access the semaphore set
     */
    if ((semid = semget((int)parent_pid, 1, 0)) == -1)
    {
        perror("semget -- [Sender child] -- access");
        exit(3);
    }

    if (semop(semid, &acquire, 1) == -1)
    {
        perror("semop -- [Sender child] -- acquire");
        exit(4);
    }

    memptr->size = num_of_columns;
    memptr->head = num_of_rows + 1;

    for (int i = 0; i < count; i++)
    {
        strcpy(memptr->column[memptr->tail][i], column.content[i]);
    }

    /*for (int i = 0; i < count; i++)
    {
        printf("[%d] - %s\t", i, memptr->column[index][i]);
    }
    printf("\n");*/
    int no_of_columns = sizeof(memptr->column) / sizeof(memptr->column[0]);
    memptr->tail = (memptr->tail + 1) % no_of_columns;
    shmdt(shmptr);
    usleep(500);
    kill(getppid(),SIGUSR1);
    if (semop(semid, &release, 1) == -1)
    {
        perror("semop -- [Sender child] -- release");
        exit(5);
    }
    printf("\nThe [sender child] process %d has been finised", getpid());
    exit(0);
}

/*
    This method is used to encode the Full column
    all details is the opposite of the decoding method
*/
void encoding(int linesNum, int colNum, char **fullColumn)
{
    // go through all the words in the column
    for (int i = 1; i <= linesNum; i++)
    {
        // here we multiply by 7, because the digit 0 will be converted to 1,000,000 (7 characters)
        char *tempString = (char *)malloc(sizeof(char) * strlen(fullColumn[i]) * 7);
        // go through all characters in each word
        for (int j = 0; j < strlen(fullColumn[i]); j++)
        {
            int flag = 0;
            int tmp;
            // if the char was Upper case alphabet
            if (fullColumn[i][j] >= 65 && fullColumn[i][j] <= 90)
            {
                tmp = fullColumn[i][j];
                tmp = 65 + (tmp - 65 + (j + 1) * colNum) % 26;
            }
            // if the char was Lower case alphabet
            else if (fullColumn[i][j] >= 97 && fullColumn[i][j] <= 122)
            {
                tmp = fullColumn[i][j];
                tmp = 97 + (tmp - 97 + (j + 1) * colNum) % 26;
            }
            // if the char was digit
            else if (fullColumn[i][j] >= 48 && fullColumn[i][j] <= 57)
            {
                tmp = fullColumn[i][j] - 48;
                tmp = 1000000 - tmp;
                flag = 1;
            }
            // if the char was other 6 possible characters (%?,!;:)
            else
            {
                switch (fullColumn[i][j])
                {
                case '!':
                    tmp = 48 + 1;
                    break;
                case '?':
                    tmp = 48 + 2;
                    break;
                case ',':
                    tmp = 48 + 3;
                    break;
                case ';':
                    tmp = 48 + 4;
                    break;
                case ':':
                    tmp = 48 + 5;
                    break;
                case '%':
                    tmp = 48 + 6;
                    break;
                default:
                    tmp = 32;
                }
            }
            // any case except the digit case, because each digit will be 6 digits or even 7
            if (!flag)
            {
                char result[2];
                sprintf(result, "%c", tmp);
                strcat(tempString, result);
            }
            // if the char was a digit
            else
            {
                sprintf(tempString, "%s%d", tempString, tmp);
            }
        }
        // to save back the encoded result in the orignal text
        fullColumn[i] = tempString;
    }
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
        else
        {
            (*result)[i] = malloc(sizeof(char) * strlen(token));
            (*result)[i] = strdup(token);
        }
        i++;
        token = strtok(NULL, delimiter);
    }

    free(tempStr); // Free the temporary string copy
}

int find_longest_word(COLUMN column, int len)
{
    int max_len = 0, temp_len = 0;
    for (int i = 0; i < len; i++)
    {
        temp_len = strlen(column.content[i]);
        max_len = temp_len > max_len ? temp_len : max_len;
    }
    return max_len;
}