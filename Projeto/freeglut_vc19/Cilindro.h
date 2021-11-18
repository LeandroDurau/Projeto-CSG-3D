#pragma once
#define _USE_MATH_DEFINES
class Cilindro
{
public:
	int resolucao;
	float tri[100][3];
	float raio;
	float altura;
public:
	Cilindro(int resolucaoz);
	void Desenha();
	void setValores(float r, float a);
	~Cilindro();
};

