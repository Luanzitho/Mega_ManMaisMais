#pragma once

#include "Projetil.h"

class ProjetilMegaman:public Projetil
{
private:
	float direcao;

public:
	ProjetilMegaman();
	ProjetilMegaman(sf::Vector2f posicao, bool direita);
	~ProjetilMegaman();
	void mover(float dt);
	void executar(float dt);
	std::string getTextureFile();
};

