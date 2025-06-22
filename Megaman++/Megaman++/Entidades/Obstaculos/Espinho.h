#pragma once

#include "Obstaculo.h"

class Espinho:public Obstaculo
{
private:
	short int danosidade;
	static int indiceEspinho;

public:
	Espinho();
	~Espinho();
	void executar(float dt);
	void obstaculizar(Personagem* pPers);
	std::string getTextureFile();
	void salvar();
	void carregar();
};

