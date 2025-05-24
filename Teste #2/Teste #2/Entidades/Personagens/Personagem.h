#pragma once
#include "../Entidade.h"

class Personagem:public Entidade
{
protected:
	int num_vidas;
	//(...)

public:
	Personagem();
	~Personagem();
	void salvarDataBuffer();
	virtual void mover();
	virtual void executar() = 0;
	//(...)
};

