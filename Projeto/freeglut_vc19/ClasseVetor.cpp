#include <math.h>
#include <GL\freeglut.h>  // GLUT, include glu.h and gl.h

class Vetor {
public:
	int Id;
	float xcomp;
	float ycomp;
	float zcomp;
public:
	Vetor(int tId, float txcomp, float tycomp, float tzcomp) {
		Id = tId;
		xcomp = txcomp;
		ycomp = tycomp;
		zcomp = tzcomp;
	}

	void Desenha(float xpos, float ypos, float zpos) {
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glVertex3f(xpos, ypos, zpos);
		glVertex3f(xpos + xcomp, ypos + ycomp, zpos + zcomp);
		glEnd();
		glPushMatrix();
		glTranslatef(xpos + xcomp, ypos + ycomp, zpos + zcomp);
		glutSolidSphere(5, 5, 5);
		glPopMatrix();
		glLineWidth(1.0f);
	}

	float Magnitude() {
		return sqrt(xcomp*xcomp + ycomp * ycomp + zcomp * zcomp);
	}

	void MultEscalar(float k) {
		xcomp = k * xcomp;
		ycomp = k * ycomp;
		zcomp = k * zcomp;
	}

	void SomaVetor(Vetor tVetor) {
		xcomp = xcomp + tVetor.xcomp;
		ycomp = ycomp + tVetor.ycomp;
		zcomp = zcomp + tVetor.zcomp;
	}

	void SubtraiVetor(Vetor tVetor) {
		xcomp = xcomp - tVetor.xcomp;
		ycomp = ycomp - tVetor.ycomp;
		zcomp = zcomp - tVetor.zcomp;
	}

	float ProdutoEscalar(Vetor tVetor) {
		return (xcomp * tVetor.xcomp) + (ycomp * tVetor.ycomp) + (zcomp * tVetor.zcomp);
	}

	Vetor ProdutoVetorial(Vetor v1, Vetor v2) {
		Vetor vr(0,0,0,0);
		float t1 = v1.ycomp * v2.zcomp;
		float t2 = v1.zcomp * v2.xcomp;
		float t3 = v1.xcomp * v2.ycomp;
		float t4 = v1.ycomp * v2.xcomp;
		float t5 = v1.zcomp * v2.ycomp;
		float t6 = v1.xcomp * v2.zcomp;
		vr.xcomp = t1 - t5;
		vr.ycomp = t2 - t6;
		vr.zcomp = t3 - t4;
		return vr;
	}

	bool Ortogonal(Vetor tVetor) {
		if (ProdutoEscalar(tVetor) == 0) return true; else return false;
	}

	void Normalizar() {
		xcomp = xcomp / Magnitude();
		ycomp = ycomp / Magnitude();
		zcomp = zcomp / Magnitude();
	}

	Vetor Soma2Vetores(Vetor v1, Vetor v2) {
		Vetor vr(0, 0, 0, 0);
		vr.xcomp = v1.xcomp + v2.xcomp;
		vr.ycomp = v1.ycomp + v2.ycomp;
		vr.zcomp = v1.zcomp + v2.zcomp;
		return vr;
	}

	Vetor Subtrai2Vetores(Vetor v1, Vetor v2) {
		Vetor vr(0, 0, 0, 0);
		vr.xcomp = v1.xcomp - v2.xcomp;
		vr.ycomp = v1.ycomp - v2.ycomp;
		vr.zcomp = v1.zcomp - v2.zcomp;
		return vr;
	}
};