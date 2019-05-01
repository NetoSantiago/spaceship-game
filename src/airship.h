#include<ctime>

class Airship{
	protected:
		bool isAlive;
		bool isEnemy;
		int radius;
		int timeToMove;
		int color;
		int x;
		int y;

	public:
		Airship();
		Airship(bool isEn);
		void moveRight();
		void moveLeft();
		void draw(int side);
		int getX();
		int getY();
		void die();
		int getRadius();
		bool getIsAlive();

};

Airship::Airship(){
	isAlive = true;
	isEnemy = false;
	radius = 4;
	timeToMove = 0;
	color = rand() % 3;
	x = 2;
	y = -38;
}

Airship::Airship(bool isEn){
	isAlive = true;
	isEnemy = isEn;
	timeToMove = 0;
	if(isEnemy == true){
		//isAlive = false;
		radius = 2;
		x=rand()%100 - 50;
		y = 40;
	} else {
		radius = 4;
		x = 0;
		y = -40;
	}
	color = rand() % 3;

}

void Airship::draw(int side){

	if(this->isEnemy){
		if(this->isAlive){
			if(this->timeToMove == 0)
				this->timeToMove = clock();
			if(clock() - this->timeToMove > 5000){
				if(side == 0){
					this->moveRight();
					//printf("%s\n", "Enemy should move right->>");
				} else {
					this->moveLeft();
					//printf("%s\n", "Enemy should move left->>");
				}
				//printf("%s", "enemy should move down\n");
				this->y--;
				this->timeToMove = clock();
			}
		}
	}

	//printf("%d %d\n", this->x, this->y);
	if(color == 0){
		glColor3f(1,0,0);
	}
	else if(color == 1){
		glColor3f(0,1,0);
	}
	else if(color == 2){
		glColor3f(0,0,1);
	}
	if(this->isEnemy == false){
		glBegin(GL_TRIANGLES);
			glVertex3f(this->x-4,this->y-4,0);
			glVertex3f(this->x+4,this->y-4,0);
			glVertex3f(this->x,this->y+4,0);
		glEnd();
	} else {
		glBegin(GL_TRIANGLES);
			glVertex3f(this->x-2,this->y,0);
			glVertex3f(this->x+2,this->y,0);
			glVertex3f(this->x,this->y-2,0);
		glEnd();
	}

	glutPostRedisplay();

}

void Airship::moveRight(void){
	//printf("%s\n", "entered moveRight");
	if(this->x <48)
		this->x += 2;
}

void Airship::moveLeft(void){
	//printf("%s\n", "entered moveLeft");
	if(this->x > -48)
		this->x-= 2;
}

int Airship::getX(){
	return this->x;
}

int Airship::getY(){
	return this->y;
}

bool Airship::getIsAlive(){
	return this->isAlive;
}

void Airship::die(){
	this->isAlive = false;
	this->x = -52;
	this->y = 42;
}

int Airship::getRadius(){
	return this->radius;
}
