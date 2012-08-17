#include"cannon.h"
 
float slopeX,slopeY;
float m;
float r = 1;
float rot_angle;
float springK , ballMass , gravity,springX;
float cenX , cenY;
float cenVX , cenVY;

float canX1,canX2, canY1, canY2,canX3,canY3,canX4,canY4;
float cannonBaseX , cannonBaseY , cannonVelY;

float t,accX,accY;
float ballX,ballY,ballVelY,ballVelX,ballVel;
bool released;
float ex,ey,ew;
float ut = 1.0/10;
bool jumped = false;


float demonX,demonY,demonVelX;
float demonLimitX1 , demonLimitX2;
float demonRadius;

GLuint _textureId; //The id of the teaxture

void initShooting();
#include"cannonFunc.h"
#include"faltu.h"
#include"turtle.h"
vector <turtle*> tur;
void removeTurtle(int i){
	delete tur[i];
	tur.erase(tur.begin()+i);
}

void initShooting(){
	released = true;
	ballVel = springX* sqrt(springK / ballMass);
	cenVX = ballVel* cos(rot_angle*PI/180);
	cenVY = ballVel* sin(rot_angle*PI/180);
	ballX = cenX*cos(rot_angle*PI/180)+ cannonBaseX ;
	ballY = cenX*sin(rot_angle*PI/180)+ cannonBaseY;
	ballVelY = cenVY;
	ballVelX = cenVX;
}
void reinstall(){
 	springX = 0;
	released = false;
}

void init(){
	t = 0.0;
	accY = -10.0;
	ey = 0.4;
	ex = 1;
	ew = 1;
	accX = 0.0;
	released = false;
	jumped = false ;
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
	initDemon();
	cannonBaseX = 100;
	cannonBaseY = 45;
}
void manageTurtles(){
	t++;
	if(tur.size() < TURTLE_LIMIT){
		if((int)t%100==0){
		 turtle* temp = new turtle();
	 	tur.push_back(temp);
		}
	}
	for(int i=0;i<tur.size();i++){
	   	tur[i]->updateTurtle();
	  	 tur[i]->drawTurtle();
		 if(tur[i]->getX() < 0 ){
		   removeTurtle(i);
		 }
	}
}
void display(void){
	
	glClear(GL_COLOR_BUFFER_BIT);
	giveTexture();
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
		if(!released){
			cenX = RADIUS + PIS_LEN - springX;
			cenY = 0.0;
			glColor3f(BLACK);
			drawBall(cenX,cenY);
		}
	}
	glPopMatrix();
	updateDemon();
	drawDemon();
	manageTurtles();

	if(released){
		//move the center of the ballz
		//cout << ballX << " " << ballY << " " << ballVelX << " " << ballVelY << endl;

		//ground friction
		if(ballVelX  > 0) accX = -abs(accX);
		else if(ballVelX < 0) accX = abs(accX);
		else accX = 0;
		//cout << accX << endl;
		
		float preballY = ballY;
		float preballX = ballX;

		ballVelX = ballVelX + accX*ut;
		ballX = ballX + ballVelX*ut ;

		ballVelY = ballVelY + accY*ut;
		ballY = ballY + (ballVelY*ut + (accY*ut*ut)/2);

		if(ballY <= 45){
			ballVelY = (-ey)*ballVelY;
			ballY = 45; 
			accX = 5.0;
		}
		else{	
			accX = 0.0;
		}
		if(ballY == 45 && abs(preballX-ballX) < 0.1 && (ballVelY-0.4444)<ERROR ){
			reinstall();
		}
		
		


		/*
		//touching the wall

		if( ballX+(cenX*cos(rot_angle*PI/180.0)) + RADIUS > 1000){
		ballVelX = -(ew)*ballVelX;
		}*/
		/*
		   if(abs(orgballX - orgballY -700.0)/sqrt(2.0) < RADIUS ){
		   float temp = ballVelY;
		   ballVelY = ballVelX;
		   ballVelX = temp;
		   }*/



		//Drawing ball and trannslating to the center of ball
		glColor3f(BLACK);
		drawBall(ballX,ballY);
	}
	glFlush();
	glutSwapBuffers();
}

int main(int argc , char** argv){

	canX1 = 0.0;
	canY1 = CAN_WID/2;
	canX2 = CAN_LEN;
	canY2 = CAN_WID/2;
	canX3 = 0.0;
	canY3 = -(CAN_WID/2);
	canX4 = CAN_LEN;
	canY4 = -(CAN_WID/2);
	rot_angle = 45;
	springK = 2.0;
	ballMass = 1.0;
	gravity = 10.0;
	released = false;
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE );
	glutInitWindowSize( WIDTH , HEIGHT );
	glutInitWindowPosition(0,0);
	glutCreateWindow("First Window");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);
	playmusic();
	glutMainLoop();
}
