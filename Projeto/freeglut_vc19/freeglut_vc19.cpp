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
#include "ClasseVetor.cpp"

using namespace std;

char title[] = "OpenGL-PUC PR 2021 - Projeto TDE ";

boolean grid_on = true;
boolean lights_on = true;
boolean projection_perspective = true;
boolean objOnOff = true;
int numObjects;
int resolution = 24;
int selector = 1;

GLfloat nRange = 100.0f;
GLfloat angleV = 45.0f, fAspect;
GLfloat angleX = 0.0f, angleY = 0.0f, angleZ;
GLfloat obsX = 0, obsY = 0, obsZ = 200;
GLfloat zNear = +100.0f;
GLfloat zFar = -100.0f;
GLfloat zCut = 0.0f;

GLfloat posicaoLuz[4];
GLfloat luzAmbiente[4];
GLfloat luzDifusa[4];
GLfloat luzEspecular[4];

//base para movimento (pegar do arquivo) [problema 2 dim possivel aumentar?]
Vetor posicao(1, 0.0f, 0.0f, 0.0f);
Vetor velocidade(2, 0.0f, 0.0f, 0.0f);
Vetor gravidade(3, 0.0f, -0.2f, 0.0f);

typedef struct objeto {
	int id;
	float dim1, dim2;
	float x, y, z;
	float r, g, b;
	boolean ligado;
};

objeto ObjectList[17];

Cubo cuboNosso;
Disco discoNosso(resolution);
Cone coneNosso(resolution);
Cilindro cilindroNosso(resolution);

Cone coneComposicao(resolution);
Cilindro cilindroComposicao(resolution);
Cilindro cilindroComposicao2(resolution);

Cubo cubomovimento;



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

// Função usada para especificar o volume de visualização
void setVisParam(void)
{
	if(projection_perspective){
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
	gluPerspective(angleV, fAspect, zNear + zCut, zFar - zCut); // fovy, aspect ratio, zNear, zFar
	glMatrixMode(GL_MODELVIEW); // Especifica sistema de coordenadas do modelo
	glLoadIdentity(); 	        // Inicializa sistema de coordenadas do modelo
	// Especifica posição do observador e do alvo
	gluLookAt(obsX, obsY, obsZ, 0, 0, 0, 0, 1, 0); // eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ
	}
}

/* Handler for window re-size event. Called back when the window first appears and
whenever the window is re-sized with its new width and height */
void reshape(GLsizei w, GLsizei h) {
	// Para previnir uma divisão por zero
	if (h == 0) h = 1;
	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w / (GLfloat)h;
	if(projection_perspective) setVisParam();
	else {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (w <= h) {
			glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
		}
		else {
			glOrtho(-nRange * w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
		}
	}
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
void DisplayFileRead(const char* fileName) // na versão 2015 (char * fileName)
{
	fstream inStream;
	inStream.open(fileName, ios::in); // abre o arquivo
	if (inStream.fail()) return;      //falha na abertura do arquivo
	cout << "Abertura do arquivo com sucesso ..." << endl;
	inStream >> numObjects;			  // lê primeira linha do arquivo, número de objetos 
	cout << numObjects << " Objetos na cena ..." << endl;
	for (int i = 1; i <= numObjects; i++) { // leitura das demais linhas, id dos objetos, dimensões, posição e cor
		inStream >> ObjectList[i].id
			>> ObjectList[i].dim1 >> ObjectList[i].dim2
			>> ObjectList[i].x >> ObjectList[i].y >> ObjectList[i].z
			>> ObjectList[i].r >> ObjectList[i].g >> ObjectList[i].b;
		ObjectList[i].ligado = true;
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
	case 'P':
	case 'p':
		if (projection_perspective) projection_perspective = false; else projection_perspective = true;
		break;
	case 'A':
	case 'a':
		selector--;
		if (selector < 1) {
			selector = 12;
		}
		break;
	case 'D':
	case 'd':
		selector++;
		if (selector > 12) selector = 1;
		break;
	case 'V':
	case 'v':
		if (ObjectList[selector].ligado)ObjectList[selector].ligado = false; else ObjectList[selector].ligado = true;
		break;
	case 'H':
	case 'h':
		ObjectList[selector].x--;
		break;
	case 'K':
	case 'k':
		ObjectList[selector].x++;
		break;
	case 'U':
	case 'u':
		ObjectList[selector].z--;
		break;
	case 'J':
	case 'j':
		ObjectList[selector].z++;
		break;
	case 'I':
	case 'i':
		ObjectList[selector].y--;
		break;
	case 'Y':
	case 'y':
		ObjectList[selector].y++;
		break;
	case 'R':
	case 'r':
		DisplayFileRead("df.txt");
		break;
	}
	setVisParam();
	glutPostRedisplay();
}
// Função callback chamada para gerenciar eventos do mouse
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

void update(int value) {
	// Adição do vetor velocidade ao vetor posicao
	posicao.SomaVetor(velocidade);
	// Adição do vetor gravidade ao vetor velocidade
	velocidade.SomaVetor(gravidade);
	// Verifica a colisão com os limites (inverte o vetor correspondente)
	if ((posicao.xcomp > nRange) || (posicao.xcomp < -nRange)) { // colisão é centro do cubo
		velocidade.xcomp = velocidade.xcomp * -1;
	}
	if ((posicao.zcomp > nRange) || (posicao.zcomp < -nRange)) {
		velocidade.zcomp = velocidade.zcomp * -1;
	}
	if ((posicao.ycomp > nRange) || (posicao.ycomp < -nRange)) {
		// Redução da velocidade quando colisão com o "chão"
		velocidade.ycomp = velocidade.ycomp * -0.95;
		posicao.ycomp = -nRange;
	}
	glutPostRedisplay(); // Informa a GLUT que o "display" foi alterado
	glutTimerFunc(25, update, 0);//Chama a função update após cada 25 milisegundos
}
/* Initialize OpenGL Graphics */
void initGL() {
	angleV = 45;

	for (int i = 1; i <= numObjects; i++) {
		switch (ObjectList[i].id) {
			
		case 12:
			velocidade.xcomp = ObjectList[i].x;
			velocidade.ycomp = ObjectList[i].y;
			velocidade.zcomp = ObjectList[i].z;
		case 100:
			posicaoLuz[0] = ObjectList[i].x;
			posicaoLuz[1] = ObjectList[i].y;
			posicaoLuz[2] = ObjectList[i].z;
			posicaoLuz[3] = ObjectList[i].dim1;
			break;
		case 101:
			luzAmbiente[0] = ObjectList[i].r;
			luzAmbiente[1] = ObjectList[i].g;
			luzAmbiente[2] = ObjectList[i].b;
			luzAmbiente[3] = ObjectList[i].dim1;
			break;
		case 102:
			luzDifusa[0] = ObjectList[i].r;
			luzDifusa[1] = ObjectList[i].g;
			luzDifusa[2] = ObjectList[i].b;
			luzDifusa[3] = ObjectList[i].dim1;
			break;
		case 103:
			luzEspecular[0] = ObjectList[i].r;
			luzEspecular[1] = ObjectList[i].g;
			luzEspecular[2] = ObjectList[i].b;
			luzEspecular[3] = ObjectList[i].dim1;
			break;
		}
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);			  // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);				  // Set the type of depth-test
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	glShadeModel(GL_FLAT);
//	glShadeModel(GL_SMOOTH);


	// Capacidade de brilho do material
	GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
	GLint especMaterial = 40;
	// Especifica que a cor de fundo da janela será preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Define a refletância do material 
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
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
		if (!projection_perspective) {
			glScalef(angleV/40, angleV/40, angleV/40);
		}
		if (grid_on) grid();


	for (int i = 1; i <= numObjects; i++) {
		switch (ObjectList[i].id) {
		case 1: //cubo
			if (ObjectList[i].ligado) {
				glPushMatrix();
				glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
				glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
				glutSolidCube(ObjectList[i].dim1);
				if (selector == 1) {
					glColor3f(1.0f, 1.0f, 1.0f);
					glutWireCube(ObjectList[i].dim1);
				}
				glPopMatrix();
			}
			break;
		case 2: //esfera
			if (ObjectList[i].ligado) {
				glPushMatrix();
				glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
				glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
				glutSolidSphere(ObjectList[i].dim1, resolution, resolution);
				if (selector == 2) {
					glColor3f(1.0f, 1.0f, 1.0f);
					glutWireSphere(ObjectList[i].dim1, resolution, resolution);
				}
				glPopMatrix();
			}
			break;
		case 3: //Teapot
			if (ObjectList[i].ligado) {
				glPushMatrix();
				glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
				glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
				glutSolidTeapot(ObjectList[i].dim1);
				if (selector == 3) {
					glColor3f(1.0f, 1.0f, 1.0f);
					glutWireTeapot(ObjectList[i].dim1);
				}
				glPopMatrix();
			}
			break;
		case 4: //Teacup
			if (ObjectList[i].ligado) {
				glPushMatrix();
				glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
				glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
				glutSolidTeacup(ObjectList[i].dim1);
				if (selector == 4) {
					glColor3f(1.0f, 1.0f, 1.0f);
					glutWireTeacup(ObjectList[i].dim1);
				}
				glPopMatrix();
			}
			break;
		case 5: //Cubo nosso
			if (ObjectList[i].ligado) {
				glPushMatrix();
				glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
				glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
				cuboNosso.setValores(ObjectList[i].dim1);
				cuboNosso.Desenha();
				if (selector == 5) {
					glColor3f(1.0f, 1.0f, 1.0f);
					glutWireCube(ObjectList[i].dim1);
				}
				glPopMatrix();
			}
			break;
		case 6: //Disco nosso
			if(ObjectList[i].ligado){
				glPushMatrix();
				glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
				glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
				discoNosso.setValores(ObjectList[i].dim1);
				discoNosso.Desenha();
				if (selector == 6) {
					glColor3f(1.0f, 1.0f, 1.0f);
					glutWireCone(ObjectList[i].dim1, 0.2, resolution, resolution);
				}
				glPopMatrix();
			}
			break;
		case 7: //Cone nosso
			if (ObjectList[i].ligado) {
				glPushMatrix();
				glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
				glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
				coneNosso.setValores(ObjectList[i].dim1, ObjectList[i].dim2);
				coneNosso.Desenha();
				if (selector == 7) {
					glColor3f(1.0f, 1.0f, 1.0f);
					glutWireCone(ObjectList[i].dim1, ObjectList[i].dim2, resolution, resolution);
				}
				glPopMatrix();
			}
			break;
		case 8: //Cilindro nosso
			if (ObjectList[i].ligado) {
				glPushMatrix();
				glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
				glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
				cilindroNosso.setValores(ObjectList[i].dim1, ObjectList[i].dim2);
				cilindroNosso.Desenha();
				if (selector == 8) {
					glPushMatrix();
						glRotatef(90, 1.0f, 0.0f, 0.0f);
						glTranslatef(0, 0, -ObjectList[i].dim2 / 2);
						glColor3f(1.0f, 1.0f, 1.0f);
						glutWireCylinder(ObjectList[i].dim1, ObjectList[i].dim2, resolution, resolution);
					glPopMatrix();
				}
				glPopMatrix();
			}
			break;
		case 9: //Composicao
			if (ObjectList[i].ligado) {
				glPushMatrix();
				glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
				glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
				cilindroComposicao.setValores(ObjectList[i].dim1, ObjectList[i].dim2);
				cilindroComposicao.Desenha();
				glPushMatrix();
				glRotatef(-90.0, 1.0, 0.0, 0.0);
				glTranslatef(0, 0, ObjectList[i].dim2 / 2);
				coneComposicao.setValores(ObjectList[i].dim1, ObjectList[i].dim2 / 2);
				coneComposicao.Desenha();
				if (selector == 9) {
					glColor3f(1.0f, 1.0f, 1.0f);
					glPushMatrix();
					glTranslatef(0, 0, -ObjectList[i].dim2);
					glutWireCylinder(ObjectList[i].dim1, ObjectList[i].dim2, resolution, resolution);
					glPopMatrix();
					glutWireCone(ObjectList[i].dim1, ObjectList[i].dim2/2, resolution, resolution);
				}
				glPopMatrix();
				glPopMatrix();
			}
			break;
		case 10://Cruz 3D
			if (ObjectList[i].ligado) {
				glColor3f(1.0f, 1.0f, 1.0f);
				glPushMatrix();
					glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
					glTranslatef(ObjectList[i].x, ObjectList[i].y, ObjectList[i].z);
					cilindroComposicao2.setValores(ObjectList[i].dim1, ObjectList[i].dim2 );
					glPushMatrix();
						glRotatef(90.0f, 1, 0, 0);
						cilindroComposicao2.Desenha();
					glPopMatrix();

					glPushMatrix();
						cilindroComposicao2.Desenha();
					glPopMatrix();

					glPushMatrix();
						glRotatef(90.0f, 0, 0, 1);
						cilindroComposicao2.Desenha();
					glPopMatrix();
					if (selector == 10) {
						glColor3f(1.0f, 1.0f, 1.0f);
						glPushMatrix();
							glRotatef(90.0f, 1, 0, 0);
							glTranslatef(0.0f, 0.0f, -25.0f);
							glutWireCylinder(ObjectList[i].dim1, ObjectList[i].dim2, resolution, resolution);
						glPopMatrix();

						glPushMatrix();
							glTranslatef(0.0f, 0.0f, -25.0f);
							glutWireCylinder(ObjectList[i].dim1, ObjectList[i].dim2, resolution, resolution);
						glPopMatrix();

						glPushMatrix();
							glRotatef(90.0f, 0, 1, 0);
							glTranslatef(0.0f, 0.0f, -25.0f);
							glutWireCylinder(ObjectList[i].dim1, ObjectList[i].dim2, resolution, resolution);
						glPopMatrix();
					}
				glPopMatrix();


			}

			break;
		case 11://Triangulo
			if (ObjectList[i].ligado) {


			}

			break;
		case 12://Cubo em movimento
			if (ObjectList[i].ligado) {//Cubo não some, erro no codigo?
				glPushMatrix();
					glColor3f(ObjectList[i].r, ObjectList[i].g, ObjectList[i].b);
					glTranslatef(posicao.xcomp,posicao.ycomp,posicao.zcomp);
					cubomovimento.setValores(ObjectList[i].dim1);
					cubomovimento.Desenha();
					if (selector == 12) {
						glColor3f(1.0f, 1.0f, 1.0f);
						glutWireCube(ObjectList[i].dim1);
					}
				glPopMatrix();
			}

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
	glutTimerFunc(25, update, 0);
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
	cout << "Teclado: tecla L liga e desliga a iluminacao" << endl;
	cout << "Teclado: tecla P muda entre perspectivas" << endl;
	cout << "Teclado: tecla G liga e desliga o desenho do Grid" << endl;
	cout << "Teclado: tecla A volta para o objeto anterior" << endl;
	cout << "Teclado: tecla D passa para o próximo objeto" << endl;
	cout << "Teclado: tecla V liga e desliga a visibilidade do objeto" << endl;
	cout << "Teclado: tecla H move objeto seleciona para esquerda" << endl;
	cout << "Teclado: tecla K move objeto seleciona para direita" << endl;
	cout << "Teclado: tecla Y move objeto seleciona para cima" << endl;
	cout << "Teclado: tecla I move objeto seleciona para baixo" << endl;
	cout << "Teclado: tecla J move objeto seleciona para frente" << endl;
	cout << "Teclado: tecla U move objeto seleciona para tras" << endl;
	cout << "Teclado: tecla R reseta localizacoes" << endl;
	glutMainLoop();                 // Enter the infinite event-processing loop
	return 0;
}