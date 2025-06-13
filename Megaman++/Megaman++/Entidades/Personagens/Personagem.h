#pragma once

#include "../Entidade.h"

class Entidade;

class Personagem:public Entidade
{
protected:
	int num_vidas;
	
public:
	Personagem();
	Personagem(int v);
	~Personagem();
	void curar(int hp);
	virtual void machucar(int dmg);
	void setNumVidas(int v); //Talvez acabe sendo removido
	int getNumVidas(); //Talvez acabe sendo removido
	virtual void mover(float dt) = 0;
	virtual void executar(float dt) = 0;
	virtual std::string getTextureFile() = 0;
};