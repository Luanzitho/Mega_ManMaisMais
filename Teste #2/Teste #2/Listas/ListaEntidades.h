#pragma once
#include "Lista.h"

class Entidade;

class ListaEntidades
{
private:
	Lista<Entidade> LEs;
	//(...)

public:
	//int tam; Talvez?
	ListaEntidades();
	~ListaEntidades();
	void incluir(Entidade* pE);
	void percorrer();
	//(...)
};

