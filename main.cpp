#include <GL/glut.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <string.h>
#include "matrix.h"
#include "airship.h"
#include "square.cpp"
#include "bullet.h"

#define X 0
#define Y 1
#define Z 2
#define MAX_ENEMIES 10
#define MAX_BULLETS 3

int bulletsAlive = 0;
int enemiesAlive = 0;
int isRunning = 1;

Airship sceneVector[1 + MAX_ENEMIES];
Bullet bulletVector[MAX_BULLETS];
float rotate_x = 0;
float rotate_y = 0;
int r,g,b;

void initGL();
void keyboard(int key, int x, int y);
void display();
void makeEnemies(int numEnemies);
void makeEnemy();
void idle();
void checkBulletsAlive();
void checkCollisions();
void drawText(char* string, int posX, int posY);
void mouse(int button, int state, int x, int y);
void createMenu();
void difficult(int op);
void mainMenu(int op);
void play_pause(int op);

int main(int argc,char** argv){
	srand((unsigned)time(NULL));
	Airship airship(false);
	sceneVector[0] = airship;
	makeEnemies(MAX_ENEMIES);

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(300,150);
	glutCreateWindow("Game");
	initGL();
	glutMouseFunc(mouse);
	glutSpecialFunc(keyboard);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}

void idle(){
	// int side = rand()%2;
	// for(int i = 1; i <= MAX_ENEMIES; i++){
	// 	sceneVector[i].draw(side);
	// }
	// for(int j = 0; j < MAX_BULLETS; j++){
	// 	bulletVector[j].draw();
	// }
	checkCollisions();
	makeEnemy();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	printf("%d", sceneVector[0].getIsAlive());
	if(isRunning == 1){
		if(sceneVector[0].getIsAlive()){
			drawText((char*)"GAME RUNNING", -47, 37);
			glLoadIdentity();

			for(int i = 0; i <=  MAX_ENEMIES; i++){
				int side = rand()%2;
				sceneVector[i].draw(side);
			}
			for(int j = 0; j < MAX_BULLETS; j++){
				bulletVector[j].draw();
			}
		} else {
			drawText((char*)"GAME PAUSED", -47, 37);
			drawText((char*)"GAME OVER", -10, 0);
		}

	} else {
		drawText((char*)"GAME PAUSED", -47, 37);
		drawText((char*)"GAME PAUSED", -10, 0);
	}

	glutPostRedisplay();
	glutSwapBuffers();

}

void keyboard(int key, int x, int y){

    //printf("key code: %d\n", key);
    switch(key){
    	case GLUT_KEY_LEFT:
				//printf("%s\n","Should move left");
				sceneVector[0].moveLeft();
				break;
			case GLUT_KEY_RIGHT:
				//printf("%s\n","Should move right");
				sceneVector[0].moveRight();
				break;
			case GLUT_KEY_UP:
				checkBulletsAlive();
				if(bulletsAlive < MAX_BULLETS){
					for(int i = 0; i < MAX_BULLETS; i++){
						if(!bulletVector[i].getIsAlive()){
							bulletVector[i] = Bullet(sceneVector[0].getX(), sceneVector[0].getY(), false, true);
							bulletsAlive++;
							break;
						}
					}
				}
				break;

			default:
			//printf("%s", "No key pressed");
			break;
    }
    glutPostRedisplay();
}

void initGL(){
	glClearColor(1.0,1.0,1.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50,50,-40,40,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void makeEnemies(int numEnemies){
	for(int i = 1; i <= numEnemies; i++){
		sceneVector[i] = Airship(true);
		printf("killing airship\n\n");
		sceneVector[i].die();
		enemiesAlive = 0;
	}
}

void checkBulletsAlive(){
	int cont = 0;
	for(int i = 0; i < MAX_BULLETS; i++){
		if(bulletVector[i].getIsAlive())
			cont += 1;
	}
	bulletsAlive = cont;
}

void checkCollisions(){
	for(int i = 1; i < 1+MAX_ENEMIES; i++){// The +1 is because you need to count the friendly spaceship;
		if(sceneVector[0].getIsAlive()){
			if(sqrt(pow(sceneVector[0].getX() - sceneVector[i].getX(), 2) + pow(sceneVector[0].getY() - sceneVector[i].getY(), 2))<sceneVector[0].getRadius()+sceneVector[i].getRadius()){
					sceneVector[0].die();
					createMenu();
					glutPostRedisplay();
			}
		}
	}
	for(int i = 0; i < MAX_BULLETS; i++){
		if(bulletVector[i].getIsAlive()){
			for(int j = 1; j < 1+MAX_ENEMIES; j++){
				if(sceneVector[j].getIsAlive()){
					if(sqrt(pow(bulletVector[i].getX() - sceneVector[j].getX(), 2) + pow(bulletVector[i].getY() - sceneVector[j].getY(), 2)) < bulletVector[i].getRadius()+sceneVector[j].getRadius()){
						sceneVector[j].die();
						bulletVector[i].die();
						enemiesAlive--;
					}
				}
			}
		}
	}
}

void makeEnemy(){
	if(enemiesAlive < MAX_ENEMIES){
		if(rand()%100 < 1){
			for(int i = 1; i < 1+MAX_ENEMIES; i++){
				if(!sceneVector[i].getIsAlive()){
					sceneVector[i] = Airship(true);
					enemiesAlive++;
					break;
				}
			}
		}
	}
}

void drawText(char* string, int posX, int posY){
	glPushMatrix();
  	// Posição no universo onde o texto será colocado
    glRasterPos2f(posX,posY);
    // Exibe caracter a caracter
    while(*string)
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*string++);
	glPopMatrix();
}

void createMenu(){
    int menu,submenu1, submenu2;

    submenu1 = glutCreateMenu(difficult);
    glutAddMenuEntry("easy",0);
    glutAddMenuEntry("medium",1);
    glutAddMenuEntry("hard",2);

		submenu2 = glutCreateMenu(play_pause);
		glutAddMenuEntry("play",0);
		glutAddMenuEntry("pause",1);


    menu = glutCreateMenu(mainMenu);
    glutAddSubMenu("difficult",submenu1);
		glutAddSubMenu("play/pause",submenu2);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON)
         if (state == GLUT_DOWN){
            isRunning = 0;
						createMenu();
					}

    glutPostRedisplay();
}

void difficult(int op)
{
   switch(op) {
            case 0:
                     printf("easy\n");
                     break;
            case 1:
                     printf("medium\n");
                     break;
            case 2:
                     printf("hard\n");
                     break;
    }
    glutPostRedisplay();
}

void mainMenu(int op){

}

void play_pause(int op){

	if(sceneVector[0].getIsAlive()){
		switch(op) {
				case 0:
					isRunning = 1;
					break;
				case 1:
					isRunning = 0;
					break;
		}
	} else {
			switch(op){
					case 0:
						makeEnemies(MAX_ENEMIES);
						sceneVector[0] = Airship(false);
						isRunning = 1;
						break;
					case 1:
						isRunning = 0;
						break;
			}
	}


	 glutPostRedisplay();
}
