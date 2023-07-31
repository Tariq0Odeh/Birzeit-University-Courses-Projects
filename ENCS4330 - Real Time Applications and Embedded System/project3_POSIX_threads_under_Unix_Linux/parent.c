#include "local.h"

//------------------------------------------------Global variables-------------------------------------------------------------//

int NUM_OF_ANTS, NUM_OF_FOODS;
int MIN_SPEED, MAX_SPEED;
int FOOD_TIMER, FOOD_SMELL_DISTANCE;
int PHEROMONE_SMELL_DISTANCE_THRESHOLD;
float FOOD_PORTION;
int SIMULATION_TIMER;

pthread_t *p_threads;
pthread_t *p_threads_food;
Ant *ants;
Food *foods;
int *threads_id;
int *threads_id_food;
int num_mutex = 0;

int windowWidth = 1100;                              // Width of the window
int windowHeight = 1050;                             // Height of the window
int hight_area = 842;                                // Height of area that ants can move on it
int start_counter = 10;                              // Time to start the simulation
int end_counter = 0;                                 // Counter to end the simulation
int start_state = 0;                                 // Flag to start the simulation
int creatAnt_state = 1;                              // Flag to help to end the simulation
int foodMain_state = 1;                              // Flag to help to end the simulation
int angles[] = {0, 45, 90, 135, 180, 225, 270, 315}; // The directions of ants
float foodSize = 0.3;                                // The size of food that display on the screen
int num_Afood = 0;                                   // Number of foods
int num_Peat = 0;                                    // Number of food that eaten

//--------------------------------------------Functions declarations/prototypes --------------------------------------------------//

void read_arguments(char *argument_file);
void *createAnt(void *arg);
void *foodMainThread();
void *createFood(void *arg);
void *endSimulation_Time(void *arg);
void exit_program();
void startOpenGl();
void display();
void init();
void timer();
void reshape(int w, int h);
void drawAnt(Ant square);
void drawFood(Food foodPiece);
void rectangle(int x1, int y1, int x2, int y2, float r, float g, float b);
void drawText_size(int centerX, int centerY, char *str, int size);
void drawTextTable(int numCols, int numRows, int cellWidth, int cellHeight, int posX, int posY);
void writeIntegerAtPosition(int number, float x, float y);
void writeFloatAtPosition(float number, float x, float y);
void displayFloat(float number, float x, float y);
void drawString(float x, float y, const char *string);
void displayCircle(float centerX, float centerY, float radius);

//----------------------------------------------------The Main-----------------------------------------------------------------//

int main(int argc, char **argv)
{
    if(argc != 2){
        printf("Please enter arguments.txt as input.\n");
    }
    read_arguments(argv[1]);
    printf(BLUE "File read successfully\n" RESET);

    p_threads = malloc(sizeof(p_threads) * NUM_OF_ANTS);
    ants = malloc(sizeof(Ant) * NUM_OF_ANTS);
    threads_id = malloc(sizeof(int) * NUM_OF_ANTS);

    NUM_OF_FOODS = (SIMULATION_TIMER * 60) / FOOD_TIMER;

    p_threads_food = malloc(sizeof(p_threads_food) * NUM_OF_FOODS);
    foods = malloc(sizeof(Food) * NUM_OF_FOODS);
    threads_id_food = malloc(sizeof(int) * NUM_OF_FOODS);

    for (int i = 0; i < NUM_OF_ANTS; i++) // create the ants and give them random locations and speeds
    {
        threads_id[i] = pthread_create(&p_threads[i], NULL, createAnt, &ants[i]);
        if (threads_id[i] != 0)
        {
            printf("Failed to create Ants thread.\n");
            exit(-1);
        }
    }

    pthread_t foodThread;
    int foodThread_id = pthread_create(&foodThread, NULL, foodMainThread, NULL);
    if (foodThread_id != 0)
    {
        printf("Failed to create main Food thread.\n");
        exit(-2);
    }

    pthread_t timeEndThread;
    int ftimeEndThread_id = pthread_create(&timeEndThread, NULL, endSimulation_Time, NULL);
    if (ftimeEndThread_id != 0)
    {
        printf("Failed to create endSimulation_Time thread.\n");
        exit(-3);
    }

    glutInit(&argc, argv);
    startOpenGl();

    return 0;
}

//----------------------------------------------------Functions----------------------------------------------------------------//

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
        if (strcmp(token, "NUM_OF_ANTS") == 0)
        {
            token = strtok(NULL, " ");
            NUM_OF_ANTS = atoi(token);
        }
        else if (strcmp(token, "SPEED_RANGE") == 0)
        {
            token = strtok(NULL, " ");
            MIN_SPEED = atoi(token);
            token = strtok(NULL, " ");
            MAX_SPEED = atoi(token);
        }
        else if (strcmp(token, "FOOD_TIMER") == 0)
        {
            token = strtok(NULL, " ");
            FOOD_TIMER = atoi(token);
        }
        else if (strcmp(token, "FOOD_SMELL_DISTANCE") == 0)
        {
            token = strtok(NULL, " ");
            FOOD_SMELL_DISTANCE = atoi(token);
        }
        else if (strcmp(token, "PHEROMONE_SMELL_DISTANCE_THRESHOLD") == 0)
        {
            token = strtok(NULL, " ");
            PHEROMONE_SMELL_DISTANCE_THRESHOLD = atoi(token);
        }
        else if (strcmp(token, "FOOD_PORTION") == 0)
        {
            token = strtok(NULL, " ");
            FOOD_PORTION = atof(token);
        }
        else if (strcmp(token, "SIMULATION_TIMER") == 0)
        {
            token = strtok(NULL, " ");
            SIMULATION_TIMER = atoi(token);
        }
    }

    fclose(file);
}

//--------------------------------------------------------------------

void *createAnt(void *arg)
{
    sleep(start_counter);
    int direction;
    start_state = 1;
    Ant *ant = (Ant *)arg;
    ant->posX = rand() % (windowWidth - 12);
    ant->posY = rand() % (hight_area - 12);
    int randomIndex = rand() % 8;     // Generate random index within the array size
    ant->angle = angles[randomIndex]; // Get the random number from the array
    int temp = rand() % MAX_SPEED + MIN_SPEED;
    ant->speed = MIN_SPEED + temp * 0.2;
    ant->strong_pheromone = 0;
    ant->weak_pheromone = 0;
    ant->closestFood = -1;

    while (creatAnt_state)
    {
        int closestFood = -1;
        int minimumDis = 1800;
        for (int i = 0; i < NUM_OF_FOODS; i++)
        {
            if (&foods[i] == NULL || foods[i].quantity <= 0.0)
            {
                ant->strong_pheromone = 0;
                continue;
            }
            float sq1 = (ant->posX - foods[i].posX);
            float sq2 = (ant->posY - foods[i].posY);
            int distance = sqrt(sq1 * sq1 + sq2 * sq2);
            if (closestFood == -1 || distance < minimumDis)
            {
                closestFood = i;
                minimumDis = distance;
            }
        }

        if (closestFood != -1 && minimumDis <= 2 && foods[closestFood].quantity > 0.0)
        {
            int food_portion = rand() % num_mutex; // Generate a random number between 0 and 4
            pthread_mutex_lock(&foods[closestFood].food_mutex[food_portion]);
            foods[closestFood].quantity -= FOOD_PORTION;
            pthread_mutex_unlock(&foods[closestFood].food_mutex[food_portion]);
            printf(YELLOW "Portion has been eaten by ants\n" RESET);
            num_Peat++;
            sleep(1);
        }

        if (closestFood != -1 && foods[closestFood].quantity == 0)
        {
            printf(RED "The food is finished\n" RESET);
            continue;
        }

        if (minimumDis <= FOOD_SMELL_DISTANCE) // if the distance to specific food piece is less than threshold
        {
            ant->strong_pheromone = 1;
            ant->closestFood = closestFood;
            float dy = ant->posY - foods[closestFood].posY;
            float dx = ant->posX - foods[closestFood].posX;
            int new_angle = atan(dy / dx) * 180 / M_PI;

            if (ant->posX >= foods[closestFood].posX && ant->posY >= foods[closestFood].posY)
            {
                ant->angle = (180 + new_angle) % 360;
            }
            else if (ant->posX >= foods[closestFood].posX && ant->posY <= foods[closestFood].posY)
            {
                ant->angle = (180 + new_angle) % 360;
            }
            else if (ant->posX <= foods[closestFood].posX && ant->posY >= foods[closestFood].posY)
            {
                ant->angle = (360 + new_angle) % 360;
            }
            else
            {
                ant->angle = (new_angle) % 360;
            }
        }

        int closestAnt_1 = -1;
        int minDis_1 = 1800;
        for (int i = 0; i < NUM_OF_ANTS; i++)
        {
            if (ant == &ants[i])
                continue;
            float sq1 = (ant->posX - ants[i].posX);
            float sq2 = (ant->posY - ants[i].posY);
            int distance = sqrt(sq1 * sq1 + sq2 * sq2);
            if (closestAnt_1 == -1 || distance < minDis_1)
            {
                if (ants[i].strong_pheromone && ant->strong_pheromone != 1)
                {
                    closestAnt_1 = i;
                    minDis_1 = distance;
                }
                else
                {
                    ant->weak_pheromone = 0;
                }
            }
        }

        if (minDis_1 <= PHEROMONE_SMELL_DISTANCE_THRESHOLD && ant->strong_pheromone != 1)
        {
            ant->closestFood = ants[closestAnt_1].closestFood;
            ant->weak_pheromone = 1;

            float dy = ant->posY - foods[ants[closestAnt_1].closestFood].posY;
            float dx = ant->posX - foods[ants[closestAnt_1].closestFood].posX;
            int new_angle = atan(dy / dx) * 180 / M_PI;

            if (ant->posX >= foods[ants[closestAnt_1].closestFood].posX &&
                ant->posY >= foods[ants[closestAnt_1].closestFood].posY)
            {
                ant->angle = (180 + new_angle) % 360;
            }
            else if (ant->posX >= foods[ants[closestAnt_1].closestFood].posX &&
                     ant->posY <= foods[ants[closestAnt_1].closestFood].posY)
            {
                ant->angle = (180 + new_angle) % 360;
            }
            else if (ant->posX <= foods[ants[closestAnt_1].closestFood].posX &&
                     ant->posY >= foods[ants[closestAnt_1].closestFood].posY)
            {
                ant->angle = (360 + new_angle) % 360;
            }
            else
            {
                ant->angle = (new_angle) % 360;
            }
        }

        int closestAnt_2 = -1;
        int minDis_2 = 1800;
        for (int i = 0; i < NUM_OF_ANTS; i++)
        {
            if (ant == &ants[i])
                continue;
            float sq1 = (ant->posX - ants[i].posX);
            float sq2 = (ant->posY - ants[i].posY);
            int distance = sqrt(sq1 * sq1 + sq2 * sq2);
            if (closestAnt_2 == -1 || distance < minDis_2)
            {
                if (ants[i].weak_pheromone)
                {
                    closestAnt_2 = i;
                    minDis_2 = distance;
                }
            }
        }

        if (minDis_2 <= PHEROMONE_SMELL_DISTANCE_THRESHOLD && ant->strong_pheromone != 1 && ant->weak_pheromone != 1)
        {
            int tmp11 = ant->speed * cos(((ant->angle + 5)) % 360 * M_PI / 180.0);
            int tmp12 = ant->speed * sin(((ant->angle + 5)) % 360 * M_PI / 180.0);

            int tmp21 = ant->speed * cos(((ant->angle - 5)) % 360 * M_PI / 180.0);
            int tmp22 = ant->speed * sin(((ant->angle - 5)) % 360 * M_PI / 180.0);

            float y = foods[ants[closestAnt_2].closestFood].posY;
            float x = foods[ants[closestAnt_2].closestFood].posX;

            if (sqrt((tmp11 - x) * (tmp11 - x) + (tmp12 - y) * (tmp12 - y)) <=
                sqrt((tmp21 - x) * (tmp21 - x) + (tmp22 - y) * (tmp22 - y)))
            {
                ant->angle = (ant->angle + 5) % 360;
            }
            else
            {
                ant->angle = (ant->angle - 5) % 360;
                if(ant->angle < 0)
                    ant->angle += 360;
            }
        }

        ant->posX += ant->speed * cos(ant->angle * M_PI / 180.0);
        ant->posY += ant->speed * sin(ant->angle * M_PI / 180.0);

        ant->posX = round(ant->posX);
        ant->posY = round(ant->posY);

        if (ant->posX <= 0 || ant->posX >= windowWidth || ant->posY <= 0 || ant->posY >= hight_area)
        {
            // Change direction with an additional 45° angle (CW or CCW)
            direction = (rand() % 2 == 0) ? 1 : 1; 
            ant->angle = ((ant->angle + 180) + (45 * direction)) % 360;
            if(ant->angle < 0)
                ant->angle += 360;
        }
        usleep(16670);
    }
    pthread_exit(NULL);
}

//--------------------------------------------------------------------

void *foodMainThread()
{
    sleep(start_counter);
    for (int i = 0; i < NUM_OF_FOODS; i++) //  create the Foods and give them random locations
    {
        if (!foodMain_state)
        {
            break;
        }
        threads_id_food[i] = pthread_create(&p_threads_food[i], NULL, createFood, &foods[i]);
        printf(GREEN "Food has been set\n" RESET);
        num_Afood++;
        if (threads_id_food[i] != 0)
        {
            printf("Failed to create Food thread.\n");
        }
        pthread_join(threads_id_food[i], NULL);
        sleep(FOOD_TIMER);
    }
    pthread_exit(NULL);
}

//--------------------------------------------------------------------

void *createFood(void *arg)
{
    Food *foodPiece = (Food *)arg;
    foodPiece->posX = rand() % (windowWidth - 12);
    foodPiece->posY = rand() % (hight_area - 12);
    foodPiece->quantity = 1.0;
    num_mutex = (int)(foodPiece->quantity / FOOD_PORTION);
    for (int i = 0; i < num_mutex; i++)
    {
        pthread_mutex_init(&foodPiece->food_mutex[i], NULL);
    }
}

//--------------------------------------------------------------------

void *endSimulation_Time(void *arg)
{
    sleep((SIMULATION_TIMER * 60) + start_counter);
    creatAnt_state = 0;
    foodMain_state = 0;
    usleep(10000);
    for(int i=0;i<NUM_OF_ANTS;i++){
        pthread_cancel(p_threads[i]); 
    }
    for(int i=0;i<NUM_OF_FOODS;i++){
        pthread_cancel(p_threads_food[i]); 
    }
    exit_program();
    pthread_exit(NULL);
}

//--------------------------------------------------------------------

void exit_program()
{
    for (int i = 0; i < NUM_OF_FOODS; i++)
    {
        for (int j = 0; j < num_mutex; j++)
        {
            pthread_mutex_destroy(&foods[i].food_mutex[j]);
        }
    }

    free(p_threads);
    free(ants);
    free(threads_id);
    free(p_threads_food);
    free(foods);
    free(threads_id_food);

    raise(SIGTERM);
}

//--------------------------------------------------------------------

void startOpenGl()
{
    init();
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, hight_area);
    glutInitWindowPosition(500, 200);
    glutCreateWindow("Ant searching for food simulation");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
}

//--------------------------------------------------------------------

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glutPostRedisplay();

    if (start_state && creatAnt_state && foodMain_state)
    {
        for (int i = 0; i < NUM_OF_ANTS; i++)
        {
            // Position and scale the ant
            glPushMatrix();
            glTranslatef(ants[i].posX, ants[i].posY, 0.0f); // Set position
            glScalef(100.0f, 100.0f, 1.0f);
            glRotatef(ants[i].angle, 0.0f, 0.0f, 1.0f);
            drawAnt(ants[i]);
            glPopMatrix();
        }

        for (int i = 0; i < NUM_OF_FOODS; i++)
        {
            if (foods[i].quantity > 0) // Position and scale the food Piece
            {
                glPushMatrix();
                glTranslatef(foods[i].posX, foods[i].posY, 0.0f); // Set position
                glScalef(100.0f, 100.0f, 1.0f);
                drawFood(foods[i]);
                glPopMatrix();
                displayCircle(foods[i].posX, foods[i].posY, FOOD_SMELL_DISTANCE);
            }
        }
    }

    rectangle(0, 0, 8, 850, 0.5333, 0.2902, 0.2235);       // line-x1
    rectangle(1200, 0, 1092, 850, 0.5333, 0.2902, 0.2235); // line-x2
    rectangle(0, 0, 1100, 8, 0.5333, 0.2902, 0.2235);      // line-y1
    rectangle(0, 850, 1100, 842, 0.5333, 0.2902, 0.2235);  // line-y2

    rectangle(0, 850, 1100, 1000, 0.1f, 0.2f, 0.25f); // background for inf

    //------------

    // Table-1//

    rectangle(237, 924, 443, 968, 0.3255, 0.4431, 0.5333);
    drawText_size(260, 940, "Number of ants: ", 15);
    writeIntegerAtPosition(NUM_OF_ANTS, 400, 938);

    rectangle(237, 872, 443, 920, 0.3255, 0.4431, 0.5333);
    drawText_size(275, 890, "Food timer: ", 15);
    writeIntegerAtPosition(FOOD_TIMER, 380, 888);

    rectangle(447, 934, 653, 978, 0.3255, 0.4431, 0.5333);
    drawText_size(470, 950, "Speed range: ", 15);
    writeIntegerAtPosition(MIN_SPEED, 580, 948);
    drawText_size(590, 948, "-", 18);
    writeIntegerAtPosition(MAX_SPEED, 600, 948);

    rectangle(447, 882, 653, 930, 0.3255, 0.4431, 0.5333);
    drawText_size(485, 900, "Food Portion: ", 15);
    writeFloatAtPosition(FOOD_PORTION, 610, 898);

    rectangle(657, 924, 863, 968, 0.3255, 0.4431, 0.5333);
    drawText_size(675, 940, "Pheromone smell: ", 15);
    writeIntegerAtPosition(PHEROMONE_SMELL_DISTANCE_THRESHOLD, 823, 938);

    rectangle(657, 872, 863, 920, 0.3255, 0.4431, 0.5333);
    drawText_size(690, 890, "Food smell: ", 15);
    writeIntegerAtPosition(FOOD_SMELL_DISTANCE, 798, 888);

    //------------

    // Table-2//
    rectangle(47, 937, 233, 983, 0.1255, 0.8039, 0.1961);
    drawText_size(65, 955, "Start in (sec): ", 15);
    writeIntegerAtPosition(start_counter, 205, 953);

    rectangle(47, 887, 233, 933, 0.3255, 0.4431, 0.5333);
    drawText_size(65, 905, "Number of food: ", 15);
    writeIntegerAtPosition(num_Afood, 205, 903);

    //------------

    // Table-3//
    rectangle(867, 937, 1053, 983, 0.8118, 0.1294, 0.1608);
    drawText_size(885, 955, "End in (sec): ", 15);
    writeIntegerAtPosition((SIMULATION_TIMER * 60) - end_counter, 1005, 953);

    rectangle(867, 887, 1053, 933, 0.3255, 0.4431, 0.5333);
    drawText_size(880, 905, "Portions eaten: ", 15);
    writeIntegerAtPosition(num_Peat, 1018, 903);

    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}

//--------------------------------------------------------------------

void timer()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();

    if (start_counter > 0)
    {
        start_counter--;
        glutPostRedisplay();           // Mark the current window for redisplay
        glutTimerFunc(1000, timer, 0); // Set the timer for the next decrement
    }
    else if (end_counter != SIMULATION_TIMER * 60)
    {
        end_counter++;
        glutPostRedisplay();           // Mark the current window for redisplay
        glutTimerFunc(1000, timer, 0); // Set the timer for the next decrement
    }
    else
    {
        glutPostRedisplay(); // Mark the current window for redisplay
        glutTimerFunc(1000 / 60, timer, 0);
    }
}

//--------------------------------------------------------------------

void init()
{
    glClearColor(0.9608, 0.9373, 0.9059, 1.0f);
}

//--------------------------------------------------------------------

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1100, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
}

//--------------------------------------------------------------------

void drawFood(Food foodPiece)
{
    glColor3f(0.588f, 0.294f, 0.0f); // Set color
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, foodSize);
    glVertex2f(foodSize / 5, foodSize);
    glVertex2f(foodSize / 5, 0.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); // Set color
    glBegin(GL_POLYGON);
    glVertex2f(foodSize / 5, 0.0f);
    glVertex2f(foodSize / 5, foodSize);
    glVertex2f(2 * foodSize / 5, foodSize);
    glVertex2f(2 * foodSize / 5, 0.0f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f); // Set color
    glBegin(GL_POLYGON);
    glVertex2f(2 * foodSize / 5, 0.0f);
    glVertex2f(2 * foodSize / 5, foodSize);
    glVertex2f(foodSize, foodSize);
    glVertex2f(foodSize, 0.0f);
    glEnd();
}

//--------------------------------------------------------------------

void drawCircle(float cx, float cy, float r, int num_segments)
{

    glColor3f(0.6f, 0.4f, 0.2f); // Set the color to brown
    glBegin(GL_POLYGON);

    for (int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * (float)i / (float)num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);

        // Adjust x-coordinate to make the circle look more oval-like
        if (x < 0)
        {
            x -= r * 0.15f;
        }
        else
        {
            x += r * 0.15f;
        }

        glVertex2f(x + cx, y + cy);
    }

    glEnd();

    // Draw legs
    glColor3f(0.0f, 0.0f, 0.0f); // Set leg color to black
    glBegin(GL_LINES);

    // Top side legs
    float legOffset = r * 0.2f;                            // Adjust the offset for space between lines
    glVertex2f(cx - r * 0.25f - legOffset, cy + r * 1.2f); // Start point of the leg
    glVertex2f(cx - r * 0.45f - legOffset, cy + r * 1.8f); // End point of the leg

    glVertex2f(cx + r * 0.25f + legOffset, cy + r * 1.2f); // Start point of the leg
    glVertex2f(cx + r * 0.45f + legOffset, cy + r * 1.8f); // End point of the leg

    // Bottom side legs
    glVertex2f(cx - r * 0.25f - legOffset, cy - r * 1.2f); // Start point of the leg
    glVertex2f(cx - r * 0.45f - legOffset, cy - r * 1.8f); // End point of the leg

    glVertex2f(cx + r * 0.25f + legOffset, cy - r * 1.2f); // Start point of the leg
    glVertex2f(cx + r * 0.45f + legOffset, cy - r * 1.8f); // End point of the leg

    glEnd();
}

void drawAnt(Ant square)
{
    // Body
    drawCircle(0.0f, 0.0f, 0.1f, 100); // Center at (0, 0), radius 0.1, 100 segments

    // Head
    glColor3f(0.4f, 0.2f, 0.1f); // Set head color to dark brown
    glPushMatrix();
    glTranslatef(0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 50, 50);
    glPopMatrix();

    // Left Eye
    glColor3f(1.0f, 1.0f, 1.0f); // Set eye color to white
    glPushMatrix();
    glTranslatef(0.09f, 0.02f, 0.06f);
    glutSolidSphere(0.01f, 20, 20);
    glPopMatrix();

    // Right Eye
    glColor3f(1.0f, 1.0f, 1.0f); // Set eye color to white
    glPushMatrix();
    glTranslatef(0.09f, -0.02f, 0.06f);
    glutSolidSphere(0.01f, 20, 20);
    glPopMatrix();

    // Antennae
    glColor3f(0.0f, 0.0f, 0.0f); // Set antennae color to yellow
    glBegin(GL_LINES);
    glVertex2f(0.1f, 0.0f);
    glVertex2f(0.2f, 0.1f);
    glVertex2f(0.1f, 0.0f);
    glVertex2f(0.2f, -0.1f);
    glEnd();
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

void drawText_size(int centerX, int centerY, char *str, int size)
{
    glColor3f(1.0, 1.0, 1.0);

    glRasterPos2i(centerX, centerY); // Position for Square 1 text
    const char *text1 = str;

    if (size == 18)
    {
        for (int i = 0; i < strlen(text1); i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
    }
    else if (size == 10)
    {
        for (int i = 0; i < strlen(text1); i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text1[i]);
    }
    else if (size == 15)
    {
        for (int i = 0; i < strlen(text1); i++)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text1[i]);
    }
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

void writeIntegerAtPosition(int number, float x, float y)
{
    glRasterPos2f(x, y);
    char str[10];
    sprintf(str, "%d", number);
    for (int i = 0; str[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
}

void writeFloatAtPosition(float number, float x, float y)
{
    glRasterPos2f(x, y);
    char str[10];
    sprintf(str, "%.2f", number);
    for (int i = 0; str[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
}

//--------------------------------------------------------------------

void drawString(float x, float y, const char *string)
{
    glRasterPos2f(x, y);
    int len = strlen(string);
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
}
//--------------------------------------------------------------------

void displayFloat(float number, float x, float y)
{
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%.2f", number);
    drawString(x, y, buffer);
}

//--------------------------------------------------------------------

void displayCircle(float centerX, float centerY, float radius)
{
    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0); // Translate to the specified center position

    glBegin(GL_LINE_LOOP);

    // Draw the circle
    int numSegments = 100;
    for (int i = 0; i < numSegments; i++)
    {
        float theta = 2.0f * PI * i / numSegments;
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x, y);
    }

    glEnd();
    glPopMatrix();
}

//--------------------------------------------------------------------
