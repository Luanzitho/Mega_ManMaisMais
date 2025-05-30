#pragma once
#include "Inimigo.h"
class Metall:public Inimigo //Equivalente a Inimigo_facil
{
private:


public:
	Metall();
	~Metall();
	void executar();
	void mover();
	//void danificar(Megaman* p);
	//void esconder();
	std::string getTextureFile();
};

