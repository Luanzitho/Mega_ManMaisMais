#pragma once

#include "../Entidade.h"

class Entidade;

class Personagem:public Entidade
{
protected:
	int num_vidas;
	float velocidade;
	float velVertical;
	float aceleracao;
	float gravidade;
	float velMax;

public:
	Personagem();
	Personagem(int v);
	~Personagem();
	virtual void mover(float dt) = 0;
	virtual void executar(float dt) = 0;
	virtual std::string getTextureFile() = 0;
};