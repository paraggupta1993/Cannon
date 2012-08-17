void scoreFile(){
	fd = fopen("high.txt","r");
	if(fd!=NULL){
		fscanf(fd,"%s %d",playerHigh,&hs);
		fclose(fd);
	}
	else{
		hs=-1;
	}
}
void mousePressed(int x,int y){
	if( springX < PIS_LEN){
			springX+= 1;
	}
	float my = 900.0-y;
	float mx = x;
	rot_angle = (atan((my-cannonBaseY)/(mx-cannonBaseX))*180.0)/PI;
	if(rot_angle<0) rot_angle+=180.0;
}
void mouseClick(int button,int state,int x, int y){
	if(button == GLUT_LEFT_BUTTON && state==GLUT_UP){
		curBall->initShooting();
		balls.push_back(curBall);
		curBall = new Ball();
	}
	
}
/*
void mousePassiveMotion(int x, int y){
	rot_angle = atan(((900-y)-cannonBaseY)/((x)-cannonBaseX))*180/PI;
	if(rot_angle<0) rot_angle =0;

}*/
void keyboard( unsigned char key, int mouseX , int mouseY){
	if( key == 27){
		exit(0);
	}
	if( key == 'r'){
		if(rot_angle< 180 && rot_angle>=0)
			rot_angle+= ROT_UNIT;
	}
	if( key =='t'){
		if(rot_angle<= 180 && rot_angle>0)
			rot_angle-= ROT_UNIT;
	}
	if(key =='l'){
		if(cannonBaseX <  882.0 - (CAN_RADIUS + CAN_LEN)){
			cannonBaseX+=CANNON_X_UNIT;
		}
	}
	if(key == 'j'){
		if( cannonBaseX > CAN_RADIUS){
			cannonBaseX-=CANNON_X_UNIT;
		}
	}
	if(!jumped && key == 'i'){
		cannonVelY = CANNON_VEL_Y;
		jumped = true;
	}

	if( !released && key =='d'){
		if( springX < PIS_LEN){
			springX+= SPRING_UNIT;
		}
	}
	if(!released && key == 's'){ //shoot
		curBall->initShooting();
		balls.push_back(curBall);
		curBall = new Ball();
	}
	if(key == 'z'){
		if(zoom<1000){
			zoom += 200.0;
		}
	}
	if(key == 'x'){
		if(zoom>=200){
			zoom -= 200.0;
		}
	}
	if(key == 'c'){
		if(cannonCamera){
			cannonCamera = false;
			curBallCamera = true;
		}
		else{
			cannonCamera = true;
			curBallCamera = false;
		}
	}
}
using namespace irrklang;
ISoundEngine* engine = createIrrKlangDevice();
using namespace std;
void playmusic(){
	using namespace irrklang;

	if (!engine)
	{
		printf("Could not startup engine\n");
		exit(0);
	}
	// To play a sound, we only to call play2D(). The second parameter
	// tells the engine to play it looped.
	// play some sound stream, looped
	engine->play2D("../sounds/mario.mp3", true);

	// In a loop, wait until user presses 'q' to exit or another key to
	// play another sound.
	using namespace std;
}
void stopMusic(){
	using namespace irrklang;
	engine->drop(); // delete engine
	using namespace std;
}
void moveCannon(){
	float dt = ut/2.0;
	cannonVelY = cannonVelY + accY*dt;
	cannonBaseY = cannonBaseY + cannonVelY*dt + accY*dt*dt;	

	if(cannonBaseY < 45){
		cannonBaseY = 45;
		jumped = false;
	}
}



