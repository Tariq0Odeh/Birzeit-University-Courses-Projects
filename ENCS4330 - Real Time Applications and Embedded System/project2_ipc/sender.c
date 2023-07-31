#include "local.h"

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

pid_t sender_pid;
int counter = 0;

int count_words(char *line);
void sender_handler();
int find_longest_column(FILE *file);
int find_longest_line(FILE *file);
int find_longest_word(FILE *file);

void removeEmptyLinesAndExtraSpaces(const char *inputFilePath, const char *outputFilePath);

int main(int argc, char *argv[])
{
    sender_pid = getpid();
    parent_pid = getppid();
    printf("This is the [Sender] process %d\n", sender_pid);
    removeEmptyLinesAndExtraSpaces("sender.txt", "temp.txt");
    FILE *file;
    int num_of_columns = 0, num_of_rows = 0, longest_length = 0;
    pid_t child_pid;
    

    key_t key;
    int mid, n;
    MESSAGE msg;
    static char m_key[10];

    signal(SIGUSR1, sender_handler);

    file = fopen(SENDER_FILE, "r");
    if (file == NULL)
    {
        printf("Sender.c - Unable to open the file.\n");
        exit(-1);
    }

    num_of_columns = find_longest_line(file);
    file = fopen(SENDER_FILE, "r");
    num_of_rows = find_longest_column(file);
    file = fopen(SENDER_FILE, "r");
    longest_length = find_longest_word(file);

    printf("Num of columns [%d]\n", num_of_columns);

    printf("Longest word [%d]\n", longest_length);

    int children_pid[num_of_columns];
    COLUMN columns[num_of_columns];

    for (int i = 0; i < num_of_columns; i++)
    {
        columns[i].content = malloc(sizeof(char *) * num_of_rows);
        for (int j = 0; j < num_of_rows; j++)
        {
            columns[i].content[j] = malloc(sizeof(char) * longest_length);
        }
    }

    char line[LINE_MAX_LENGTH];
    int col_num = 0, row_num = 0;
    file = fopen(SENDER_FILE, "r");

    while (fgets(line, LINE_MAX_LENGTH, file))
    {
        if (line[0] == EOF || strcmp(line, "\n") == 0 || strcmp(line, " ") == 0)
        {
            continue;
        }
        char *token = strtok(line, " \t\n");
        col_num = 0;
        while (token != NULL && col_num < num_of_columns)
        {
            // printf("[%d][%d] %s\n", col_num + 1, row_num, token);
            strcpy(columns[col_num++].content[row_num], token);
            token = strtok(NULL, " \t\n");
            // usleep(500);
        }

        for (int i = col_num; i < num_of_columns; i++)
        {
            strcpy(columns[col_num++].content[row_num], "alright");
        }

        row_num++;
    }
    printf("Num of rows [%d]\n", num_of_rows);

    fclose(file);
    /*
     *displaying the columns
     */
    /*for (int i = 0; i < num_of_columns; i++)
    {
        for (int j = 0; j < num_of_rows; j++)
        {
            printf("%s ", columns[i].content[j]);
        }
        printf("\n");
    }*/

    if ((key = ftok(".", SEED)) == -1)
    {
        perror("Sender: key generation");
        exit(-2);
    }
    if ((mid = msgget(key, 0)) == -1)
    {
        mid = msgget(key, IPC_CREAT | 0777);
    }
    printf("\n");
    // to fork the depending on the number of columns in the file children and then execute them
    for (int i = 0; i < num_of_columns; i++)
    {
        child_pid = fork();

        if (child_pid == -1)
        {
            printf("Sender.c - Error with forking\n");
            exit(-3);
        }
        // if the child_pid not zero, that means we are in the parent, so we save the child pid
        else if (getpid() == sender_pid)
        {
            children_pid[i] = child_pid;
        }
        else if (child_pid == 0)
        {
            msg.msg_fm = getpid();
            msg.msg_to = SENDER;
            memset(msg.buffer, 0x0, BUFSIZ);

            n = 11;
            sprintf(msg.buffer, "%d ", i + 1);
            for (int j = 0; j < num_of_rows; j++)
            {
                strcat(msg.buffer, columns[i].content[j]);
                strcat(msg.buffer, " ");
                n += strlen(columns[i].content[j]) * sizeof(char);
                n += sizeof(char);
            }
            n += sizeof(msg.msg_fm);

            if (msgsnd(mid, &msg, n, 0) == -1)
            {
                perror("[Sender] msgsend");
                exit(-4);
            }

            char parent_pid_str[10], numOfRows[10], num_of_columns_str[10], index[10];
            sprintf(parent_pid_str, "%d", parent_pid);
            sprintf(m_key, "%d", mid);
            sprintf(numOfRows, "%d", num_of_rows);
            sprintf(num_of_columns_str, "%d", num_of_columns);
            sprintf(index, "%d", i);

            if (execl("./sender_children", parent_pid_str, m_key, numOfRows, num_of_columns_str, index, NULL) == -1)
            {
                perror("[Sender] error with Executing sender_children");
                exit(-4);
            }
            exit(1);
        }
    }
    while (1)
    {
        while (counter < num_of_columns)
        {
            pause();
        }
        kill(parent_pid, SIGUSR1);
        msgctl(mid, IPC_RMID, NULL);
        break;
    }
    printf("\n\n********************\n\n");

    return 0;
}

int count_words(char *line)
{
    int wordCount = 0;
    int isWord = 0;

    for (int i = 0; line[i] != '\0'; i++)
    {
        if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
        {
            isWord = 0;
        }
        else if (isWord == 0)
        {
            isWord = 1;
            wordCount++;
        }
    }

    return wordCount;
}

void sender_handler()
{
    counter++;
    return;
}

int find_longest_column(FILE *file)
{
    int numRows = 0;
    char line[LINE_MAX_LENGTH];

    while (fgets(line, LINE_MAX_LENGTH, file))
    {
        if (line[0] == EOF || strcmp(line, "\n") == 0 || strcmp(line, " ") == 0)
        {
            continue;
        }
        numRows++;
    }
    return numRows;
}

int find_longest_line(FILE *file)
{
    char line[BUFSIZ];
    char *longest_line;
    int longestLineLength = 0;
    int LineCount = 0;
    /*
     * finds the longest line
     */
    while (fgets(line, BUFSIZ, file))
    {
        LineCount++;
        int currentLineLength = strlen(line);
        if (currentLineLength > longestLineLength)
        { // Check if the current line is the longest
            longestLineLength = currentLineLength;
            longest_line = malloc(sizeof(line));
            strcpy(longest_line, line);
        }
    }
    return count_words(longest_line);
}

int find_longest_word(FILE *file)
{
    char c;
    char longest_word[LINE_MAX_LENGTH];
    int longest_length = 0;
    char current_word[LINE_MAX_LENGTH];
    int current_length = 0;

    while ((c = fgetc(file)) != EOF)
    {
        if (isalpha(c))
        {
            current_word[current_length++] = c;
        }
        else
        {
            if (current_length > longest_length)
            {
                longest_length = current_length;
                strncpy(longest_word, current_word, longest_length);
            }
            current_length = 0;
        }
    }

    // Check the last word in case the file doesn't end with a non-letter character
    if (current_length > longest_length)
    {
        longest_length = current_length;
        strncpy(longest_word, current_word, longest_length);
    }
    return longest_length > 7 ? longest_length : 7;
}

void removeEmptyLinesAndExtraSpaces(const char *inputFilePath, const char *outputFilePath)
{
    FILE *inputFile = fopen(inputFilePath, "r");
    FILE *outputFile = fopen(outputFilePath, "w");

    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Unable to open the file.\n");
        return;
    }

    char line[LINE_MAX_LENGTH];

    while (fgets(line, LINE_MAX_LENGTH, inputFile))
    {
        if (line[0] == EOF || strcmp(line, "\n") == 0 || strcmp(line, " ") == 0)
        {
            continue;
        }
        // Remove newline characters at the end of the line
        line[strcspn(line, "\n")] = '\0';

        // Trim leading spaces
        char *start = line;
        while (isspace(*start))
        {
            start++;
        }

        // Remove extra spaces and shift spaces
        int isSpace = 0;
        char *writePtr = line;
        for (char *readPtr = start; *readPtr; readPtr++)
        {
            if (isspace(*readPtr))
            {
                if (!isSpace)
                {
                    *writePtr++ = ' ';
                    isSpace = 1;
                }
            }
            else
            {
                *writePtr++ = *readPtr;
                isSpace = 0;
            }
        }
        *writePtr = '\0';

        if (strlen(line) > 0)
        {
            fprintf(outputFile, "%s\n", line);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    // Copy the content from the output file back to the input file
    inputFile = fopen(inputFilePath, "w");
    outputFile = fopen(outputFilePath, "r");

    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Unable to open the file.\n");
        return;
    }

    while (fgets(line, LINE_MAX_LENGTH, outputFile))
    {
        fputs(line, inputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    // Delete the output file
    remove(outputFilePath);

    printf("Empty lines removed, extra spaces and shift spaces condensed successfully!\n");
}
