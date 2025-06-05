#pragma once

#include "Lista.h"
#include "../Entidades/Entidade.h"

class ListaEntidades
{
public: //private:
	Lista<Entidade> LEs;

public:
	ListaEntidades();
	~ListaEntidades();
	void incluirEntidade(Entidade* pE);
	void percorrer(float dt);
};

