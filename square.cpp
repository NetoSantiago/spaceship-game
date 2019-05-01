void square(float* p1, float* p2, float* p3, float* p4){
	glVertex3fv(p4); //P4
	glVertex3fv(p1); //P1
	glVertex3fv(p3); //P3

	glVertex3fv(p1); //P1
	glVertex3fv(p2); //P2
	glVertex3fv(p3); //P3
}

void square2(float* p1, float* p2, float* p3, float* p4){
  p1[1]++;
  p2[1]++;
  p3[1]++;
  p4[1]++;
	glVertex3fv(p4); //P4
	glVertex3fv(p1); //P1
	glVertex3fv(p3); //P3

	glVertex3fv(p1); //P1
	glVertex3fv(p2); //P2
	glVertex3fv(p3); //P3
}

void square3(float* p1, float* p2, float* p3, float* p4){
  p1[1]-=2;
  p2[1]-=2;
  p3[1]-=2;
  p4[1]-=2;
	glVertex3fv(p4); //P4
	glVertex3fv(p1); //P1
	glVertex3fv(p3); //P3

	glVertex3fv(p1); //P1
	glVertex3fv(p2); //P2
	glVertex3fv(p3); //P3
}
