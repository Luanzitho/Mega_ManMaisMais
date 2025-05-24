#pragma once
#include "Personagem.h"

class Jogador:public Personagem
{
private:
	int pontos;
	//(...)

public:
	Jogador();
	~Jogador();
	void executar();
	//(...)
};

