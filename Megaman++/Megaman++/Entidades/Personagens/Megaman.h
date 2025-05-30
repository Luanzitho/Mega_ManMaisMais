#pragma once
#include "Personagem.h"

class Megaman:public Personagem
{
private:
	bool player1;
	sf::Texture textura;
	int pontos;

public:
	Megaman();
	Megaman(bool player);
	~Megaman();
	void mover();
	//void atirar();
	void executar();
	std::string getTextureFile();
};

