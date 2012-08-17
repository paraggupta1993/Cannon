#include"cannon.h"

char playerName[52];
char playerHigh[52];
int score; 
float slopeX,slopeY;
float m;
float r = 1;
float rot_angle;
float springK , ballMass , gravity,springX;

float canX1,canX2, canY1, canY2,canX3,canY3,canX4,canY4;
float cannonBaseX , cannonBaseY , cannonVelY;

float t,accY;
bool released;
float ex,ey,ew;
float ut = 1.0/10;
bool jumped = false;

int turtle_limit,turtle_period;
int level,lives;
float zoom;

float demonX,demonY,demonVelX;
float demonLimitX1 , demonLimitX2;
float demonRadius;

bool cannonCamera;
bool curBallCamera;

GLuint _textureId; //The id of the teaxture
GLuint demonTexture; //The id of the teaxture

#include"turtle.h"
vector <turtle*> tur;
#include"ball.h"
vector <Ball*> balls;
Ball* curBall;
int hs;
FILE *fd;
#include"cannonFunc.h"
#include"faltu.h"
void removeTurtle(int i){
	delete tur[i];
	tur.erase(tur.begin()+i);
}
void removeBall(int i){
	delete balls[i];
	balls.erase(balls.begin()+i);
}

void init(){
	canX1 = 0.0;
	canY1 = CAN_WID/2;
	canX2 = CAN_LEN;
	canY2 = CAN_WID/2;
	canX3 = 0.0;
	canY3 = -(CAN_WID/2);
	canX4 = CAN_LEN;
	canY4 = -(CAN_WID/2);
	rot_angle = 45;
	springK = 4.0;
	ballMass = 1.0;
	gravity = 10.0;
	released = false;

	zoom = 0.0;
	lives = 3;
	score=0;
	t = 0.0;
	accY = -10.0;
	ey = 0.8;
	ex = 1;
	ew = 1;
	released = false;
	jumped = false ;
	turtle_limit=3;
	level = 1;
	cannonCamera = true;
	curBallCamera = false;
	turtle_period = 100.0;

	// setting up background color
	glClearColor( SKY_BLUE , 1.f);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	//gluOrtho2D( 0.0 ,1300.0,0.0,700.0);
	gluOrtho2D(0.0,1600,0.0,900);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	Image* image = loadBMP("../images/mr.bmp");
	_textureId = loadTexture(image);
	delete image;

	image = loadBMP("../images/my.bmp");
	demonTexture = loadTexture(image);
	delete image;

	curBall = new Ball();
	initDemon();
	cannonBaseX = 100;
	cannonBaseY = 45;
}
void manageTurtles(){
	t++;
	if(tur.size() < turtle_limit){
		if((int)t%(int)turtle_period==0){
			turtle* temp = new turtle();
			tur.push_back(temp);
		}
	}
	for(int i=0;i<tur.size();i++){
		tur[i]->updateTurtle();
		tur[i]->drawTurtle();
		if(tur[i]->stoped()){
			removeTurtle(i);
		}
	}
}
void displayScoreboard(){
	char sc[100];
	sprintf(sc,"Score:%d Lives:%d Level:%d",score,lives,level);
	glRasterPos3d(100,810 ,0.0);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(unsigned char*)sc );
	sprintf(sc,"HighScore:%d (%s)",hs,playerHigh);
	glRasterPos3d(100,770 ,0.0);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(unsigned char*)sc );
}
void myOrtho(float X,float Y){
		float x1,x2,y1,y2;
		float width = 1600.0 - zoom;
		float height = (width*9.0)/16.0;
		x1 = X - width/2.0;
		x2 = X + width/2.0;
		y1 = Y - height/2.0;
		y2 = Y + height/2.0;
		float fx1 , fx2, fy1,fy2;
		if(x1<0){
			fx1 = 0.0;
			fx2 = width;
		}
		else if(x2>1600.0){
			fx1 = 1600.0-width;
			fx2 = 1600.0;
		}
		else{
			fx1 = X - (width/2.0);
			fx2 = X + (width/2.0);
		}
		if(y1<0){
			fy1 = 0.0;
			fy2 = height;
		}
		else if(y2>900.0){
			fy1 = 900.0-height;
			fy2 = 900.0;
		}
		else{
			fy1 = Y - (height/2.0);
			fy2 = Y + (height/2.0);
		}
		gluOrtho2D(fx1,fx2,fy1,fy2);
}
void adjustCamera(){
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	if(curBallCamera){
		if( balls.size() <=0 ){
			myOrtho(cannonBaseX , cannonBaseY);
		}
		else{
			myOrtho( balls[balls.size()-1]->ballX ,balls[balls.size()-1]->ballY);
		}
	}
	else if(cannonCamera){
		myOrtho(cannonBaseX , cannonBaseY);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void display(void){



	adjustCamera();
	glClear(GL_COLOR_BUFFER_BIT);
	giveTexture();
	glPushMatrix();
	glTranslatef(demonX,demonY,0);
	giveTextureDemon();
	glPopMatrix();


	glPushMatrix();
	{
		//translating to the left-bottom corner of our boundary
		if(jumped){
			moveCannon();
		}
		glTranslatef(cannonBaseX ,cannonBaseY,0);
		glColor3f(BLACK);
		drawObstacles();
		//tranlating to the cannon's bottom
		glRotatef(rot_angle , 0 , 0 , 1);
		drawCannon();
		drawPiston();
		//draw Cannon Ball
		curBall->drawUnreleased();
	}
	glPopMatrix();
	displayScoreboard();
	updateDemon();
	//drawDemon();
	manageTurtles();

	//for every released ball...
	for(int i=0;i<balls.size();i++){
		balls[i]->drawReleased();
		//cout << balls[i]->ballX << " " << balls[i]->ballY << " " << balls[i]->ballVelX << " " << balls[i]->ballVelY << endl;
		if(balls[i]->stoped()){
			removeBall(i);
		}
	}
	ballTurtle();
	ballDemon();
	turtleCannon();
	glFlush();
	glutSwapBuffers();
}
void update (int value){
	glutPostRedisplay();
	glutTimerFunc(25,update,0);
}

int main(int argc , char** argv){
	srand(time(NULL));
	printf("\n\nEnter Player Name:");
	scanf("%s",playerName);
	scoreFile();

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE );
	glutInitWindowSize( WIDTH , HEIGHT );
	glutInitWindowPosition(0,0);
	glutCreateWindow("First Window");
	
	init();
	glutDisplayFunc(display);
	//glutIdleFunc(display);
	glutTimerFunc(25, update , 0);
	glutKeyboardFunc(keyboard);

	glutMouseFunc(mouseClick);
	glutMotionFunc(mousePressed);
	//glutPassiveMotionFunc(mousePassiveMotion);
	playmusic();
	glutMainLoop();
}
