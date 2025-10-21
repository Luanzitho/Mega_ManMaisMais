#pragma once
#include "Item.h"
#include <random>

class Item;
class Megaman;

class Regen:public Item
{
private:
	float regenAmount;
	float timerDespawn;
	int tipoRegen;
	std::random_device rd;
	ListaEntidades* LE;
	Gerenciador_Colisoes* GC;

public:
	Regen();
	~Regen();
	void executar(float dt);
	void regenerar(Megaman* p);
	std::string getTextureFile();
	void serPego(Megaman* p);
	void mover(float dt);
	void associaListaEntidades(ListaEntidades* pLista);
	void associaGerenciadorColisoes(Gerenciador_Colisoes* gc);
	void salvar();
	void carregar();
};

