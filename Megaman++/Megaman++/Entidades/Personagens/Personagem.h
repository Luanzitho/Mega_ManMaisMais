#pragma once

#include "../Entidade.h"

class Entidade;

class Personagem:public Entidade
{
protected:
	int num_vidas;
	static int qualPersonagem;

public:
	Personagem();
	Personagem(int v);
	~Personagem();
	void curar(const int hp);
	virtual void machucar(const int dmg);
	void setNumVidas(const int v);
	int getNumVidas();
	virtual void mover(float dt) = 0;
	virtual void executar(float dt) = 0;
	virtual std::string getTextureFile() = 0;
	virtual void salvar();
	virtual void carregar();
};