#pragma once

#include "Obstaculo.h"

class Plataforma:public Obstaculo
{
private:
	int largura;

public:
	Plataforma();
	~Plataforma();
	void executar();
	void obstaculizar(Personagem* pPers);
	std::string getTextureFile();
};

