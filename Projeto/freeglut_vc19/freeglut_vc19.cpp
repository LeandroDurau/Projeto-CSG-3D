/// MS VS
#include <windows.h>      // for MS Windows
#include <GL\glew.h>
#include <GL\freeglut.h>  // GLUT, include glu.h and gl.h
#include <stdio.h>
#include <iostream>
using namespace std;

/* Global variables */
char title[] = "OpenGL-PUC PR (Projeção Ortogonal Fixa)";

/* Initialize OpenGL Graphics */
void initGL() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color
}

/* Handler for window-repaint event. Called back when the window first appears and
whenever the window needs to be re-painted. */
void render() {
	glMatrixMode(GL_MODELVIEW);        // To operate on model-view matrix
	glLoadIdentity();                  // Reset the model-view matrix
	glTranslatef(50.0f, 50.0f, 0.0f);  // Translação - afeta as coordenadas das geometrias defindas a seguir
	glutWireTeapot(25.0);			   // valores em sistema de coordenadas do mundo
	glFlush();
}

/* Handler for window re-size event. Called back when the window first appears and
whenever the window is re-sized with its new width and height */
void reshape(GLsizei w, GLsizei h) {

	if (h == 0) h = 1; // avoid division by zero

	glViewport(0, 0, w, h);  // set Viewport dimensions

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Definição do volume de visualização em uma projeção ortogonal
	// eixo X horizontal, Y vertical, Z perpendicular a tela
	// limites definidos em sistemas de coordenadas do mundo
	glOrtho(0, 100, 0, 100, 0, 100); // limites: esquerda, direita, inferior, superior, próximo, distante

}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Define buffered mode
	glutInitWindowSize(640, 480);     // Set the window's initial width & height
	glutInitWindowPosition(50, 50);   // Position the window's initial top-left corner
	glutCreateWindow(title);          // Create window with the given title
	glutDisplayFunc(render);          // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);         // Register callback handler for window re-size event
	initGL();                         // Our own OpenGL initialization

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	cout << "Renderer:" << renderer << endl;
	cout << "OpenGL version supported:" << version << endl;
	cout << "Codigo Minimo com Projeção Ortogonal FIXA - sem ajuste das proporcoes " << endl;

	glutMainLoop();                   // Enter the infinite event-processing loop
	return 0;
}