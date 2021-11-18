#pragma once
#define _USE_MATH_DEFINES
class Cone
{
public:
	int resolucao;
	float altura;
	float tri[100][3];
	float raio;
public:
	Cone(int resolucaoz);
	void Desenha();
	void setValores(float r, float h);
	~Cone();
};

