#include"cannon.h"

void drawObstacles(){

	/*
	   glBegin(GL_LINES);
	   glVertex2f(-100,0);
	   glVertex2f(1200,0);
	   glEnd();
	//drawing walls 
	glColor3f(BLACK);
	glBegin(GL_LINES);
	glVertex2f(1000,0);
	glVertex2f(1000,700);
	glVertex2f(700,0);
	glVertex2f(1000,300);
	glEnd();*/
}

void drawCannon(){
	glBegin(GL_LINES);
	glVertex2f(canX1,canY1);
	glVertex2f(canX2,canY2);
	glVertex2f(canX3,canY3);
	glVertex2f(canX4,canY4);
	glVertex2f(canX1,canY1);
	glVertex2f(canX3,canY3);
	glEnd();
	glColor3f(RED);
	drawCircle(0,0,CAN_RADIUS);
	glColor3f(WHITE);
}
void drawPiston(){
	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f( PIS_LEN - springX , 0 );
	glVertex2f( PIS_LEN-springX , -(CAN_WID/2));
	glVertex2f( PIS_LEN-springX , (CAN_WID/2) );
	glEnd();
}
void initDemon(){	
	demonX = 500.0;
	demonY = 720.0;
	demonLimitX1 = 200.0;
	demonLimitX2 = 1200.0;
	demonVelX = 40.0;
	demonRadius = 30.0;
}

void drawCircle(float X , float Y,float r){
	glPushMatrix();
	{
		glTranslatef(X,Y,0);
		//drawing ball
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f( 0 , 0 , 0.0);
		for(int j=0;j<380;j+=5){
			glVertex2f( r*cos((j*PI)/180.0), r*sin((j*PI)/180.0) );
		}
		glEnd();
	}
	glPopMatrix();
}
void updateDemon(){
	demonX += demonVelX * ut;
	if(demonX >= demonLimitX2) demonVelX = -(abs(demonVelX));
	if(demonX <= demonLimitX1) demonVelX = abs(demonVelX);
}
void drawDemon(){
	drawCircle(demonX , demonY, demonRadius);
}
void drawBall(float X,float Y){
	drawCircle(X , Y ,RADIUS);
}
void giveTexture(){
	glColor3f(WHITE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f,0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1600.0f,0.0f,0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1600.0f, 900.0f,0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f,900.0f, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void giveTextureDemon(){
	glColor3f(WHITE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, demonTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	float temp = demonRadius;
	//cout << temp << endl;
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-temp,-temp,0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(temp,-temp,0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(temp,temp,0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-temp,temp, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void ground(float& x,float &y,float &vx,float&vy,float &accX){
	if(y <= 45){
		vy = (-ey)*vy;
		y = 45; 
		vx = vx*0.95;
	}
}

void mountainh(float& x,float &y,float &vx,float&vy,float &accX){
	//left wall
	if((y>=900-752 && y<=900-662) && (x>=1000 && x<=1000+VEL_ERROR)){
		x = 1000;
		vx = -vx;
	}
	//horizontal
	if( (x>=1000 && x<=1215) && (y<=900-662 && y>=900-662-VEL_ERROR)){
		vy = (-ey)*vy;
		y = 900-662;
		vx = vx*0.95;
	}
	//right wall
	if((y>=900-752 && y<=900-662) && (x<=1215 && x>=1215 - VEL_ERROR)){
		x = 1215;
		vx = -vx;
	}

}
void mountainl(float& x,float &y,float &vx,float&vy,float &accX){
	//horizontal
	if(((x>=883 && x<=1000)||(x>=1215 && x<=1250)) && (y<=900-752 && y>=900-752-VEL_ERROR)){
		vy = (-ey)*vy;
		y = 900-752;
		vx = vx*0.95;
	}
	//left 
	if((y>=45 && y<=900-752) && (x>=883 && x<=883+VEL_ERROR)){
		x = 883;
		vx = -vx;
	}
	//right
	if((y>=45 && y<=900-752) && (x<=1250 && x>=1250-VEL_ERROR)){
		x = 1250;
		vx = -vx;
	}

}
void ballTurtle(){
	for(int i = 0; i<balls.size();i++){
		for(int j=0;j<tur.size();j++){
			if((balls[i]->ballX-tur[j]->x)*(balls[i]->ballX-tur[j]->x) + (balls[i]->ballY - tur[j]->y)*(balls[i]->ballY - tur[j]->y) <= (RADIUS + tur[j]->radius)*(RADIUS + tur[j]->radius)){
				if( RADIUS>tur[j]->radius){
					score++;
					removeTurtle(j);
				}
				else if(RADIUS < tur[j]->radius){
					removeBall(i);
					score--;
				}
				else {
					removeBall(i);
					removeTurtle(j);
				}
			}
		}
	}
}
void ballDemon(){
	for(int i = 0; i<balls.size();i++){
		if((balls[i]->ballX-demonX)*(balls[i]->ballX-demonX) + (balls[i]->ballY - demonY)*(balls[i]->ballY - demonY) <= (RADIUS + demonRadius)*(RADIUS + demonRadius)){
			score+=10;
			level++;
			turtle_limit+=2;
			turtle_period -= 5;
			initDemon();
			removeBall(i);
		}
	}
}
void gameover(){
	
 char sc[100];
 sprintf(sc,"GAME OVER !!!",score,lives,level);
 glRasterPos3d(700,400 ,0.0);
 int temp=0;
 	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(unsigned char*)sc );

 if(hs==-1 || (score>hs)){
 	fd = fopen("high.txt","w");
	fprintf(fd,"%s %d",playerName, score);
	fclose(fd);
 }
 
 printf("\n\nYour Score is %d\n",score);
 exit(0);
}
void turtleCannon(){
	for(int i =0; i<tur.size();i++){
		if(checkDistanceCollision(cannonBaseX , tur[i]->x , cannonBaseY , tur[i]->y, tur[i]->radius + CAN_RADIUS)){
			lives--;
			if(lives==-1){
			   gameover();
			}
			removeTurtle(i);
		}
	}
}
bool checkDistanceCollision(float x1,float x2,float y1,float y2,float  distance){
	if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<= distance*distance){
		return true;
	}
	return false;

}
void checkcollisions(float& x,float &y,float &vx,float&vy,float &accX){
	ground(x,y,vx,vy,accX);
	mountainl(x,y,vx,vy,accX);
	mountainh(x,y,vx,vy,accX);
}
void checkStopping(float& x,float &y,float &vx,float &vy,float &accX , bool& deleteMe, float& prex){
	if( (y == 45||y==900-662||y==900-752) && abs(vx)<0.5 && abs(vy)<0.5) {
		deleteMe = true;
	}
	
	if( x < 0|| x > 1600){
	 	deleteMe = true;
	}
}


