#include<iostream>
#include<stdio.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/freeglut.h>
#include<math.h>
#include<cmath>
#include<time.h>
#include<vector>
#include<string>
#include"imageloader.h"


#include <irrKlang.h>
#if defined(WIN32)
#include <conio.h>
#else
#include "../common/conio.h"
#endif


#define WIDTH 1300
#define HEIGHT 700
#define RADIUS 15.0
#define PI 3.14
#define CAN_LEN 100.0
#define CAN_RADIUS 30.0
#define CAN_WID 30.0
#define PIS_LEN 85.0
#define WHITE 1.0,1.0,1.0
#define BLACK 0.0,0.0,0.0
#define RED 1.0,0.0,0.0
#define PURPLE 0.5f,0.0f,0.8f
#define GREEN 0.0f,0.75f,0.0f
#define SKY_BLUE 0.7f,0.9f,1.0f
#define ERROR 0.0001
#define DEMON_COLOR WHITE
#define TURTLE_LIMIT 5
#define ROT_UNIT 5
#define CANNON_X_UNIT 10
#define CANNON_Y_UNIT 10
#define CANNON_VEL_Y 50
#define SPRING_UNIT 5
#define TUR_RADIUS 10
#define VEL_ERROR 10
using namespace std;

void giveTexture();
GLuint loadTexture(Image* image);

void initShooting();
void removeTurtle(int i);
void removeBall(int i);
void init();
void manageTurtles();
void displayScoreboard();
void display(void);
void drawObstacles();
void drawCannon();
void drawPiston();
void initDemon();	
void drawCircle(float X , float Y,float r);
void updateDemon();
void drawDemon();
void drawBall(float X,float Y);

void giveTexture();
void ground(float& x,float &y,float &vx,float&vy,float &accX);
void mountainh(float& x,float &y,float &vx,float&vy,float &accX);
void mountainl(float& x,float &y,float &vx,float&vy,float &accX);
void ballTurtle();
void checkcollisions(float& x,float &y,float &vx,float&vy,float &accX);
void checkStopping(float& x,float &y,float &vx,float &vy,float &accX , bool& deleteMe, float& prex);
void keyboard( unsigned char key, int mouseX , int mouseY);
void playmusic();
void stopMusic();
void moveCannon();
void ballDemon();
bool checkDistanceCollision(float x1,float x2,float y1,float y2,float  distance);
void turtleCannon();
void gameover();

void adjustCamera();
void myOrtho(float X,float Y);










