#pragma once
#ifndef _ENTIDADE_H_
#define _ENTIDADE_H_

#include "../Ente.h"

class Entidade:public Ente
{
protected:
	int x;
	int y;
	//ostream buffer;

private:
	Entidade();
	Entidade(int xI, int yI); //Essa construtora recebe as coordenadas iniciais da Entidade como parâmetro
	~Entidade();
	virtual void executar() = 0;
	//virtual void salvar() = 0;

	//void salvarDataBuffer(); 
};

#endif // _ENTIDADE_H_