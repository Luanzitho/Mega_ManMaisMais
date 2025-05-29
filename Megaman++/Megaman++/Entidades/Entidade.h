#pragma once

#include "../Ente.h"

class Entidade:public Ente
{
protected:
	//float x;
	//float y;
	//ostream buffer;

public:
	Entidade();
	~Entidade();
	virtual void executar() = 0;
	virtual std::string getTextureFile() = 0;
	//virtual void salvar() = 0;

	//void salvarDataBuffer(); 
};