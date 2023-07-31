#include "local.h"

float generate_number(int min, int max, int num);
void next_round();
void read_range_file(char *file_name, int *min, int *max);
void write_generated_float(char *file_name, float generated_number);

int unpause_player = 0;

int main(int argc, char **argv)
{
    //handling the number of arguments
	if (argc != 3){
        printf("Error in the number of passed arguments.\n");
        kill(getppid(), SIGUSR1);
        exit(-7);
    }
    pid_t parent_pid = getppid();
    char *range_file = argv[0];
    int NUM_OF_ROUNDS = atoi(argv[1]);
    int player_num = atoi(argv[2]);

    int min, max;
    int pid = getpid();
    
    signal(SIGUSR1, next_round);
    int i = 0;
    while (1)
    {
        while (unpause_player == 0){pause();}
        
        read_range_file(range_file, &min, &max);

        float generated_number = generate_number(min, max, pid);
        printf("From child (%d), generated float: %f\n", player_num, generated_number);

        char child_pid_str[10];
        sprintf(child_pid_str, "%d", pid);
        write_generated_float(child_pid_str, generated_number);

        unpause_player = 0;
        kill(getppid(), SIGUSR2);
        i++;
        if (i == NUM_OF_ROUNDS)
            exit(EXIT_SUCCESS);
        sleep(2);
    }
    exit(EXIT_SUCCESS);
}

float generate_number(int min, int max, int num)
{
    float range = max - min + 1;
    float random_num;

    srand(time(NULL) * num * 1000); // seed the random number generator with the current time

    random_num = ((float)rand() / RAND_MAX) * range + min; // generate a random float in the range [min, max]
    return random_num;
}

void next_round()
{
    unpause_player = 1;
}

void read_range_file(char *file_name, int *min, int *max){
    FILE *fp;
    fp = fopen(file_name, "r");

        if (fp == NULL)
        {
            printf("Error opening file.\n");
            exit(-8);
        }
        fscanf(fp, "%d,%d", min, max);
        fclose(fp);
}

void write_generated_float(char *file_name, float generated_number){
    FILE *fp;
    fp = fopen(file_name, "w");
        if (fp == NULL)
        {
            printf("Error opening file\n");
            exit(-9);
        }
        fprintf(fp, "%f", generated_number);
        fclose(fp);
}