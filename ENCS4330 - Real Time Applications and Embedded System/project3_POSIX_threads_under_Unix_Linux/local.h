#ifndef __LOCAL_H_
#define __LOCAL_H_

#include <sys/signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <X11/Xlib.h>
#include <pthread.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"      /*Red*/
#define GREEN   "\033[32m"      /*Green*/
#define BLUE "\033[34m" 	/*Blue*/
#define YELLOW "\033[33m"	/*Yellow*/
#define PI 3.1415926535898
#define LINE_MAX_LENGTH 1000
#define MAX_SIZE 100 // Maximum size of the array

typedef struct
{
    float posX;  	// X position of the square
    float posY;  	// Y position of the square
    float speed; 	// The speed for ants
    int angle;   	// The direction that will move to it at the began
    int strong_pheromone;  //If the ant released strong pheromone
    int weak_pheromone;    //If the ant released weak pheromone
    int closestFood;     //The closest Food to the ant
} Ant;

typedef struct{
    float posX;  	// X position of the food
    float posY;  	// Y position of the food
    float quantity; 	// It will start with quantity = 1. Full portions
    pthread_mutex_t food_mutex[MAX_SIZE];  //The mutex on food
} Food;

#endif
