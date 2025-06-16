#pragma once

#include "Fase.h"

class Fase;

class Fase2 : public Fase
{
private:
	int minInimigosMedios;
	int maxChefoes;
public:
	//const int maxChefoes;
	Fase2();
	~Fase2();
	void executar(float dt);
	void criarChefoes();
	void criarObsMedios();
	void criarMinInimigosMedios();
	void criarProjeteis();
	void criarInimigos();
	void criarObstaculos();
};