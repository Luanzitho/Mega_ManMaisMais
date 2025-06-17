#pragma once

#include "Fase.h"

class Fase;

class Fase1 : public Fase
{
private:
	int minInimigosMedios;
public:
	Fase1();
	~Fase1();
	void executar(float dt);
	void criarMolas();
	void criarMinInimigosMedios();
	void criarProjeteis();
	void criarInimigos();
	void criarObstaculos();
};