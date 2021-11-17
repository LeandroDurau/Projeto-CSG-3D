#include <math.h>
#include <GL\freeglut.h>
#include "Triangle.h"
#include "TetraHedro.h"

#include <iostream>		  // for "cout <<"
using namespace std;

TetraHedro::TetraHedro(int idC, float ppcx, float ppcy, float ppcz, float aa)
{
	pcx = ppcx;
	pcy = ppcy;
	pcz = ppcz;
	a = aa;
	id = idC;

	float angulo = 30.0f*PI / 180.0f; 
	// Base como um triângulo equilátero com o centro na origem e altura "a"

	t1[0][0] =  0.0f;             t1[0][1] =  0.0f;             t1[0][2] = a;    // Face 1
	t1[1][0] =  a * cos(angulo);  t1[1][1] = -a * sin(angulo);  t1[1][2] = 0.0f;
	t1[2][0] = -a * cos(angulo);  t1[2][1] = -a * sin(angulo);  t1[2][2] = 0.0f;

	t2[0][0] = 0.0f;              t2[0][1] =  0.0f;             t2[0][2] = a;    // Face 2
	t2[1][0] = 0.0f;              t2[1][1] =  a;                t2[1][2] = 0.0f;
	t2[2][0] = a * cos(angulo);   t2[2][1] = -a * sin(angulo);  t2[2][2] = 0.0f;

	t3[0][0] =  0;                t3[0][1] =  0;                t3[0][2] = a;    // Face 3 
	t3[1][0] = -a * cos(angulo);  t3[1][1] = -a * sin(angulo);  t3[1][2] = 0;
	t3[2][0] =  0;                t3[2][1] =  a;                t3[2][2] = 0;

	t4[0][0] =  0.0f;             t4[0][1] =  a;                t4[0][2] = 0.0f; // Face 4, Base
	t4[1][0] = -a * cos(angulo);  t4[1][1] = -a * sin(angulo);  t4[1][2] = 0.0f;
	t4[2][0] =  a * cos(angulo);  t4[2][1] = -a * sin(angulo);  t4[2][2] = 0.0f;
}

void TetraHedro::Desenha()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // desenha faces posteriores somente com arestas
	glPushMatrix();
	glTranslatef(pcx, pcy, pcz);

	glBegin(GL_TRIANGLES);
		Triangle f1(1,t1);		// face 1
		glNormal3fv(f1.normal);
		glVertex3fv(t1[0]);
		glVertex3fv(t1[1]);
		glVertex3fv(t1[2]);
	
		Triangle f2(1, t2);		// face 2
		glNormal3fv(f2.normal);
		glVertex3fv(t2[0]);
		glVertex3fv(t2[1]);
		glVertex3fv(t2[2]);

		Triangle f3(1, t3);		// face 3
		glNormal3fv(f3.normal);
		glVertex3fv(t3[0]);
		glVertex3fv(t3[1]);
		glVertex3fv(t3[2]);

		Triangle f4(1, t4);		// face 4
		glNormal3fv(f4.normal);
		glVertex3fv(t4[0]);
		glVertex3fv(t4[1]);
		glVertex3fv(t4[2]);
	glEnd();

	// desenha os vetores normais
	// cálculo do centro das faces
	// Face 1
	// centro da face
	float cf1x = (t1[0][0] + t1[1][0] + t1[2][0] ) / 3; //  média dos componentes em x
	float cf1y = (t1[0][1] + t1[1][1] + t1[2][1] ) / 3;
	float cf1z = (t1[0][2] + t1[1][2] + t1[2][2] ) / 3;
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex3f(cf1x, cf1y, cf1z);
		glVertex3f(cf1x + f1.normal[0] * 10, cf1y + f1.normal[1] * 10, cf1z + f1.normal[2] * 10);
	glEnd();
	// Face 2
	float cf2x = (t2[0][0] + t2[1][0] + t2[2][0]) / 3; //  média dos componentes em x
	float cf2y = (t2[0][1] + t2[1][1] + t2[2][1]) / 3;
	float cf2z = (t2[0][2] + t2[1][2] + t2[2][2]) / 3;
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex3f(cf2x, cf2y, cf2z);
		glVertex3f(cf2x + f2.normal[0] * 10, cf2y + f2.normal[1] * 10, cf2z + f2.normal[2] * 10);
	glEnd();
	// Face 3
	float cf3x = (t3[0][0] + t3[1][0] + t3[2][0]) / 3; //  média dos componentes em x
	float cf3y = (t3[0][1] + t3[1][1] + t3[2][1]) / 3;
	float cf3z = (t3[0][2] + t3[1][2] + t3[2][2]) / 3;
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex3f(cf3x, cf3y, cf3z);
		glVertex3f(cf3x + f3.normal[0] * 10, cf3y + f3.normal[1] * 10, cf3z + f3.normal[2] * 10);
	glEnd();
	// Face 4
	float cf4x = (t4[0][0] + t4[1][0] + t4[2][0]) / 3; //  média dos componentes em x
	float cf4y = (t4[0][1] + t4[1][1] + t4[2][1]) / 3;
	float cf4z = (t4[0][2] + t4[1][2] + t4[2][2]) / 3;
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex3f(cf4x, cf4y, cf4z);
		glVertex3f(cf4x + f4.normal[0] * 10, cf4y + f4.normal[1] * 10, cf4z + f4.normal[2] * 10);
	glEnd();

	glPopMatrix();
}

TetraHedro::~TetraHedro()
{
}
