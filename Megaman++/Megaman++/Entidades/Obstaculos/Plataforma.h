#pragma once

#include "Obstaculo.h"

class Plataforma:public Obstaculo
{
private:
	int altura;

public:
	Plataforma();
	~Plataforma();
	void executar(float dt);
	void obstaculizar(Personagem* pPers);
	std::string getTextureFile();
};

