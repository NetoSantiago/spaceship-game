class Bullet{
	protected:
		bool isAlive;
		bool isEnemy;
		int radius;
		int timeToMove;
		int x;
		int y;

	public:
		Bullet();
		Bullet(int x, int y, bool isEn, bool isAlive);
    int getX();
    int getY();
    bool getIsAlive();
		void die();
		int getRadius();
		void draw();
};

Bullet::Bullet(){
  this->isAlive = false;
  this->isEnemy = false;
  this->timeToMove = 100;
	this->radius = 2;
  this->x = 0;
  this->y = 0;
}

Bullet::Bullet(int x, int y, bool isEn, bool isAlive){
  this->isAlive = isAlive;
  this->isEnemy = isEn;
	this->radius = 2;
  this->timeToMove = 100;
  this->x = x;
  this->y = y+1;
}

void Bullet::draw(){
  if(this->y > 40)
    this->isAlive = false;
	if(this->isAlive){
	  if(this->timeToMove == 100){
	    this->timeToMove = clock();
	    //printf("%s", "Bullet received CLOCK\n\n");
	  }
	  if(clock() - this->timeToMove > 300){
	    //printf("%s", "bullet should move UP\n\n");
	    this->y++;
	    this->timeToMove = clock();
	  }
	  float p1[] = {(float)this->x, (float)this->y, 0.0};
	  float p2[] = {(float)this->x+1, (float)this->y, 0.0};
	  float p3[] = {(float)this->x+1, (float)this->y+1, 0.0};
	  float p4[] = {(float)this->x, (float)this->y+1, 0.0};
	  glColor3f(0,0,0);
	  glBegin(GL_TRIANGLES);
	    square(p1,p2,p3,p4);
	  glEnd();

	  glBegin(GL_TRIANGLES);
	    square2(p1,p2,p3,p4);
	  glEnd();

	  glBegin(GL_TRIANGLES);
	    square3(p1,p2,p3,p4);
	  glEnd();

		glutPostRedisplay();
	}
}

int Bullet::getX(){
  return this->x;
}

int Bullet::getY(){
  return this->y;
}

int Bullet::getRadius(){
  return this->radius;
}

bool Bullet::getIsAlive(){
  return this->isAlive;
}

void Bullet::die(){
	this->isAlive = false;
}
