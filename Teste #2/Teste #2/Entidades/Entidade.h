#pragma once
#include <ostream>
#include "../Ente.h"

class Entidade:public Ente
{
protected:
	int x;
	int y;
	//(...)
	//ostream buffer;

public:
	Entidade();
	virtual ~Entidade();
	virtual void executar() = 0;
	virtual void salvar() = 0;
	//(..)
	void salvarDataBuffer();
};

