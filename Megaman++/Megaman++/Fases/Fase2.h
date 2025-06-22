#pragma once

#include "Fase.h"

class Fase;

class Fase2 : public Fase
{
private:
	int maxChefoes;
	int minEspinhos;
public:
	//const int maxChefoes;
	Fase2();
	~Fase2();
	void executar(float dt);
	void criarChefoes();
	void criarEspinhos();
	void criarInimigos();
	void criarObstaculos();
	void salvar();
	void carregar();
};