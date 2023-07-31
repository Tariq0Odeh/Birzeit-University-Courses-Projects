#include "local.h"

void next_round();

int unpause_coprocessor = 0;

int main(int argc, char **argv)
{
    //handling the number of arguments
    if (argc != 5){
        printf("Error in the number of passed arguments.\n");
        kill(getppid(), SIGUSR1);
        exit(-10);
    }

    pid_t parent_pid = getppid();
    int fd_write = atoi(argv[0]);
    int fd_read = atoi(argv[1]);
    int fd_write2 = atoi(argv[2]);
    int fd_read2 = atoi(argv[3]);
    int num_of_rounds = atoi(argv[4]);

    signal(SIGINT, next_round);
    int i = 0;
    while (1)
    {
        while (unpause_coprocessor == 0){pause();}
        
        char received_msg[BUFSIZ];
        char tmp_str[BUFSIZ];
        read_pipe_str(fd_read, fd_write, received_msg, BUFSIZ);
     
        unpause_coprocessor = 0;
        printf("\nFrom co-processor [%s]\n\n", received_msg);

        float num1, num2, num3, num4, sum1, sum2;
        sscanf(received_msg, "%f,%f,%f,%f", &num1, &num2, &num3, &num4);
        memset(received_msg, 0x0, BUFSIZ);

        sum1 = num1 + num2;
        sum2 = num3 + num4;
        printf("Sum1 (For Team One) = [%f]\n", sum1);
        printf("Sum2 (For Team Two) = [%f]\n\n", sum2);
        fflush(stdout);

        sprintf(tmp_str, "%f,", sum1);
        strcat(received_msg, tmp_str);

        memset(tmp_str, 0x0, BUFSIZ);

        sprintf(tmp_str, "%f", sum2);
        strcat(received_msg, tmp_str);
        sleep(1);

        write_pipe_str(fd_read2, fd_write2, received_msg, strlen(received_msg));

        kill(getppid(), SIGUSR2);
        i++;
        if (i == num_of_rounds)
            exit(EXIT_SUCCESS);
        sleep(1);
    }
    exit(EXIT_SUCCESS);
}

void next_round()
{
    unpause_coprocessor = 1;
}
