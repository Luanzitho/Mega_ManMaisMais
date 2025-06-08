#pragma once

#include "Inimigo.h"
#include "Megaman.h"

class Metall:public Inimigo //Equivalente a Inimigo_facil
{
private:
	float cooldownEsconder;

public:
	Metall();
	~Metall();
	void executar(float dt);
	void mover(float dt);
	void danificar(Megaman* p);
	//void esconder();
	std::string getTextureFile();
};

