#include <math.h>
#include <GL\freeglut.h>
#include "Cubo.h"
#include "Triangle.h"

#include <iostream>		  // for "cout <<"
using namespace std;

Cubo::Cubo()
{
}

void Cubo::setValores(float aresta)
{
	a = aresta;

	//Triangulo f1
	tri[0][0] = -a / 2; tri[0][1] = a / 2; tri[0][2] = a / 2;
	tri[1][0] = a / 2; tri[1][1] = a / 2; tri[1][2] = a / 2;
	tri[2][0] = -a / 2; tri[2][1] = -a / 2; tri[2][2] = a / 2;
	//Triangulo f2
	tri[3][0] = a / 2; tri[3][1] = a / 2; tri[3][2] = a / 2;
	tri[4][0] = a / 2; tri[4][1] = -a / 2; tri[4][2] = a / 2;
	tri[5][0] = -a / 2; tri[5][1] = -a / 2; tri[5][2] = a / 2;
	//Triangulo d1
	tri[6][0] = a / 2; tri[6][1] = a / 2; tri[6][2] = a / 2;
	tri[7][0] = a / 2; tri[7][1] = a / 2; tri[7][2] = -a / 2;
	tri[8][0] = a / 2; tri[8][1] = -a / 2; tri[8][2] = a / 2;
	//Triangulo d2
	tri[9][0] = a / 2; tri[9][1] = a / 2; tri[9][2] = -a / 2;
	tri[10][0] = a / 2; tri[10][1] = -a / 2; tri[10][2] = -a / 2;
	tri[11][0] = a / 2; tri[11][1] = -a / 2; tri[11][2] = a / 2;
	//Triangulo t1
	tri[12][0] = a / 2; tri[12][1] = a / 2; tri[12][2] = -a / 2;
	tri[13][0] = -a / 2; tri[13][1] = a / 2; tri[13][2] = -a / 2;
	tri[14][0] = a / 2; tri[14][1] = -a / 2; tri[14][2] = -a / 2;
	//Triangulo t2
	tri[15][0] = -a / 2; tri[15][1] = a / 2; tri[15][2] = -a / 2;
	tri[16][0] = -a / 2; tri[16][1] = -a / 2; tri[16][2] = -a / 2;
	tri[17][0] = a / 2; tri[17][1] = -a / 2; tri[17][2] = -a / 2;
	//Triangulo e1
	tri[18][0] = -a / 2; tri[18][1] = a / 2; tri[18][2] = a / 2;
	tri[19][0] = -a / 2; tri[19][1] = -a / 2; tri[19][2] = a / 2;
	tri[20][0] = -a / 2; tri[20][1] = a / 2; tri[20][2] = -a / 2;
	//Triangulo e2
	tri[21][0] = -a / 2; tri[21][1] = a / 2; tri[21][2] = -a / 2;
	tri[22][0] = -a / 2; tri[22][1] = -a / 2; tri[22][2] = a / 2;
	tri[23][0] = -a / 2; tri[23][1] = -a / 2; tri[23][2] = -a / 2;
	//Triangulo c1
	tri[24][0] = -a / 2; tri[24][1] = a / 2; tri[24][2] = -a / 2;
	tri[25][0] = a / 2; tri[25][1] = a / 2; tri[25][2] = -a / 2;
	tri[26][0] = -a / 2; tri[26][1] = a / 2; tri[26][2] = a / 2;
	//Triangulo c2
	tri[27][0] = -a / 2; tri[27][1] = a / 2; tri[27][2] = a / 2;
	tri[28][0] = a / 2; tri[28][1] = a / 2; tri[28][2] = -a / 2;
	tri[29][0] = a / 2; tri[29][1] = a / 2; tri[29][2] = a / 2;
	//Triangulo b1
	tri[30][0] = -a / 2; tri[30][1] = -a / 2; tri[30][2] = -a / 2;
	tri[31][0] = -a / 2; tri[31][1] = -a / 2; tri[31][2] = a / 2;
	tri[32][0] = a / 2; tri[32][1] = -a / 2; tri[32][2] = -a / 2;
	//Triangulo b2
	tri[33][0] = -a / 2; tri[33][1] = -a / 2; tri[33][2] = a / 2;
	tri[35][0] = a / 2; tri[35][1] = -a / 2; tri[35][2] = -a / 2;
	tri[34][0] = a / 2; tri[34][1] = -a / 2; tri[34][2] = a / 2;
}

void Cubo::Desenha()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; i += 3)
	{
		float Temp[3][3];
		Temp[0][0] = tri[i][0]; Temp[0][1] = tri[i][1]; Temp[0][2] = tri[i][2];
		Temp[1][0] = tri[i+1][0]; Temp[1][1] = tri[i+1][1]; Temp[1][2] = tri[i+1][2];
		Temp[2][0] = tri[i+2][0]; Temp[2][1] = tri[i+2][1]; Temp[2][2] = tri[i+2][2];
		Triangle f(1, Temp);
		glNormal3fv(f.normal);
		glVertex3fv(Temp[0]);
		glVertex3fv(Temp[1]);
		glVertex3fv(Temp[2]);
	}
	glEnd();
}

Cubo::~Cubo()
{
}
