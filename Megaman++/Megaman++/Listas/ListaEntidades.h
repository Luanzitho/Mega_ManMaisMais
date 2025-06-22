#pragma once

#include "Lista.h"
#include "../Entidades/Entidade.h"

class ListaEntidades
{
private:
	Lista<Entidade> LEs;

public:
	ListaEntidades();
	~ListaEntidades();
	void limpar();
	void incluirEntidade(Entidade* pE);
	void percorrer(float dt, sf::Vector2f tam);
	void verificaAbatidos();
	void salvarEntidades();
	void carregaEntidades();
	//Lista<> get
};

