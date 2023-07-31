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