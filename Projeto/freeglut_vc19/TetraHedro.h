#pragma once
# define PI 3.141592653589793238462643383279502884L /* pi */
class TetraHedro
{
public:
	float pcx, pcy, pcz;
	float a;       // aresta
	int id;
	float t1[3][3]; // triângulo que forma a face 1 (3 vértices - x,y,z)
	float t2[3][3];
	float t3[3][3];
	float t4[3][3];

public:
	TetraHedro(int idC, float ppcx, float ppcy, float ppcz, float aa);
	void Desenha();
	~TetraHedro();
};

