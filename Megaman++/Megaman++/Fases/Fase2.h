#pragma once

#include "Fase.h"

class Fase;

class Fase2 : public Fase
{
private:
	int maxCutMan;
	int minEspinhos;

public:
	Fase2();
	~Fase2();
	void executar(float dt);
	void criarCutMan();
	void criarEspinhos();
	void criarInimigos();
	void criarObstaculos();
	void salvar();
	void carregar();
};