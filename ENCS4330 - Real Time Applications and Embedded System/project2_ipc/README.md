# RTP2
Real Time Project 2
***

C code to find the longest line and hiw many words in it
```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

void findLongestLine(const char* filePath) {
    FILE* file = fopen(filePath, "r");

    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
//    char longestLine[MAX_LINE_LENGTH];
    int maxWords = 0;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        int wordCount = 0;
        char* token = strtok(line, " \t\n");

        while (token != NULL) {
            wordCount++;
            token = strtok(NULL, " \t\n");
        }

        if (wordCount > maxWords) {
            maxWords = wordCount;
//            strcpy(longestLine, line);
        }
    }

    fclose(file);

    printf("Number of words in the longest line: %d\n", maxWords);
}

int main() {
    const char* filePath = "input2.txt";    // Replace with your input file path

    findLongestLine(filePath);

    return 0;
}

```

***
C code to compare betwwen two text files and check if is it the same content or not 
```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int compareFiles(FILE *file1, FILE *file2) {
    char line1[MAX_LINE_LENGTH];
    char line2[MAX_LINE_LENGTH];

    while (fgets(line1, MAX_LINE_LENGTH, file1) && fgets(line2, MAX_LINE_LENGTH, file2)) {
        if (strcmp(line1, line2) != 0) {
            return 0; // Files are not the same
        }
    }

    // If one file has more content than the other, they are not the same
    if (fgets(line1, MAX_LINE_LENGTH, file1) || fgets(line2, MAX_LINE_LENGTH, file2)) {
        return 0; // Files are not the same
    }

    return 1; // Files are the same
}

int main() {
    FILE *file1, *file2;

    file1 = fopen("input.txt", "r");
    file2 = fopen("input2.txt", "r");

    if (file1 == NULL || file2 == NULL) {
        printf("Unable to open one or both files.\n");
        return 1;
    }

    int isSame = compareFiles(file1, file2);

    if (isSame) {
        printf("The content of the files is the same.\n");
    } else {
        printf("The content of the files is different.\n");
    }

    fclose(file1);
    fclose(file2);

    return 0;
}

```

***

C code to remove empty lines, extra spaces and shift spaces in-place

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1000

void removeEmptyLinesAndExtraSpaces(const char* inputFilePath, const char* outputFilePath) {
    FILE* inputFile = fopen(inputFilePath, "r");
    FILE* outputFile = fopen(outputFilePath, "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, inputFile)) {
        // Remove newline characters at the end of the line
        line[strcspn(line, "\n")] = '\0';

        // Trim leading spaces
        char* start = line;
        while (isspace(*start)) {
            start++;
        }

        // Remove extra spaces and shift spaces
        int isSpace = 0;
        char* writePtr = line;
        for (char* readPtr = start; *readPtr; readPtr++) {
            if (isspace(*readPtr)) {
                if (!isSpace) {
                    *writePtr++ = ' ';
                    isSpace = 1;
                }
            }
            else {
                *writePtr++ = *readPtr;
                isSpace = 0;
            }
        }
        *writePtr = '\0';

        if (strlen(line) > 0) {
            fprintf(outputFile, "%s\n", line);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    // Copy the content from the output file back to the input file
    inputFile = fopen(inputFilePath, "w");
    outputFile = fopen(outputFilePath, "r");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    while (fgets(line, MAX_LINE_LENGTH, outputFile)) {
        fputs(line, inputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    // Delete the output file
    remove(outputFilePath);

    printf("Empty lines removed, extra spaces and shift spaces condensed successfully!\n");
}

int main() {
    const char* inputFilePath = "input2.txt";       // Replace with your input file path
    const char* outputFilePath = "output.txt";     // Replace with your desired output file path

    removeEmptyLinesAndExtraSpaces(inputFilePath, outputFilePath);

    return 0;
}
```


***

this code is a split file from kareem (not used)

```C 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numOfColumns = 4;   // this value should come from previous methods
int numOfLines = 2;     // this value should come from previous methods
char*** columns;

void splitTheFileToColumns(char * fileName);
void printCol(int j);

int main(int argc, char **argv) {
    char* fileName = "sender.txt";
    splitTheFileToColumns(fileName);

    printCol(0);
    printCol(1);
    return 0;
}

void splitTheFileToColumns(char * fileName){
    FILE *file = fopen(fileName, "r"); 

    if (file == NULL) {
        printf("Error opening the file.\n");
        exit(-1);
    }

    columns = (char***)malloc(numOfColumns * sizeof(char**));
    for (int i = 0; i < numOfColumns; i++) {
        columns[i] = (char**)malloc(numOfLines * sizeof(char*));
    }

    char *line = NULL;
    size_t lineSize = 0;
    int columnCount = 0;
    int lineCount = 0;
    while (getline(&line, &lineSize, file) != -1) {

        line[strcspn(line, "\n")] = '\0';

        // Split the line into columns based on spaces
        char *token = strtok(line, " ");
        columnCount = 0;

        while (token != NULL && columnCount < numOfColumns) {
            // Allocate memory for the new variable
            columns[columnCount][lineCount] = malloc((strlen(token) + 1) * sizeof(char));
            if (columns[columnCount][lineCount] == NULL) {
                printf("Memory allocation failed.\n");
                exit(-2);
            }

            // Copy the contents of the original variable to the new variable
            strcpy(columns[columnCount][lineCount], token);
            token = strtok(NULL, " ");
            columnCount++;
        }
        for(;columnCount<numOfColumns;columnCount++){
            columns[columnCount][lineCount]= "alright";
        }
        lineCount++;
    }

    free(line);
    fclose(file);
}

void printCol(int j){
    // Print the columns
    for (int i = 0; i < numOfColumns; i++) {
        printf("%s\n", columns[i][j]);
    } 
}
```
***
Concept code for semaphores
```C
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define NUM_PROCESSES 5

// Function to perform the critical section
void criticalSection(int processId, int semaphoreId) {
    // Acquire the semaphore
    struct sembuf acquireOp = {0, -1, 0};
    semop(semaphoreId, &acquireOp, 1);

    // Critical section
    printf("Process %d entered the critical section.\n", processId);
    sleep(2); // Simulating some work
    printf("Process %d exited the critical section.\n", processId);

    // Release the semaphore
    struct sembuf releaseOp = {0, 1, 0};
    semop(semaphoreId, &releaseOp, 1);
}

int main() {
    key_t key;
    int semaphoreId;

    // Generate a key for the semaphore set
    if ((key = ftok(".", 'S')) == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a semaphore set with a single semaphore
    if ((semaphoreId = semget(key, 1, IPC_CREAT | 0666)) == -1) {
        perror("semget");
        exit(1);
    }

    // Initialize the semaphore value to 1 (unlocked)
    if (semctl(semaphoreId, 0, SETVAL, 1) == -1) {
        perror("semctl");
        exit(1);
    }

    // Fork multiple processes
    for (int i = 0; i < NUM_PROCESSES; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // Child process
            criticalSection(i, semaphoreId);
            exit(0);
        }
    }

    // Wait for all child processes to finish
    for (int i = 0; i < NUM_PROCESSES; i++) {
        wait(NULL);
    }

    // Remove the semaphore set
    if (semctl(semaphoreId, 0, IPC_RMID) == -1) {
        perror("semctl");
        exit(1);
    }

    return 0;
}
```
***
Read arguments.txt file
```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* file = fopen("argument.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    int NUM_OF_HELPER_PROC = -1;
    int NUM_OF_SPY_PROC = -1;
    int FAIL_THRESHOLD = -1;
    int SUCCESS_THRESHOLD = -1;
    int SPY_SLEEP_RANGE_MIN = -1;
    int SPY_SLEEP_RANGE_MAX = -1;
    int RECEIVER_SLEEP_RANGE_MIN = -1;
    int RECEIVER_SLEEP_RANGE_MAX = -1;

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char* token = strtok(line, " ");
        if (strcmp(token, "NUM_OF_HELPER_PROC") == 0) {
            token = strtok(NULL, " ");
            NUM_OF_HELPER_PROC = atoi(token);
        } else if (strcmp(token, "NUM_OF_SPY_PROC") == 0) {
            token = strtok(NULL, " ");
            NUM_OF_SPY_PROC = atoi(token);
        } else if (strcmp(token, "FAIL_THRESHOLD") == 0) {
            token = strtok(NULL, " ");
            FAIL_THRESHOLD = atoi(token);
        } else if (strcmp(token, "SUCCESS_THRESHOLD") == 0) {
            token = strtok(NULL, " ");
            SUCCESS_THRESHOLD = atoi(token);
        } else if (strcmp(token, "SPY_SLEEP_RANGE") == 0) {
            token = strtok(NULL, " ");
            SPY_SLEEP_RANGE_MIN = atoi(token);
            token = strtok(NULL, " ");
            SPY_SLEEP_RANGE_MAX = atoi(token);
        } else if (strcmp(token, "RECEIVER_SLEEP_RANGE") == 0) {
            token = strtok(NULL, " ");
            RECEIVER_SLEEP_RANGE_MIN = atoi(token);
            token = strtok(NULL, " ");
            RECEIVER_SLEEP_RANGE_MAX = atoi(token);
        }
    }

    fclose(file);

    // Print the values to verify they were read correctly
    printf("NUM_OF_HELPER_PROC: %d\n", NUM_OF_HELPER_PROC);
    printf("NUM_OF_SPY_PROC: %d\n", NUM_OF_SPY_PROC);
    printf("FAIL_THRESHOLD: %d\n", FAIL_THRESHOLD);
    printf("SUCCESS_THRESHOLD: %d\n", SUCCESS_THRESHOLD);
    printf("SPY_SLEEP_RANGE_MIN: %d\n", SPY_SLEEP_RANGE_MIN);
    printf("SPY_SLEEP_RANGE_MAX: %d\n", SPY_SLEEP_RANGE_MAX);
    printf("RECEIVER_SLEEP_RANGE_MIN: %d\n", RECEIVER_SLEEP_RANGE_MIN);
    printf("RECEIVER_SLEEP_RANGE_MAX: %d\n", RECEIVER_SLEEP_RANGE_MAX);

    return 0;
}
```
