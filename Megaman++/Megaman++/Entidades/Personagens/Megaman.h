#pragma once
#include "Personagem.h"

class Megaman:public Personagem
{
private:
	bool player1;

public:
	Megaman();
	Megaman(bool novoPlayer);
	~Megaman();
	void mover();
	void executar();
	std::string getTextureFile();
	//void atirar();
};

