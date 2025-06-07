#pragma once

#include "../Entidade.h"

class Entidade;

class Personagem:public Entidade
{
protected:
	int num_vidas;
	float velocidade;
	float velVertical;
	bool noChao;

public:
	Personagem();
	Personagem(int v);
	~Personagem();
	void operator++();
	void operator--();
	void setNumVidas(int v); //Talvez acabe sendo removido
	int getNumVidas(); //Talvez acabe sendo removido
	void setVelocidade(float v);
	float getVelocidade();
	void setVelVertical(float v);
	float getVelVertical();
	virtual void mover(float dt) = 0;
	virtual void executar(float dt) = 0;
	void setNoChao(bool noChao);
	bool getNoChao();
	virtual std::string getTextureFile() = 0;
};