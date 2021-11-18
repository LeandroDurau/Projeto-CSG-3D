#include "Cone.h"
#include <math.h>
#include <GL\freeglut.h>
#include "Triangle.h"

Cone::Cone(int resolucaoz)
{
	resolucao = resolucaoz;
}

void Cone::Desenha()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < resolucao; i++)
	{
		float Temp[3][3];
		Temp[0][0] = 0; Temp[0][1] = 0; Temp[0][2] = 0;
		Temp[1][0] = tri[i][0]; Temp[1][1] = tri[i][1]; Temp[1][2] = tri[i][2];
		Temp[2][0] = tri[i + 1][0]; Temp[2][1] = tri[i + 1][1]; Temp[2][2] = tri[i + 1][2];
		Triangle f(1, Temp);
		glNormal3fv(f.normal);
		glVertex3fv(Temp[0]);
		glVertex3fv(Temp[1]);
		glVertex3fv(Temp[2]);

		Temp[0][0] = 0; Temp[0][1] = 0; Temp[0][2] = altura;
		Triangle f1(1, Temp);
		glNormal3fv(f1.normal);
		glVertex3fv(Temp[0]);
		glVertex3fv(Temp[1]);
		glVertex3fv(Temp[2]);
	}
	glEnd();
}

void Cone::setValores(float r, float h)
{
	altura = h;
	raio = r;
	int i = 0;
	for (GLfloat angle = 0.0; angle < (2.0 * M_PI); angle += (2.0 * M_PI / resolucao)) {
		GLfloat x = raio * sin(angle);
		GLfloat y = raio * cos(angle);
		tri[i][0] = x; tri[i][1] = y; tri[i][2] = 0;
		i++;
	}
}

Cone::~Cone()
{
}
