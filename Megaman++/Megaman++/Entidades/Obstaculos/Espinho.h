#pragma once

#include "Obstaculo.h"

class Espinho:public Obstaculo
{
private:
	short int danosidade;

public:
	Espinho();
	~Espinho();
	void executar(float dt);
	void obstaculizar(Personagem* pPers);
	std::string getTextureFile();
};

