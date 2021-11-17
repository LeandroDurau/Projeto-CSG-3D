#pragma once
class Triangle
{
public:
	int Id;
	float vertices[3][3];		// 3 vértices do triângulo
	float normal[3];		    // vetor normal a este triângulo
public:
	Triangle(int tId, float tvertices[3][3]);
	~Triangle();
};

