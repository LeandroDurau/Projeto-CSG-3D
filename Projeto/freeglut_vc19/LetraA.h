#pragma once
class LetraA
{
public:
	float a;
	float b;
	float tri[18][3];
public:
	LetraA();
	void setValores(float aresta, float grosura);
	void Desenha();
	~LetraA();
};

