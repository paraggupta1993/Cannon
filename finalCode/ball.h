class Ball
{
	public:

	float cenX , cenY;
	float cenVX , cenVY;
	float ballX,ballY,ballVelY,ballVelX,ballVel;
	float accX;
	bool deleteMe;
	Ball(){
		accX = 0.0;
		deleteMe = false;
		cenX = RADIUS + PIS_LEN - springX;
		cenY = 0.0;
		
	}	
	void drawUnreleased(){
		cenX = RADIUS + PIS_LEN - springX;
		cenY = 0.0;
		
		glColor3f(BLACK);
		drawBall(cenX,cenY);
	}

	void initShooting(){
		ballVel = springX* sqrt(springK / ballMass);
		cenVX = ballVel* cos(rot_angle*PI/180);
		cenVY = ballVel* sin(rot_angle*PI/180);
		ballX = cenX*cos(rot_angle*PI/180)+ cannonBaseX ;
		ballY = cenX*sin(rot_angle*PI/180)+ cannonBaseY;
		ballVelY = cenVY;
		ballVelX = cenVX;

		springX = 0;
	}

	void drawReleased(){

		float preballY = ballY;
		float preballX = ballX;

		ballX = ballX + ballVelX*ut;
		ballVelY = ballVelY + accY*ut;
		ballY = ballY + (ballVelY*ut + (accY*ut*ut)/2);

		checkcollisions(ballX,ballY,ballVelX,ballVelY,accX);
		checkStopping(ballX , ballY , ballVelX, ballVelY , accX , deleteMe,preballX);

		glColor3f(BLACK);
		drawBall(ballX,ballY);
	}
	bool stoped(){
	  return deleteMe;
	}
};
