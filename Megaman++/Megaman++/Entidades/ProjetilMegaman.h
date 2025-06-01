#pragma once

#include "Projetil.h"

class ProjetilMegaman:public Projetil
{
protected:
	float direcao;

public:
	ProjetilMegaman();
	ProjetilMegaman(sf::Vector2f posicao, bool direita);
	~ProjetilMegaman();
	void mover(float dt);
	virtual void executar(float dt);
	virtual std::string getTextureFile() override;
};

