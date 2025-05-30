#pragma once
#include "Personagem.h"
#include "Megaman.h"

class Inimigo:public Personagem
{
protected:
	int nivel_maldade;

public:
	Inimigo();
	~Inimigo();
	//void salvarDataBuffer();
	virtual void mover() = 0;
	virtual void executar() = 0;
	//virtual void danificar() = 0;
	virtual std::string getTextureFile() = 0;
};

