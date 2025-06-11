#pragma once

#include "Projetil.h"

class Megaman;

class ProjetilMetall:public Projetil
{
private:
	int direcao;

public:
	ProjetilMetall();
	ProjetilMetall(sf::Vector2f posicao, bool direita);
	~ProjetilMetall();
	void atingirMegaman(Megaman* p);
	void mover(float dt);
	void executar(float dt);
	std::string getTextureFile();
};

