#pragma once
#include "Inimigo.h"
class Metall:public Inimigo //Equivalente a Inimigo_facil
{
private:


public:
	Metall();
	~Metall();
	void executar(float dt);
	void mover(float dt);
	//void danificar(Megaman* p);
	//void esconder();
	std::string getTextureFile();
};

