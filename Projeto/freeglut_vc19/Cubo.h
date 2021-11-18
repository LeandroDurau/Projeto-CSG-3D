#pragma once
class Cubo
{
public:
	float a = 0;
	float tri[36][3];
public:
	Cubo();
	void setValores(float aresta);
	void Desenha();
	~Cubo();
};

