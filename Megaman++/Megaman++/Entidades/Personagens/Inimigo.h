#pragma once

#include "Personagem.h"
#include "Megaman.h"
#include <time.h>

class Inimigo:public Personagem
{
protected:
	int nivel_maldade;
	int dano;
	Megaman* pMega;

public:
	Inimigo();
	~Inimigo();
	//void salvarDataBuffer();
	void conhecerJogador(Megaman* p);
	virtual void mover(float dt) = 0;
	virtual void executar(float dt) = 0;
	virtual void danificar(Megaman* p) = 0;
	virtual std::string getTextureFile() = 0;
};