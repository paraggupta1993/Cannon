class turtle 
{
	public :
	float x,y;
	float vx,vy;
	float accX;
	float radius;
	bool deleteMe;
	turtle(){
		x=demonX;
		y=demonY;
		vy= -(rand()%10);
		vx= (rand()%100)-50;
		radius= 10+rand()%15;
		accX = 0.0;
		deleteMe = false;
	}
	void drawTurtle(){
		glColor3f(PURPLE);
		drawCircle(x,y,radius);
		glColor3f(BLACK);
	}
	bool stoped(){
		if(x < 0 || deleteMe || x>1600) return true;
		return false;
	}
	void updateTurtle(){

		float prey = y;
		float prex = x;

		x = x + vx*ut;
		vy = vy + accY*ut;
		y = y + (vy*ut + (accY*ut*ut)/2);
		
		//ground collision
		checkcollisions(x,y,vx,vy,accX);
		checkStopping(x,y,vx,vy,accX,deleteMe,prex);
	}
};


