/// MS VS
#include <windows.h>      // for MS Windows
#include <GL\glew.h>
#include <GL\freeglut.h>  // GLUT, include glu.h and gl.h
#include <iostream>		  // for "cout <<" 
#include <string>

#include <fstream>

#include "Triangle.h"
#include "TetraHedro.h"
#include "Cubo.h"
#include "Disco.h"
#include "Cone.h"
#include "Cilindro.h"

using namespace std;

char title[] = "OpenGL-PUC PR 2021 - ";

boolean grid_on = true;
boolean lights_on = true;
int numObjects;
int resolution = 24;

GLfloat nRange = 100.0f;
GLfloat angleV = 45.0f, fAspect;
GLfloat angleX = 0.0f, angleY = 0.0f, angleZ;
GLfloat obsX = 0, obsY = 0, obsZ = 200;
GLfloat zNear = +100.0f;
GLfloat zFar = -100.0f;
GLfloat zCut = 0.0f;

GLfloat posicaoLuz[4] = { 0.0, 150.0, 500.0, 1.0 };

typedef struct objeto {
	int id;
	float dim1, dim2;
	float x, y, z;
	float r, g, b;
};

objeto ObjectList[12];

Cubo cuboNosso;
Disco discoNosso(resolution);
Cone coneNosso(resolution);
Cilindro cilindroNosso(resolution);



void cor(std::string n_cor) {
	if (n_cor == "BRANCO") glColor3f(1.0f, 1.0f, 1.0f); else
		if (n_cor == "CINZA") glColor3f(0.5f, 0.5f, 0.5f); else
			if (n_cor == "VERMELHO") glColor3f(1.0f, 0.0f, 0.0f); else
				if (n_cor == "VERDE") glColor3f(0.0f, 1.0f, 0.0f); else
					if (n_cor == "AZUL") glColor3f(0.0f, 0.0f, 1.0f); else
						if (n_cor == "AMARELO") glColor3f(1.0f, 1.0f, 0.0f); else
							if (n_cor == "CIANO") glColor3f(0.0f, 1.0f, 1.0f); else
								if (n_cor == "MAGENTA") glColor3f(1.0f, 0.0f, 1.0f); else
									if (n_cor == "PRETO") glColor3f(0.0f, 0.0f, 0.0f);
}

// Fun��o usada para especificar o volume de visualiza��o
void setVisParam(void)
{
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();
	// Especifica a proje��o perspectiva
	gluPerspective(angleV, fAspect, zNear + zCut, zFar - zCut); // fovy, aspect ratio, zNear, zFar
	glMatrixMode(GL_MODELVIEW); // Especifica sistema de coordenadas do modelo
	glLoadIdentity(); 	        // Inicializa sistema de coordenadas do modelo
	// Especifica posi��o do observador e do alvo
	gluLookAt(obsX, obsY, obsZ, 0, 0, 0, 0, 1, 0); // eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ
}

/* Handler for window re-size event. Called back when the window first appears and
whenever the window is re-sized with its new width and height */
void reshape(GLsizei w, GLsizei h) {
	// Para previnir uma divis�o por zero
	if (h == 0) h = 1;
	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
	// Calcula a corre��o de aspecto
	fAspect = (GLfloat)w / (GLfloat)h;
	setVisParam();
}

// Keyboard ...
void processSpecialKeys(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_LEFT:
		angleY--;
		break;
	case GLUT_KEY_RIGHT:
		angleY++;
		break;
	case GLUT_KEY_UP:
		angleX--;
		break;
	case GLUT_KEY_DOWN:
		angleX++;
		break;
	case GLUT_KEY_PAGE_UP:
		angleZ--;
		break;
	case GLUT_KEY_PAGE_DOWN:
		angleZ++;
		break;
	}
	setVisParam();
	glutPostRedisplay();
}
void DisplayFileRead(const char* fileName) // na vers�o 2015 (char * fileName)
{
	fstream inStream;
	inStream.open(fileName, ios::in); // abre o arquivo
	if (inStream.fail()) return;      //falha na abertura do arquivo
	cout << "Abertura do arquivo com sucesso ..." << endl;
	inStream >> numObjects;			  // l� primeira linha do arquivo, n�mero de objetos 
	cout << numObjects << " Objetos na cena ..." << endl;
	for (int i = 1; i <= numObjects; i++) { // leitura das demais linhas, id dos objetos, dimens�es, posi��o e cor
		inStream >> ObjectList[i].id
			>> ObjectList[i].dim1 >> ObjectList[i].dim2
			>> ObjectList[i].x >> ObjectList[i].y >> ObjectList[i].z
			>> ObjectList[i].r >> ObjectList[i].g >> ObjectList[i].b;
	}
	inStream.close();				// fecha o arquivo
}
void processRegularKey(unsigned char key, int xx, int yy) {
	switch (key) {
	case 'L':
	case 'l':
		if (lights_on) {
			lights_on = false;
			glDisable(GL_LIGHTING);
		}
		else {
			lights_on = true;
			glEnable(GL_LIGHTING);
		}
		break;
	case 'G':
	case 'g':
		if (grid_on) grid_on = false; else grid_on = true;
		break;
	}
	setVisParam();
	glutPostRedisplay();
}
// Fun��o callback chamada para gerenciar eventos do mouse
void mouse(int button, int state, int xx, int yy)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angleV >= 10) angleV -= 2;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angleV <= 130) angleV += 2;
		}
	setVisParam();
	glutPostRedisplay();
}

/* Initialize OpenGL Graphics */
void initGL() {
	angleV = 45;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);			  // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);				  // Set the type of depth-test
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	glShadeModel(GL_FLAT);
//	glShadeModel(GL_SMOOTH);

	GLfloat luzAmbiente[4]  = { 0.2,0.2,0.2,1.0 };
	GLfloat luzDifusa[4]    = { 0.5,0.5,0.5,1.0 };
	GLfloat luzEspecular[4] = { 0.5,0.5,0.5,1.0 };

	// Capacidade de brilho do material
	GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
	GLint especMaterial = 40;
	// Especifica que a cor de fundo da janela ser� preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Define a reflet�ncia do material 
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentra��o do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	// Define os par�metros da luz de n�mero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
	// Habilita a defini��o da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de ilumina��o
	glEnable(GL_LIGHTING);
	// Habilita a luz de n�mero 0
	glEnable(GL_LIGHT0);
}
void grid() {
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	cor("CINZA"); // grid
	for (int i = -nRange; i <= +nRange; i = i + 10) {
		glVertex3f(-nRange, float(i), 0.0f);
		glVertex3f(+nRange, float(i), 0.0f);

		glVertex3f(float(i), -nRange, 0.0f);
		glVertex3f(float(i), +nRange, 0.0f);
	}
	glEnd();
	glLineWidth(3.0f);
	glBegin(GL_LINES); // eixos
		cor("VERMELHO"); // vermelho eixo x
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(nRange / 2, 0.0f, 0.0f);
		cor("VERDE"); // verde eixo y
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, nRange / 2, 0.0f);
		cor("AZUL"); // azul eixo z
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, nRange / 2);
	glEnd();
	glLineWidth(1.0f);
}


/* Handler for window-repaint event. Called back when the window first appears and
whenever the window needs to be re-painted. */
void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

	glPushMatrix();
		glRotatef(angleX, 1.0f, 0.0f, 0.0f);
		glRotatef(angleY, 0.0f, 1.0f, 0.0f);
		glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
		if (grid_on) grid();


	for (int i = 1; i <= numObjects; i++) {
		switch (ObjectList[i].id) {
		case 1: //cubo
			glPushMatrix();
			glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
			glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
			glutSolidCube(ObjectList[i].dim1);
			glPopMatrix();
			break;
		case 2: //esfera
			glPushMatrix();
			glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
			glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
			glutSolidSphere(ObjectList[i].dim1, resolution, resolution);
			glPopMatrix();
			break;
		case 3: //Teapot
			glPushMatrix();
			glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
			glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
			glutSolidTeapot(ObjectList[i].dim1);
			glPopMatrix();
			break;
		case 4: //Teacup
			glPushMatrix();
			glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
			glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
			glutSolidTeacup(ObjectList[i].dim1);
			glPopMatrix();
			break;
		case 5: //Cubo nosso
			glPushMatrix();
			glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
			glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
			cuboNosso.setValores(ObjectList[i].dim1);
			cuboNosso.Desenha();
			glPopMatrix();
			break;
		case 6: //Disco nosso
			glPushMatrix();
			glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
			glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
			discoNosso.setValores(ObjectList[i].dim1);
			discoNosso.Desenha();
			glPopMatrix();
			break;
		case 7: //Cone nosso
			glPushMatrix();
			glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
			glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
			coneNosso.setValores(ObjectList[i].dim1, ObjectList[i].dim2);
			coneNosso.Desenha();
			glPopMatrix();
			break;
		case 8: //Cilindro nosso
			glPushMatrix();
			glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
			glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
			cilindroNosso.setValores(ObjectList[i].dim1, ObjectList[i].dim2);
			cilindroNosso.Desenha();
			glPopMatrix();
			break;
		}
	}

	glPopMatrix();
	glutSwapBuffers(); 
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	glutInit(&argc, argv);             // Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Define double buffered mode
	glutInitWindowSize(640, 480);      // Set the window's initial width & height
	glutInitWindowPosition(50, 50);    // Position the window's initial top-left corner
	glutCreateWindow(title);           // Create window with the given title
	glutDisplayFunc(render);           // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);          // Register callback handler for window re-size event
	glutSpecialFunc(processSpecialKeys);  // Register callback handler for arrow keys 
	glutKeyboardFunc(processRegularKey);
	glutMouseFunc(mouse);
	DisplayFileRead("df.txt");

	initGL();                           // Our own OpenGL initialization

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	cout << "Renderer:" << renderer << endl;
	cout << "OpenGL version supported:" << version << endl;

	cout << "MENU" << endl;
	cout << "Projecao Perspectiva" << endl;
	cout << "Eixo X em Vermelho" << endl;
	cout << "Eixo Y em Verde" << endl;
	cout << "Eixo Z em Azul" << endl;
	cout << "Interacao:" << endl;
	cout << "Mouse: botao esquerdo zoom in, direito zoom out" << endl;
	cout << "Teclado: setas rotacao da cena (eixos X e Y)" << endl;
	cout << "Teclado: PgUp e PgDn rotacao da cena (eixo Z)" << endl;
	cout << "Teclado: tecla L liga a iluminacao" << endl;
	cout << "Teclado: tecla O desliga a iluminacao" << endl;
	cout << "Teclado: tecla G liga e desliga o desenho do Grid" << endl;

	glutMainLoop();                 // Enter the infinite event-processing loop
	return 0;
}