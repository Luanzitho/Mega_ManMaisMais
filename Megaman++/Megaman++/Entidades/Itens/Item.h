#pragma once
#include "../Entidade.h"

class ListaEntidades;
class Megaman;
class Gerenciador_Colisoes;

class Item:public Entidade
{
protected:
	float altura;
	float largura;
	float timerDespawn;

public:
	Item();
	~Item();
	virtual void executar(float dt) = 0;
	virtual std::string getTextureFile() = 0;
	virtual void serPego(Megaman* p) = 0;
	virtual void mover(float dt) = 0;
	virtual int getFrame() = 0;
	virtual sf::Vector2f getEscalaCorreta() = 0;
	virtual void associaListaEntidades(ListaEntidades* pLista) = 0;
	virtual void associaGerenciadorColisoes(Gerenciador_Colisoes* gc) = 0;
	virtual void salvar();
	virtual void carregar();
};

