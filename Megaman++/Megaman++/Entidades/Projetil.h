#pragma once

#include "Entidade.h"

class Projetil:public Entidade
{
protected:
	bool ativo;
	int dano;
	float velocidade;

public:
	Projetil();
	~Projetil();
	virtual void executar(float dt) = 0;
	virtual std::string getTextureFile() = 0;
};

