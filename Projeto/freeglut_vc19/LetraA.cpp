#include "LetraA.h"
#include <math.h>
#include <GL\freeglut.h>
#include "Triangle.h"

LetraA::LetraA()
{

}

void LetraA::setValores(float aresta)
{
	a = aresta;
	b = a/2;

	//Triangulo1 e ´Perna esquerda
	tri[0][0] = -a; tri[0][1] = 0; tri[0][2] = 0;
	tri[1][0] = 0; tri[1][1] = 4*(a-b); tri[1][2] = 0;
	tri[2][0] = -a+b; tri[2][1] = 0; tri[2][2] = 0;

	//Triangulo2
	tri[3][0] = -a; tri[3][1] = 0; tri[3][2] = 0;
	tri[4][0] = 0; tri[4][1] = 4*a; tri[4][2] = 0;
	tri[5][0] = 0; tri[5][1] = 4*(a-b); tri[5][2] = 0;

	//Triangulo3 e Perna direita
	tri[6][0] = a; tri[6][1] = 0; tri[8][2] = 0;
	tri[7][0] = a-b; tri[7][1] = 0; tri[7][2] = 0;
	tri[8][0] = 0; tri[8][1] = 4*(a-b); tri[6][2] = 0;

	//Triangulo4
	tri[9][0] = a; tri[9][1] = 0; tri[9][2] = 0;
	tri[10][0] = 0; tri[10][1] = 4*(a-b); tri[10][2] = 0;
	tri[11][0] = 0; tri[11][1] = 4*a; tri[11][2] = 0;

	//Triangulo5 e traço do meio
	tri[12][0] = -a+b+(a/8); tri[12][1] = a/2; tri[12][2] = 0;
	tri[13][0] = -a+b+(a/8)-(b/4); tri[13][1] = (a/2)+b; tri[13][2] = 0;
	tri[14][0] = a-b-(a/8); tri[14][1] = a / 2; tri[14][2] = 0;

	//Triangulo6
	tri[15][0] = a-b-(a/8); tri[15][1] = a/2; tri[15][2] = 0;
	tri[16][0] = -a+b+(a/8) - (b / 4); tri[16][1] = (a / 2)+b; tri[16][2] = 0;
	tri[17][0] = a-b-(a/8) + (b / 4); tri[17][1] = (a / 2) + b; tri[17][2] = 0;
}

void LetraA::Desenha()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 18; i += 3)
	{
		float Temp[3][3];
		Temp[0][0] = tri[i][0]; Temp[0][1] = tri[i][1]; Temp[0][2] = tri[i][2];
		Temp[1][0] = tri[i + 1][0]; Temp[1][1] = tri[i + 1][1]; Temp[1][2] = tri[i + 1][2];
		Temp[2][0] = tri[i + 2][0]; Temp[2][1] = tri[i + 2][1]; Temp[2][2] = tri[i + 2][2];
		Triangle f(1, Temp);
		glNormal3fv(f.normal);
		glVertex3fv(Temp[0]);
		glVertex3fv(Temp[1]);
		glVertex3fv(Temp[2]);
	}
	glEnd();
}

LetraA::~LetraA()
{
}

