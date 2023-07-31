#include "local.h"

#define NUM_OF_PLAYERS 4
#define NUM_OF_CHILDREN 5

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Global Variables we use in Parent
int NUM_OF_ROUNDS = 5,curr_round = 0;
float proc[4];
int curr_player = 0;
int min = 0, max = 1;
int start =0;
int winner;
FILE *fp;
int fd[2][2];
char min_max_string[40];
int children_pid[NUM_OF_CHILDREN];
int player_wait_signal[NUM_OF_CHILDREN] = {0};
float sum1=0, sum2=0;
int team1_points = 0, team2_points = 0;
char *range_file = "range.txt";
int child_number = 0;
int parent_pid;

// The parent Methods 
void terminate_children();
void terminate_FIFO();
void initialize_pipes();
void count_points();
void declare_winner();
void child_handler();
void kill_all();
void remove_files();
void validate_args(int argc, char *argv[]);

// The openGL Methods 
void startOpenGl();
void display();
void RoundNumber();
void LineInTheMiddle();
void LineHorizontal();
void TeamOne();
void TeamTwo();
void viewportOne();
void viewportTwo();
void viewportMain();
void viewportMain2();
void footer();
void AllProcesses();
void Summation();
void renderBitMap(double x, double y, void *font, char *string);
void FinalScreen();
void init();
void ending();
void timer(int t);

int main(int argc, char **argv)
{

	validate_args(argc,argv);
	pid_t child_pid;
	parent_pid = getpid();

	signal(SIGUSR2, child_handler);
	signal(SIGUSR1, kill_all);

	initialize_pipes();

	// to fork the five children and then execute them 
	for (int i = 0; i < NUM_OF_CHILDREN; i++)
	{
		child_pid = fork();
		usleep(500);

		if (child_pid == -1)
		{
			printf("Error with forking\n");
			exit(-1);
		}

		// if the child_pid not zero, that means we are in the parent, so we save the child pid
		if (getpid() == parent_pid)
		{
			children_pid[i] = child_pid;
		}

		char *rounds_str = malloc(sizeof(int));
		char *player_num = malloc(sizeof(int));

		sprintf(rounds_str, "%d", NUM_OF_ROUNDS);
		sprintf(player_num, "%d", i);

		// if the child_pid equals zero, that means we are in the child process 
		// this "if statement" for the first 4 children 
		if (child_pid == 0 && i < NUM_OF_PLAYERS)
		{
			if (execl("./child", range_file, rounds_str, player_num, NULL) == -1)
			{
				printf("Error with Executing child\n");
				exit(-2);
			}
			exit(1);
		}
		// this "else if" for the the child number 5 co-processor
		else if (child_pid == 0 && i == (NUM_OF_CHILDREN - 1))
		{

			char fd_write_str[10], fd_read_str[10];
			char fd_write_str2[10], fd_read_str2[10];

			sprintf(fd_write_str, "%d", fd[0][1]);
			sprintf(fd_read_str, "%d", fd[0][0]);
			sprintf(fd_write_str2, "%d", fd[1][1]);
			sprintf(fd_read_str2, "%d", fd[1][0]);
		
			if (execl("./co-processor", fd_write_str, fd_read_str, fd_write_str2, fd_read_str2, rounds_str, NULL) == -1)
			{
				printf("Error with Executing co-processor\n");
				exit(-3);
			}
			exit(EXIT_SUCCESS);
		}

		free(rounds_str);
		free(player_num);

	}
	glutInit(&argc, argv);
    startOpenGl();

	return 0;
}

void terminate_children()
{
	for (int i = 0; i < NUM_OF_CHILDREN; i++)
	{
		int status;
		kill(children_pid[i], SIGTERM);
		waitpid(children_pid[i], &status, 0);

        if (WIFEXITED(status)) {
            printf("Child (%d) process terminated with exit status %d\n", i, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child (%d) process terminated by signal %d\n", i, WTERMSIG(status));
        }
	}
	return;
}

void initialize_pipes()
{
		if (pipe(fd[0]) == -1 || pipe(fd[1]) == -1)
		{
			perror("Pipe initialization error");
			exit(-4);
		}
}

void validate_args(int argc, char **argv){
	FILE *fp2;
    fp2 = fopen(argv[1], "r");
	if (fp2 == NULL)
	{
		printf("Error opening file\n");
		exit(-5);
	}

	// Store the content of the file
	char myString[100];

	// Read the content and print it
	while(fgets(myString, 100, fp2)) {
		char *ptr = strtok(myString, " ");
		if(strcmp(ptr,"NUMBER_OF_ROUNDS")==0){
			ptr = strtok(NULL, " ");
			NUM_OF_ROUNDS = atoi(ptr);
		 }
	}
	fclose(fp2); 
}

void count_points()
{
	if (sum1 > sum2)
	{
		team1_points++;
	}
	else if (sum1 < sum2)
	{
		team2_points++;
	}
	else
	{
		team1_points++;
		team2_points++;
	}
}
void declare_winner()
{
	printf("\n------------------------------------------\n");
	if (team1_points > team2_points)
	{
		printf(GREEN "Team1 is the winner!\n" RESET);
		winner =1;
	}
	else if (team1_points < team2_points)
	{
		printf(RED "Team2 is the winner!\n" RESET);
		winner=2;
	}
	else
	{
		printf("Draw\n");
		winner=0;
	}
	printf("\n------------------------------------------\n");
}

void child_handler()
{
	player_wait_signal[child_number] = 1;
	child_number++;
	child_number %= 5;
	return;
}

void kill_all(){
	terminate_children();
	kill(getpid(), SIGTERM);
}

void remove_files(){
	printf("\n");
	for (int i = 0; i < NUM_OF_PLAYERS; i++){
		char filename[50];
		sprintf(filename, "%d", children_pid[i]);
		if(remove(filename) == 0) {
        	printf("%s file deleted successfully.\n", filename);
		}
		else {
			printf("Unable to delete the file.\n");
    	}
	}
}

void startOpenGl(){

  init();
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowPosition(450, 450);
  glutInitWindowSize(950, 750);
  glutCreateWindow("My first Program");
  glutDisplayFunc(display);

  glutTimerFunc(0, timer, 0);

  init();

  glutMainLoop();
}

void init(){
	glClearColor(1.0,1.0,1.0,1.0);

}

void display() {

	// Set every pixel in the frame buffer to the current clear color.
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	viewportMain();
	viewportOne();
	viewportTwo();
	viewportMain2();
	LineInTheMiddle();
	LineHorizontal();
	RoundNumber();
	AllProcesses();
	Summation();
	TeamOne();
	TeamTwo();
	footer();
  	glutPostRedisplay();
    glutSwapBuffers();


}

void FinalScreen(){
	
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f (0.0, 0.0, 0.0);
	char string[100];

	if(winner==0){
	snprintf(string,20,"Draw !!");
	}else{
	sprintf(string, "Team %d is the Winner !!",winner);

	}
	renderBitMap(-0.20, -0.2, GLUT_BITMAP_TIMES_ROMAN_24, string);
	char string2[30];
	sprintf(string2, "Team One: \n Final Score = %d",team1_points);
	renderBitMap(-0.80, 0.5, GLUT_BITMAP_TIMES_ROMAN_24, string2);

	char string3[30];
	sprintf(string3, "Team Two: \n Final Score = %d",team2_points);
	renderBitMap(0.20, 0.5, GLUT_BITMAP_TIMES_ROMAN_24, string3);
	glFlush();
}

void renderBitMap(double x, double y, void *font, char *string) {
    char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}
void RoundNumber(){
	glColor3f (0.0, 0.0, 0.0);
	char string[30];
	if(curr_round == 0)
		snprintf(string,30,"Start!");
	else
		snprintf(string,30,"Round %d",curr_round);
	renderBitMap(-0.07, 0.85, GLUT_BITMAP_TIMES_ROMAN_24, string);
	renderBitMap(-0.18, 0.75, GLUT_BITMAP_9_BY_15, min_max_string);

}

void LineInTheMiddle(){
	glColor3f (1.0, 0.0, 0.0);
	glPointSize(10.0);
	glBegin(GL_LINES);
	glVertex2f(0.0,-1.0);
	glVertex2f(0.0,0.7);
	glEnd();
}

void LineHorizontal(){
	glColor3f (1.0, 0.0, 0.0);
	glPointSize(1.0);
	glBegin(GL_LINES);
	glVertex2f(-1.0,0.7);
	glVertex2f(1.0,0.7);
	glEnd();

}

void footer(){
	glColor3f (1.0, 0.0, 0.0);
	glPointSize(1.0);
	glBegin(GL_LINES);
	glVertex2f(1.0,-0.7);
	glVertex2f(-1.0,-0.7);
	glEnd();
	glFlush();

}

void viewportOne(){
	glPointSize(10.0);
	glBegin(GL_POLYGON);

	glColor3f(1.0f, 0.4f, 0.4f); glVertex2f(-1,0.7);
	glColor3f(1.0f, 0.4f, 0.4f); glVertex2f(-1,-1);
	glColor3f(1.0f, 0.4f, 0.4f); glVertex2f(0,-1.0);
	glColor3f(1.0f, 0.4f, 0.4f); glVertex2f(0,0.7);
	glEnd();

}

void viewportTwo(){
	glPointSize(10.0);
	glBegin(GL_POLYGON);

	glColor3f(0.4f, 0.9f, 0.3f); glVertex2f(0,0.7);
	glColor3f(0.4f, 0.9f, 0.3f); glVertex2f(0,-1.0);
	glColor3f(0.4f, 0.9f, 0.3f); glVertex2f(1,-1);
	glColor3f(0.4f, 0.9f, 0.3f); glVertex2f(1,0.7);
	glEnd();


}

void viewportMain(){
	glPointSize(10.0);
	glBegin(GL_POLYGON);
	glColor3f(0.83, 0.83, 0.78); glVertex2f(-1,1);
	glColor3f(0.79, 0.96, 1); glVertex2f(-1,0.7);
	glColor3f(0.83, 0.83, 0.78); glVertex2f(1,0.7);
	glColor3f(0.79, 0.96, 1); glVertex2f(1,1);
	glFlush();
    glEnd();

}

void viewportMain2(){
	glPointSize(10.0);
	glBegin(GL_POLYGON);
	glColor3f(0.83, 0.83, 0.78); glVertex2f(1,-1);
	glColor3f(0.79, 0.96, 1); glVertex2f(1,-0.7);
	glColor3f(0.83, 0.83, 0.78); glVertex2f(-1,-0.7);
	glColor3f(0.79, 0.96, 1); glVertex2f(-1,-1);
	glEnd();


}

void TeamOne(){
	glColor3f (0.0, 0.0, 0.0);
	glRasterPos2f(-0.6, 0.5); // define position on the screen
	char string[6]="TEAM 1";
	int len = strlen(string);
	for (int i = 0; i < len; i++) {
    		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void TeamTwo(){
	glColor3f (0.0, 0.0, 0.0);
	glRasterPos2f(0.4, 0.5); // define position on the screen
	char string[6]="TEAM 2";
	int len = strlen(string);
	for (int i = 0; i < len; i++) {
    		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void AllProcesses(){
	float x[]={-0.95,-0.95,0.05,0.05};
	float y[]={0.3,0.1,0.3,0.1};
	char string[30];
	for(int i = 1;i <=4;i++){
		glColor3f (0.0, 0.0, 0.0);
		if(proc[i-1]!=0.0){
		sprintf(string, "Child %d = %f",i,proc[i-1]);
		renderBitMap(x[i-1]+0.25, y[i-1],GLUT_BITMAP_9_BY_15,string);
		}
	}

	char string2[30];
	sprintf(string2, "Current Score = %d",team1_points);
	renderBitMap(-0.75, -0.88, GLUT_BITMAP_TIMES_ROMAN_24, string2);

	char string3[30];
	sprintf(string3, "Current Score = %d",team2_points);
	renderBitMap(0.25, -0.88, GLUT_BITMAP_TIMES_ROMAN_24, string3);
}

void Summation(){
	char string2[40];
	sprintf(string2, "Sum = %f",sum1);
	renderBitMap(-0.70, -0.3, GLUT_BITMAP_TIMES_ROMAN_24, string2);

	char string3[40];
	sprintf(string3, "Sum = %f",sum2);
	renderBitMap(0.35, -0.3, GLUT_BITMAP_TIMES_ROMAN_24, string3);
}

void ending(){

	declare_winner();
	glutPostRedisplay();
	sleep(3);
	FinalScreen();
	printf("\n");
	terminate_children();
	remove_files();
	sleep(3);
	kill(parent_pid, SIGTERM);

}

void timer(int t){

	glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);
   if (start ==2){

		sleep(2);
		ending();
	}
    else if(start==1){

		sleep(2);
    	char children_generated_numbers[BUFSIZ];
		char teams_sum[BUFSIZ];
		memset(children_generated_numbers, 0, sizeof(children_generated_numbers));
		//generates min and max
		srand(time(0) * (curr_round + 1) * 100);
		min = rand() % 1000;
		max = 1 + min + rand() % (1000);

		fp = fopen(range_file, "w");
		if (fp == NULL)
		{
			printf("Error opening file\n");
			exit(-7);
		}
		fprintf(fp, "%d,%d", min, max);
		fclose(fp);

		printf("Min (%d), Max (%d)\n\n\n", min, max);
		sprintf(min_max_string,"Min (%d), Max (%d)", min, max);
		usleep(500);

		// players
		while (1)
		{
			//inform the child to start
			kill(children_pid[curr_player], SIGUSR1);
			//wait the child to generate a random number
			while (player_wait_signal[curr_player] == 0){pause();}

			float rand_float;
			//read the generated number

			char id_str[10];
			sprintf(id_str, "%d", children_pid[curr_player]);

			fp = fopen(id_str, "r");

			if (fp == NULL)
			{
				printf("Error opening file. \n");
				exit(-8);
			}
			fscanf(fp, "%f", &rand_float);
			fclose(fp);
			printf("From parent, child (%d) generated random float: |%f|\n", curr_player, rand_float);
			proc[curr_player] = rand_float;

			player_wait_signal[curr_player] = 0;
			curr_player++;
			char temp_str[BUFSIZ];


			if (curr_player == NUM_OF_PLAYERS)
			{
				sprintf(temp_str, "%f", rand_float);
				strcat(children_generated_numbers, temp_str);
				curr_player = 0;
				break;
			}
			else
			{
				sprintf(temp_str, "%f,", rand_float);
				strcat(children_generated_numbers, temp_str);

			}
			printf("\n");
			usleep(500);
			memset(temp_str, 0x0, BUFSIZ);
		}

		printf("\n");
		usleep(500);
		printf("From parent, generated numbers [%s]\n", children_generated_numbers);

		//writes the generated numbers to the pipe
		write_pipe_str(fd[0][0], fd[0][1], children_generated_numbers, strlen(children_generated_numbers));

		usleep(500);

		//inform the co-processor to start
		kill(children_pid[NUM_OF_CHILDREN - 1], SIGINT);

		//wait until the two summations are ready
		while (player_wait_signal[NUM_OF_CHILDREN - 1] == 0){pause();}
		sleep(2);

		//read the two summations from the co-processor using pipe
		read_pipe_str(fd[1][0], fd[1][1], teams_sum, BUFSIZ);

		usleep(500);
		printf("From parent, teams sum: [%s]\n", teams_sum);
		
		sscanf(teams_sum, "%f,%f", &sum1, &sum2);
		usleep(500);
		count_points();
		usleep(500);

		printf("\nTeam1 [%d] - Team2 [%d]\n", team1_points, team2_points);
		printf("\nRound(%d) finished\n\n", curr_round + 1);
		printf("**************************\n");

		
		curr_round++;
		if (curr_round == NUM_OF_ROUNDS)
		{
			start =2;
			
		}

		memset(children_generated_numbers, 0x0, BUFSIZ);
		memset(teams_sum, 0x0, BUFSIZ);
		sleep(1);


	}else if (start == 0){
	start=1;
}
}
