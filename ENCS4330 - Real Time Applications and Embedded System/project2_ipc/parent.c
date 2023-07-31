#include "local.h"

//------------------------------------------------OpenGL variables-------------------------------------------------------------//
float move_y[4] = {77.0, 168.0, 298.0, 382.0};						   //{sender, encoding, spies, helper}
float move_x[3] = {340.0, 260.0, 502.0};							   //{parent-successful, parent-failed, spies}
float move_xy[3][2] = {{80.0, 423.0}, {107.0, 450.0}, {493.0, 450.0}}; //{to receiver, from receiver, from master spy}
bool op_successful = false;
bool go = false;
bool fail_succ[2] = {false, false};		   // to control the final result
bool encoding_go = false;				   // when receive colum from sender
bool ready_to_parent[2] = {false, false};  // receiver, master spy
bool spies_go[2] = {false, false};		   // the first between spies and sheared memory and the second between spies and master spy
bool receiver_go[1] = {true};			   // to control receiver direction
int sender_counter = 0;					   // to mange the number of encoding processes
bool state_RHS[3] = {false, false, false}; // to let them start after the encoding enter all columns
bool first_time = true;

int num_swap = 0;
int num_enc_op = 0;

//------------------------------------------------OpenGL functions-------------------------------------------------------------//
void startOpenGl();
void display();
void init();
void reshape(int w, int h);
void timer();
void tempMain();
void endProgram();
void rectangle(int x1, int y1, int x2, int y2, float r, float g, float b);
void drawSquare(int centerX, int centerY, int sideLength, float red, float green, float blue);
void drawText_size(int centerX, int centerY, char *str, int size);
void drawLine(int centerX1, int centerY1, int centerX2, int centerY2);
void writeIntegerAtPosition(int number, float x, float y);
void drawTextTable(int numCols, int numRows, int cellWidth, int cellHeight, int posX, int posY);

// global variables
int num_of_helper_proc = 1;
int num_of_spy_proc = 1;
int sender_pid, receiver_pid, master_spy_pid;
int *helper_processes;
int *spy_processes;

int spy_got_msg = 0, receiver_got_msg = 0, got_msg_first = 2;
int num_of_successful_decoding = 0, num_of_failed_decoding = 0;
int indices = 7, rows = 6;
int wait_process = 0;
int count = 0;
int sucess_threshold = 2, failure_threshold = 2;
int flag = 0;
int receiver_sleep_limit = 0, helper_sleep_limit = 0, spy_sleep_limit = 0;

void validate_args(int argc, char **argv);
void spy_handler();
void receiver_handler();
void startOtherProcesses();
void deleteAll();
int compareFiles(char *filename1, char *filename2);
void read_arguments(char *argument_file);

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("[Parent] missing arguments\n");
		exit(-1);
	}
	read_arguments(argv[1]);
	// validate_args(argc, argv);
	pid_t child_pid;
	parent_pid = getpid();
	static struct MEMORY memory;
	memory.head = 6, memory.tail = 0, memory.size = 7;

	signal(SIGUSR1, startOtherProcesses);
	signal(SIGUSR2, spy_handler);
	signal(SIGALRM, receiver_handler);
	signal(SIGINT, deleteAll);

	/*
	 * Create, attach and initialize the memory segment
	 */
	if ((shmid = shmget((int)parent_pid, sizeof(memory),
						IPC_CREAT | 0666)) != -1)
	{

		if ((shmptr = (char *)shmat(shmid, 0, 0)) == (char *)-1)
		{
			perror("shmptr -- parent -- attach");
			exit(1);
		}
		memcpy(shmptr, (char *)&memory, sizeof(memory));
	}
	else
	{
		perror("shmid -- parent -- creation");
		exit(2);
	}
	printf("Shared memory id [%d]\n\n", shmid);

	/*
	 * Create and initialize the semaphores
	 */
	if ((semid = semget((int)parent_pid, 1,
						IPC_CREAT | 0666)) != -1)
	{
		if (semctl(semid, 0, SETVAL, 1) == -1)
		{
			perror("semctl -- parent -- initialization");
			exit(3);
		}
	}
	else
	{
		perror("semget -- parent -- creation");
		exit(4);
	}

	// to fork the sender, receiver, spy

	child_pid = fork();

	if (child_pid == -1)
	{
		printf("Error with forking\n");
		exit(-1);
	}
	// if the child_pid not zero, that means we are in the parent, so we save the child pid
	else if (getpid() == parent_pid)
	{
		sender_pid = child_pid;
	}
	else if (child_pid == 0)
	{
		if (execl("./sender", "./sender", (char*) NULL) == -1)
		{
			printf("Error with Executing sender\n");
			exit(-2);
		}
		exit(1);
	}

	// waiting sender to finish
	while (1)
	{
		while (wait_process == 0)
		{
			pause();
		}
		break;
	}
	// return 0;
	memptr = (struct MEMORY *)shmptr;
	indices = memptr->size;
	rows = memptr->head;

	semctl(semid, 0, IPC_RMID, 0);

	/*
	 * Create and initialize the semaphores
	 */
	if ((semid = semget((int)parent_pid, 1,
						IPC_CREAT | 0666)) != -1)
	{
		// arg.array = start_val;

		if (semctl(semid, 0, SETVAL, 1) == -1)
		{
			perror("semctl -- parent -- initialization");
			exit(3);
		}
	}
	else
	{
		perror("semget -- parent -- creation");
		exit(4);
	}

	/*
	 * Create the Queue between the Master_spy and Spies
	 */
	if ((queid = msgget((int)parent_pid, 0)) == -1)
	{
		queid = msgget((int)parent_pid, IPC_CREAT | 0777);
	}

	for (int i = 0; i < 2; i++)
	{
		child_pid = fork();
		usleep(500);

		if (child_pid == -1)
		{
			printf("Error with forking\n");
			exit(-1);
		}
		// if the child_pid not zero, that means we are in the parent, so we save the child pid
		else if (getpid() == parent_pid)
		{
			if (i == 0)
			{
				receiver_pid = child_pid;
			}
			else
			{
				master_spy_pid = child_pid;
			}
		}
		else if (child_pid == 0 && i == 0)
		{
			char indices_str[10], rows_str[10], sleep_str[10];
			sprintf(indices_str, "%d", indices);
			sprintf(rows_str, "%d", rows);
			sprintf(sleep_str, "%d", receiver_sleep_limit);
			if (execl("./receiver", indices_str, rows_str, sleep_str, NULL) == -1)
			{
				printf("Error with Executing receiver\n");
				exit(-2);
			}
			exit(1);
		}
		else if (child_pid == 0 && i == 1)
		{
			char indices_str[10], rows_str[10], queueid[10];
			sprintf(indices_str, "%d", indices);
			sprintf(rows_str, "%d", rows);
			sprintf(queueid, "%d", queid);
			if (execl("./master_spy", indices_str, rows_str, queueid, NULL) == -1)
			{
				printf("Error with Executing master_spy\n");
				exit(-2);
			}
			exit(1);
		}
	}
	// return 0;
	// sleep(10);
	// forking helpers
	for (int i = 0; i < num_of_helper_proc; i++)
	{
		child_pid = fork();
		usleep(500);

		if (child_pid == -1)
		{
			printf("Error with forking in helper proc\n");
			exit(-1);
		}
		// if the child_pid not zero, that means we are in the parent, so we save the child pid
		else if (getpid() == parent_pid)
		{
			helper_processes[i] = child_pid;
		}
		else if (child_pid == 0)
		{
			char indices_str[10], rows_str[10], sleep_str[10];
			sprintf(indices_str, "%d", indices);
			sprintf(rows_str, "%d", rows);
			sprintf(sleep_str, "%d", helper_sleep_limit);
			if (execl("./helper", indices_str, rows_str, sleep_str, NULL) == -1)
			{
				printf("Error with Executing helper\n");
				exit(-2);
			}
			exit(1);
		}
	}

	// forking spy processes
	for (int i = 0; i < num_of_spy_proc; i++)
	{
		child_pid = fork();
		usleep(500);

		if (child_pid == -1)
		{
			printf("Error with forking in spy proc\n");
			exit(-1);
		}
		// if the child_pid not zero, that means we are in the parent, so we save the child pid
		else if (getpid() == parent_pid)
		{
			spy_processes[i] = child_pid;
		}
		else if (child_pid == 0)
		{
			char indices_str[10], rows_str[10], queueid[10], sleep_str[10];
			sprintf(indices_str, "%d", indices);
			sprintf(rows_str, "%d", rows);
			sprintf(queueid, "%d", queid);
			sprintf(sleep_str, "%d", spy_sleep_limit);
			if (execl("./spy", indices_str, rows_str, queueid, sleep_str, NULL) == -1)
			{
				printf("Error with Executing spy\n");
				exit(-2);
			}
			exit(1);
		}
	}
	glutInit(&argc, argv);
	startOpenGl();
	return 0;
}
void read_arguments(char *argument_file)
{
	FILE *file = fopen(argument_file, "r");
	if (file == NULL)
	{
		printf("Failed to open the file.\n");
		exit(EXIT_FAILURE);
	}
	char line[LINE_MAX_LENGTH];
	memset(line, 0x0, LINE_MAX_LENGTH);
	while (fgets(line, LINE_MAX_LENGTH, file) != NULL)
	{
		
		char *token = strtok(line, " ");
		if (strcmp(token, "NUM_OF_HELPER_PROC") == 0)
		{
			token = strtok(NULL, " ");
			num_of_helper_proc = atoi(token);
			helper_processes = malloc(sizeof(int) * num_of_helper_proc);
		}
		else if (strcmp(token, "NUM_OF_SPY_PROC") == 0)
		{
			token = strtok(NULL, " ");
			num_of_spy_proc = atoi(token);
			spy_processes = malloc(sizeof(int) * num_of_spy_proc);
		}
		else if (strcmp(token, "FAIL_THRESHOLD") == 0)
		{
			token = strtok(NULL, " ");
			failure_threshold = atoi(token);
		}
		else if (strcmp(token, "SUCCESS_THRESHOLD") == 0)
		{
			token = strtok(NULL, " ");
			sucess_threshold = atoi(token);
		}
		else if (strcmp(token, "SPY_SLEEP_LIMIT") == 0)
		{
			token = strtok(NULL, " ");
			spy_sleep_limit = atoi(token);
		}
		else if (strcmp(token, "RECEIVER_SLEEP_LIMIT") == 0)
		{
			token = strtok(NULL, " ");
			receiver_sleep_limit = atoi(token);
		}
		else if (strcmp(token, "HELPER_SLEEP_LIMIT") == 0)
		{
			token = strtok(NULL, " ");
			helper_sleep_limit = atoi(token);
		}
	}

	fclose(file);
}

int compareFiles(char *filename1, char *filename2)
{
	FILE *file1, *file2;
	file1 = fopen(filename1, "r");
	file2 = fopen(filename2, "r");
	if (file1 == NULL)
	{
		printf("Failed to open the file [%s].\n", filename1);
		return -1;
	}
	if (file2 == NULL)
	{
		printf("Failed to open the file [%s].\n", filename2);
		return -1;
	}
	char line1[LINE_MAX_LENGTH];
	char line2[LINE_MAX_LENGTH];

	while (fgets(line1, LINE_MAX_LENGTH, file1) && fgets(line2, LINE_MAX_LENGTH, file2))
	{
		if (strcmp(line1, line2) != 0)
		{
			return 0; // Files are not the same
		}
	}

	// If one file has more content than the other, they are not the same
	if (fgets(line1, LINE_MAX_LENGTH, file1) || fgets(line2, LINE_MAX_LENGTH, file2))
	{
		return 0; // Files are not the same
	}

	return 1; // Files are the same
}

void startOtherProcesses()
{
	wait_process = 1;
}

void spy_handler()
{
	if (got_msg_first == 2)
	{
		got_msg_first = 1;
	}
	spy_got_msg = 1;
	printf(BLUE "SPY DONE\n" RESET);
	ready_to_parent[1] = true;
	return;
}

void receiver_handler()
{
	if (got_msg_first == 2)
	{
		got_msg_first = 0;
	}
	receiver_got_msg = 1;
	printf(BLUE "RECEIVER DONE\n" RESET);
	ready_to_parent[0] = true;
	return;
}

void deleteAll()
{
	// msgctl(mid, IPC_RMID, (struct msqid_ds *) 0 );
	shmctl(shmid, IPC_RMID, (struct shmid_ds *)0); /* remove */
	semctl(semid, 0, IPC_RMID, 0);
	msgctl(queid, IPC_RMID, NULL);

	// exit(-1);
}

//-------------------------------------------------OpenGL Functions------------------------------------------------------------//
void startOpenGl()
{
	init();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Message encoding/decoding");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	init();
	glutMainLoop();
}

//--------------------------------------------------------------------

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glutPostRedisplay();

	//* rectangle - shared memory *//
	rectangle(225, 240, 375, 320, 0, 0, 0);
	if (move_y[3] == 321.0)
		rectangle(225, 240, 375, 320, 1, 1, 0);
	if (move_x[2] == 375.0)
		rectangle(225, 240, 375, 320, 1, 0, 0);
	if (move_xy[0][0] == 222)
		rectangle(225, 240, 375, 320, 0, 1, 0);

	drawSquare(300, 50, 54, 0, 0.133f, 0.231f);	 // Square -sender
	drawSquare(300, 150, 36, 0, 0.494f, 0.655f); // Square - encoding
	drawSquare(300, 400, 36, 0, 0.494f, 0.655f); // Square - helper
	drawSquare(520, 280, 36, 0, 0.494f, 0.655f); // Square - spies
	drawSquare(80, 450, 54, 0, 0.133f, 0.231f);	 // Square - Receiver
	drawSquare(520, 450, 54, 0, 0.133f, 0.231f); // Square - master spy
	rectangle(260, 520, 340, 580, 0, 0, 0);		 // rectangle - parent

	rectangle(30, 540, 130, 560, 1, 1, 1);	// rectangle - operation has failed
	rectangle(470, 540, 570, 560, 1, 1, 1); // rectangle - operation is successful
	if (fail_succ[0])
		rectangle(30, 540, 130, 560, 1, 0, 0); // rectangle - operation has failed - to red
	else if (fail_succ[1])
		rectangle(470, 540, 570, 560, 0, 1, 0); // rectangle - operation is successful - to green

	rectangle(0, 0, 600, 12, 0.2706f, 0.2863f, 0.3333f);	// frame -1
	rectangle(0, 588, 600, 600, 0.2706f, 0.2863f, 0.3333f); // frame -2
	rectangle(0, 0, 12, 600, 0.2706f, 0.2863f, 0.3333f);	// frame -3
	rectangle(588, 0, 600, 600, 0.2706f, 0.2863f, 0.3333f); // frame -4

	//* Text inside *//
	drawText_size(0, 0, "", 18);
	drawText_size(256, 280, "Shared Memory", 18);
	drawText_size(280, 50, "Sender", 18);
	drawText_size(56, 450, "Receiver", 18);
	drawText_size(500, 450, "Master", 18);
	drawText_size(508, 438, "Spy", 18);
	drawText_size(283, 550, "Parent", 18);
	drawText_size(285, 150, "Encoding", 10);
	drawText_size(290, 400, "Helper", 10);
	drawText_size(512, 280, "Spies", 10);
	drawText_size(45, 550 - 2, "Operation has FAILED", 10);
	drawText_size(475, 550 - 2, "Operation has SUCCESSFUL", 10);

	//* Lines between the processes*//
	drawLine(300, 77, 300, 132);  // sender --> encoding
	drawLine(300, 168, 300, 240); // encoding --> shared memory
	drawLine(300, 382, 300, 320); // helper --> shared memory
	drawLine(80, 280, 225, 280);  // Decoding --> shared memory
	drawLine(502, 280, 375, 280); // spies --> shared memory
	drawLine(80, 280, 80, 423);	  // Decoding --> Receiver
	drawLine(520, 298, 520, 423); // spies --> master spy
	drawLine(107, 450, 300, 450); // Receiver -->
	drawLine(493, 450, 300, 450); // master spy -->
	drawLine(300, 450, 300, 520); //--> parent
	drawLine(260, 550, 130, 550); // parent --> operation has failed
	drawLine(340, 550, 470, 550); // parent --> operation is successful

	//* Table - 1 *//
	drawTextTable(1, 5, 140, 25, 52, 38);
	drawTextTable(1, 5, 30, 25, 192, 38);
	drawText_size(59, 150, "Columns", 15);
	drawText_size(59, 125, "Spies processes", 15);
	drawText_size(59, 100, "Helper processes", 15);
	drawText_size(59, 75, "Failed (threshold)", 15);
	drawText_size(59, 50, "Successful (threshold)", 15);
	writeIntegerAtPosition(indices, 205, 145);			 // # of Columns processes
	writeIntegerAtPosition(num_of_spy_proc, 205, 120);	 // # of Spies processes
	writeIntegerAtPosition(num_of_helper_proc, 205, 95); // # of Helper processes
	writeIntegerAtPosition(failure_threshold, 205, 70);	 // Failed (threshold)
	writeIntegerAtPosition(sucess_threshold, 205, 45);	 // Successful (threshold)

	//* Table - 2 *//
	drawTextTable(1, 3, 140, 25, 378, 38);
	drawTextTable(1, 3, 30, 25, 518, 38);
	drawText_size(385, 100, "Encoding operations", 15);
	drawText_size(385, 75, "Failed operations", 15);
	drawText_size(385, 50, "Successful operations", 15);
	writeIntegerAtPosition(indices, 531, 95);				 // # of Encoding operations
	writeIntegerAtPosition(num_of_failed_decoding, 531, 70);	 // # of Failed operations
	writeIntegerAtPosition(num_of_successful_decoding, 531, 45); // # of Successful operations

	//* Small squares to move *//
	drawSquare(300, move_y[0], 8, 0, 0.133f, 0.231f);				// sender --> encoding
	drawSquare(300, move_y[1], 8, 0, 1, 0);							// encoding --> shared memory
	drawSquare(520, move_y[2], 8, 1, 0, 0);							// spies --> master spy
	drawSquare(300, move_y[3], 8, 1, 1, 0);							// helper --> shared memory
	drawSquare(move_x[2], 280, 8, 1, 0, 0);							// spies --> shared memory
	drawSquare(move_xy[0][0], move_xy[0][1], 8, 0, 1, 0);			// Receiver --> shared memory
	drawSquare(move_xy[1][0], move_xy[1][1], 8, 0, 0.133f, 0.231f); // Receiver --> parent
	drawSquare(move_xy[2][0], move_xy[2][1], 8, 0, 0.133f, 0.231f); // master spy --> parent
	drawSquare(move_x[1], 550, 8, 1, 0, 0);							// parent --> failed
	drawSquare(move_x[0], 550, 8, 0, 1, 0);							// parent --> successful
	if (op_successful && go)
		drawSquare(move_x[0], 550, 8, 0, 1, 0); // parent --> successful
	else if (!op_successful && go)
		drawSquare(move_x[1], 550, 8, 1, 0, 0); // parent --> failed

	//* Colorers meaning *//
	drawSquare(65, 175, 8, 0, 1, 0); // Green square
	drawText_size(73, 172, "Encoded column", 15);
	drawSquare(65, 190, 8, 1, 0, 0); // Red square
	drawText_size(73, 187, "Spy column", 15);
	drawSquare(65, 205, 8, 1, 1, 0); // Green square
	drawText_size(73, 202, "Swap", 15);

	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

//--------------------------------------------------------------------

void timer()
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);


	//* move Y-axis --> {77.0, 168.0, 298.0, 382.0}; --> {sender, encoding, spies, helper}*//
	//-------------------------------------
	if (move_y[0] < 136)
		move_y[0] += 2;
	else if (sender_counter != 1)
	{
		move_y[0] = 77.0;
		encoding_go = true;
		sender_counter++;
	}
	else if (sender_counter == 1 && first_time)
	{
		state_RHS[0] = true;
		state_RHS[1] = true;
		state_RHS[2] = true;
		first_time = false;
	}
	else
	{
		encoding_go = false;
	}
	//-------------------------------------
	if (encoding_go)
	{
		if (move_y[1] < 240)
			move_y[1] += 2.5;
		else
		{
			encoding_go = false;
			move_y[1] = 168.0;
		}
	}
	//-------------------------------------
	if (move_x[2] == 501 && !spies_go[0])
		spies_go[1] = true;
	else if (move_y[2] == 430)
		spies_go[1] = false;

	if (spies_go[1])
	{
		if (move_y[2] < 430)
			move_y[2]++;
		else
			move_y[2] = 298.0;
	}
	//-------------------------------------
	if (state_RHS[1])
	{
		if (move_y[3] > 320)
			move_y[3] -= 0.5;
		else
		{
			move_y[3] = 382.0;
			num_swap++;
		}
	}
	//-------------------------------------

	//* move X-axis --> {340.0, 260.0, 502.0} --> {parent-successful, parent-failed, spies} *//
	//-------------------------------------
	if (op_successful && go)
	{
		if (move_x[0] < 470)
			move_x[0]++;
		else
			fail_succ[1] = true;
	}
	//-------------------------------------
	if (!op_successful && go)
	{
		if (move_x[1] > 130)
			move_x[1]--;
		else
			fail_succ[0] = true;
	}
	//-------------------------------------
	if (state_RHS[2])
	{
		if (spies_go[0])
		{
			if (move_x[2] > 375)
				move_x[2]--;
			else
				spies_go[0] = false;
		}
		else if (!spies_go[0])
		{
			if (move_x[2] < 502)
				move_x[2]++;
			else
				spies_go[0] = true;
		}
	}
	//-------------------------------------

	//* move XY-axis --> {{80.0, 423.0}, {107.0, 450.0}, {493.0, 450.0}} --> {to receiver, from receiver, from master spy} *//
	//-------------------------------------
	if (state_RHS[0])
	{
		if (receiver_go[0])
		{
			if (move_xy[0][1] > 280)
				move_xy[0][1] -= 2;
			else if (move_xy[0][0] < 225)
				move_xy[0][0] += 2;
			else
				receiver_go[0] = false;
		}
		else if (!receiver_go[0])
		{
			if (move_xy[0][0] > 80)
				move_xy[0][0] -= 2;
			else if (move_xy[0][1] < 423)
				move_xy[0][1] += 2;
			else
				receiver_go[0] = true;
		}
	}
	//-------------------------------------
	if (ready_to_parent[0] && num_of_successful_decoding != sucess_threshold)
	{
		if (move_xy[1][0] < 300)
			move_xy[1][0]++;
		else if (move_xy[1][1] < 520)
			move_xy[1][1]++;
		else if (move_xy[1][0] == 300 && move_xy[1][1] == 520)
		{
			move_xy[1][0] = 107.0;
			move_xy[1][1] = 450.0;
			ready_to_parent[0] = false;
		}
	}

	//-------------------------------------
	if (ready_to_parent[1] && num_of_failed_decoding != failure_threshold)
	{
		if (move_xy[2][0] > 300)
			move_xy[2][0]--;
		else if (move_xy[2][1] < 520)
			move_xy[2][1]++;
		else if (move_xy[2][0] == 300 && move_xy[2][1] == 520)
		{
			move_xy[2][0] = 493.0;
			move_xy[2][1] = 450.0;
			ready_to_parent[1] = false;
		}
	}
	//-------------------------------------
	if(flag !=0 ){
		flag++;
		if(flag == 200){
			sleep(5);
			endProgram();
			exit(0);
		}
	}
	if(spy_got_msg == 1 && receiver_got_msg ==1 && flag == 0)
		tempMain();
}


void tempMain(){
	receiver_got_msg = spy_got_msg = 0;
	for (int i = 0; i < num_of_helper_proc; i++)
	{
		kill(helper_processes[i], SIGUSR1);
	}

	for (int i = 0; i < num_of_spy_proc; i++)
	{
		kill(spy_processes[i], SIGUSR1);
	}

	if (got_msg_first == 1)
	{
		int match_file = compareFiles(SENDER_FILE, SPY_FILE);
		if (match_file == 1)
		{
			num_of_failed_decoding++;
		}
		else
		{
			int match_file = compareFiles(SENDER_FILE, RECEIVER_FILE);
			if (match_file == 1){
				num_of_successful_decoding++;
			}
		}
	}
	if (got_msg_first == 0)
	{
		int match_file = compareFiles(SENDER_FILE, RECEIVER_FILE);
		if (match_file == 1)
		{
			num_of_successful_decoding++;
		}
		else
		{
			int match_file = compareFiles(SENDER_FILE, SPY_FILE);
			if (match_file == 1){
				num_of_failed_decoding++;
			}
		}
	}

	printf(PURPLE "num_of_successful_decoding %d - num_of_failed_decoding %d\n" RESET, num_of_successful_decoding, num_of_failed_decoding);
	if (num_of_failed_decoding == failure_threshold)
	{
		op_successful = false;
		go = true;
		state_RHS[0]= false;
		state_RHS[1]= false;
		state_RHS[2]= false;
		flag = 1;
		return;
	}
	if (num_of_successful_decoding == sucess_threshold)
	{
		op_successful = true;
		go = true;
		state_RHS[0]= false;
		state_RHS[1]= false;
		state_RHS[2]= false;
		flag = 1;	
		return;	
	}
	kill(receiver_pid, SIGUSR2);
	kill(master_spy_pid, SIGUSR2);
	for (int i = 0; i < num_of_helper_proc; i++)
	{
		kill(helper_processes[i], SIGUSR2);
	}
	for (int i = 0; i < num_of_spy_proc; i++)
	{
		kill(spy_processes[i], SIGUSR2);
	}
	got_msg_first = 2;
}


void endProgram(){
	kill(receiver_pid, SIGTERM);
	kill(master_spy_pid, SIGTERM);
	for (int i = 0; i < num_of_helper_proc; i++)
	{
		kill(helper_processes[i], SIGTERM);
	}
	for (int i = 0; i < num_of_spy_proc; i++)
	{
		kill(spy_processes[i], SIGTERM);
	}

	free(helper_processes);
	free(spy_processes);
	shmdt(shmptr);
	deleteAll();
	printf(BLUE "Parent is finished\n" RESET);
	exit(0);
}
//--------------------------------------------------------------------

void init()
{
	glClearColor(0.7529f, 0.7529f, 0.7529f, 1.0f);
}

//--------------------------------------------------------------------

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 600, 0, 600);
	glMatrixMode(GL_MODELVIEW);
}

//--------------------------------------------------------------------

void rectangle(int x1, int y1, int x2, int y2, float r, float g, float b)
{
	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
}

//--------------------------------------------------------------------

void drawSquare(int centerX, int centerY, int sideLength, float red, float green, float blue)
{
	int halfSide = sideLength / 2; // Calculate half of the side length

	int vertices[] = {
		centerX - halfSide, centerY - halfSide, // Bottom-left vertex
		centerX + halfSide, centerY - halfSide, // Bottom-right vertex
		centerX + halfSide, centerY + halfSide, // Top-right vertex
		centerX - halfSide, centerY + halfSide	// Top-left vertex
	};

	glColor3f(red, green, blue); // Set the color of the square

	glBegin(GL_QUADS); // Draw the square
	for (int i = 0; i < 4; i++)
		glVertex2f(vertices[i * 2], vertices[i * 2 + 1]);
	glEnd();
}

//--------------------------------------------------------------------

void drawText_size(int centerX, int centerY, char *str, int size)
{
	glRasterPos2i(centerX, centerY); // Position for Square 1 text
	const char *text1 = str;

	if (size == 18)
	{
		glColor3f(1, 1, 1);
		for (int i = 0; i < strlen(text1); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
	}
	else if (size == 10)
	{
		glColor3f(0, 0, 0);
		for (int i = 0; i < strlen(text1); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text1[i]);
	}
	else if (size == 15)
	{
		glColor3f(0, 0, 0);
		for (int i = 0; i < strlen(text1); i++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text1[i]);
	}
}

//--------------------------------------------------------------------

void drawLine(int centerX1, int centerY1, int centerX2, int centerY2)
{
	glColor3f(0, 0, 0); // Set color to black
	glBegin(GL_LINES);
	glVertex2i(centerX1, centerY1);
	glVertex2i(centerX2, centerY2);
	glEnd();
}

//--------------------------------------------------------------------

void writeIntegerAtPosition(int number, float x, float y)
{
	glRasterPos2f(x, y);
	char str[10];
	sprintf(str, "%d", number);
	for (int i = 0; str[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
}

//--------------------------------------------------------------------

void drawTextTable(int numCols, int numRows, int cellWidth, int cellHeight, int posX, int posY)
{
	glColor3f(0, 0, 0);
	glLineWidth(2.0f);

	// Draw horizontal lines
	for (int i = 0; i <= numRows; i++)
	{
		glBegin(GL_LINES);
		glVertex2i(posX, posY + i * cellHeight);
		glVertex2i(posX + numCols * cellWidth, posY + i * cellHeight);
		glEnd();
	}

	// Draw vertical lines
	for (int i = 0; i <= numCols; i++)
	{
		glBegin(GL_LINES);
		glVertex2i(posX + i * cellWidth, posY);
		glVertex2i(posX + i * cellWidth, posY + numRows * cellHeight);
		glEnd();
	}

	// Draw text in each cell
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			int xPos = posX + col * cellWidth + 10;
			int yPos = posY + row * cellHeight + 20;

			char cellText[50];
			sprintf(cellText, "Cell %d,%d", row, col);
		}
	}
}

//--------------------------------------------------------------------