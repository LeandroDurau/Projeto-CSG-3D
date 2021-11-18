#include "Cilindro.h"
#include <math.h>
#include <GL\freeglut.h>
#include "Triangle.h"

Cilindro::Cilindro(int resolucaoz)
{
	resolucao = resolucaoz;
}

void Cilindro::Desenha()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < resolucao; i++)
	{
		float Temp[3][3];
		Temp[0][0] = 0; Temp[0][1] = -altura/2; Temp[0][2] = 0;
		Temp[1][0] = tri[i][0]; Temp[1][1] = -altura / 2; Temp[1][2] = tri[i][2];
		Temp[2][0] = tri[i + 1][0]; Temp[2][1] = -altura / 2; Temp[2][2] = tri[i + 1][2];
		Triangle f(1, Temp);
		glNormal3fv(f.normal);
		glVertex3fv(Temp[0]);
		glVertex3fv(Temp[1]);
		glVertex3fv(Temp[2]);

		Temp[0][0] = 0; Temp[0][1] = altura/2; Temp[0][2] = 0;
		Temp[1][0] = tri[i + 1][0]; Temp[1][1] = altura / 2; Temp[1][2] = tri[i + 1][2];
		Temp[2][0] = tri[i][0]; Temp[2][1] = altura / 2; Temp[2][2] = tri[i][2];

		Triangle f1(1, Temp);
		glNormal3fv(f1.normal);
		glVertex3fv(Temp[0]);
		glVertex3fv(Temp[1]);
		glVertex3fv(Temp[2]);

		float Temp2[6][3];

		Temp2[0][0] = tri[i][0]; Temp2[0][1] = altura / 2; Temp2[0][2] = tri[i][2];
		Temp2[1][0] = tri[i+1][0]; Temp2[1][1] = altura / 2; Temp2[1][2] = tri[i+1][2];
		Temp2[2][0] = tri[i][0]; Temp2[2][1] = -altura / 2; Temp2[2][2] = tri[i][2];

		Temp2[3][0] = tri[i+1][0]; Temp2[3][1] = altura / 2; Temp2[3][2] = tri[i+1][2];
		Temp2[4][0] = tri[i+1][0]; Temp2[4][1] = -altura / 2; Temp2[4][2] = tri[i+1][2];
		Temp2[5][0] = tri[i][0]; Temp2[5][1] = -altura / 2; Temp2[5][2] = tri[i][2];

		Triangle f2(1, Temp2);
		glNormal3fv(f2.normal);
		glVertex3fv(Temp2[0]);
		glVertex3fv(Temp2[1]);
		glVertex3fv(Temp2[2]);
		glVertex3fv(Temp2[3]);
		glVertex3fv(Temp2[4]);
		glVertex3fv(Temp2[5]);
	}
	glEnd();
}

void Cilindro::setValores(float r, float h)
{
	altura = h;
	raio = r;
	int i = 0;
	for (GLfloat angle = 0.0; angle < (2.0 * M_PI); angle += (2.0 * M_PI / resolucao)) {
		GLfloat x = raio * sin(angle);
		GLfloat y = raio * cos(angle);
		tri[i][0] = x; tri[i][1] = 0; tri[i][2] = y;
		i++;
	}
}

Cilindro::~Cilindro()
{
}
