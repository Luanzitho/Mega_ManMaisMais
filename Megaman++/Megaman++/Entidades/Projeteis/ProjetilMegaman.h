#pragma once

#include "Projetil.h"

class Inimigo;

class ProjetilMegaman:public Projetil
{
private:
	float direcao;

public:
	ProjetilMegaman();
	ProjetilMegaman(sf::Vector2f posicao, bool direita);
	~ProjetilMegaman();
	void atingirInimigo(Inimigo* pI);
	void mover(float dt);
	void executar(float dt);
	std::string getTextureFile();
};

