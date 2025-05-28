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
	void mover();
	void executar();
	//void setTextureFile();
	std::string getTextureFile();
};