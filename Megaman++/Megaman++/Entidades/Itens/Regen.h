#pragma once
#include "Item.h"
#include <random>

#define TEMPO_DESPAWN 5

class Item;
class Megaman;

class Regen:public Item
{
private:
	float regenAmount;
	int tipoRegen;
	std::random_device rd;
	ListaEntidades* LE;
	Gerenciador_Colisoes* GC;
	static int indiceRegen;

public:
	Regen();
	~Regen();
	void executar(float dt);
	void regenerar(Megaman* p);
	std::string getTextureFile();
	void serPego(Megaman* p);
	void mover(float dt);
	int getFrame();
	sf::Vector2f getEscalaCorreta();
	void associaListaEntidades(ListaEntidades* pLista);
	void associaGerenciadorColisoes(Gerenciador_Colisoes* gc);
	void salvar();
	void carregar();
};

