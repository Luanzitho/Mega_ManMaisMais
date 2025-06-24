#pragma once

#include "Fase.h"

class Fase;

class Fase1 : public Fase
{
private:
	int minBigEyes;
	int minMolas;

public:
	Fase1();
	~Fase1();
	void executar(float dt);
	void criarMolas();
	void criarBigEyes();
	void criarInimigos();
	void criarObstaculos();
	void salvar();
	void carregar();
};