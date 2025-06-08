#pragma once

#include "Inimigo.h"
#include "Megaman.h"

class Metall:public Inimigo //Equivalente a Inimigo_facil
{
private:
	float timerEsconder;
	float timerAtirar;

public:
	Metall();
	~Metall();
	void executar(float dt);
	void mover(float dt);
	void danificar(Megaman* p);
	//atirar();
	//void esconder();
	std::string getTextureFile();
};

