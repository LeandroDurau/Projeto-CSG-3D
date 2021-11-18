#pragma once
#define _USE_MATH_DEFINES
class Disco
{
public:
	int resolucao;
	float tri[100][3];
	float raio;
public:
	Disco(int resolucaoz);
	void Desenha();
	void setValores(float r);
	~Disco();
};

