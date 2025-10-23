#pragma once

#include "Lista.h"
#include "../Entidades/Entidade.h"

class Megaman;
class Inimigo;
class Item;

class ListaEntidades
{
private:
	Lista<Entidade> LEs;

public:
	ListaEntidades();
	~ListaEntidades();
	void limpar();
	void incluirEntidade(Entidade* pE);
	std::vector<Item*> getItensDaLista();
	void redefinirAlvo(Megaman* pM); //Caso o player 1 morra, o player 2 assume o controle
	void percorrer(float dt, sf::Vector2f tam);
	void verificaAbatidos();
	void salvarEntidades();
	void carregaEntidades();
	//Lista<> get
};

