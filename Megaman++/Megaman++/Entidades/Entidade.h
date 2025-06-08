#pragma once

#include "../Ente.h"

class Entidade:public Ente
{
protected:
	bool destruido;
	//float x;
	//float y;
	//ostream buffer;

public:
	Entidade();
	~Entidade();
	virtual void executar(float dt) = 0;
	virtual std::string getTextureFile() = 0;
	//virtual void salvar() = 0;

	//void salvarDataBuffer(); 
};