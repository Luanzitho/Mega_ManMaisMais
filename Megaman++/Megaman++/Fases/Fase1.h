#pragma once

#include "Fase.h"

class Fase;

class Fase1 : public Fase
{
private:

public:
	const int maxChefoes;
	Fase1();
	~Fase1();
	void executar(float dt);
	void criarChefoes();
	void criarObsMedios();
	void criarProjeteis();
	void criarInimigos();
	void criarObstaculos();
	//std::string getMapaFase();
};