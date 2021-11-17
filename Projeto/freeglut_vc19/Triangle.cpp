#include <math.h>
#include "Triangle.h"

Triangle::Triangle(int tId, float tvertices[3][3])
{
	Id = tId;
	vertices[0][0] = tvertices[0][0];  // vértice 0 coord x
	vertices[0][1] = tvertices[0][1];  // vértice 0 coord y
	vertices[0][2] = tvertices[0][2];  // vértice 0 coord z
	vertices[1][0] = tvertices[1][0];
	vertices[1][1] = tvertices[1][1];
	vertices[1][2] = tvertices[1][2];
	vertices[2][0] = tvertices[2][0];
	vertices[2][1] = tvertices[2][1];
	vertices[2][2] = tvertices[2][2];

	// Cálculo do vetor Normal
	float v1[3], v2[3];
	float length;  // comprimento do vetor
	// v1 = P0 - P1
	v1[0] = vertices[0][0] - vertices[1][0];  // comp x do vetor v1
	v1[1] = vertices[0][1] - vertices[1][1];  // comp y
	v1[2] = vertices[0][2] - vertices[1][2];  // comp z
	// v2 = P2 - P1
	v2[0] = vertices[2][0] - vertices[1][0];
	v2[1] = vertices[2][1] - vertices[1][1];
	v2[2] = vertices[2][2] - vertices[1][2];

	normal[0] = v1[1] * v2[2] - v1[2] * v2[1];
	normal[1] = v1[2] * v2[0] - v1[0] * v2[2];
	normal[2] = v1[0] * v2[1] - v1[1] * v2[0];

	//	Cálculo do comprimento do vetor
	length = (float)sqrt(pow(normal[0], 2.0) + pow(normal[1], 2.0) + pow(normal[2], 2.0));
	// Evita divisão por zero
	if (length == 0.0f) length = 1.0f;
	// Divide cada elemento pelo comprimento do vetor
	normal[0] /= length;
	normal[1] /= length;
	normal[2] /= length;
}


Triangle::~Triangle()
{
}
