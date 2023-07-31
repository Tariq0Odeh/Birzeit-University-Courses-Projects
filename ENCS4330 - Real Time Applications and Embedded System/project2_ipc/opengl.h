#include "local.h"

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

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

void display() {

	// Set every pixel in the frame buffer to the current clear color.
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	LineInTheMiddle();
	LineHorizontal();

  	glutPostRedisplay();
    glutSwapBuffers();


}

void timer(int t){
	glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);
   
}

void init(){
	glClearColor(1.0,1.0,1.0,1.0);
}

void startOpenGl(){

  init();
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowPosition(250, 250);
  glutInitWindowSize(600, 400);
  glutCreateWindow("Second Project");
  glutDisplayFunc(display);

  glutTimerFunc(0, timer, 0);

  init();

  glutMainLoop();
}

