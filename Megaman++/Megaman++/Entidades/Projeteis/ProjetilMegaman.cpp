#include "ProjetilMegaman.h"

ProjetilMegaman::ProjetilMegaman(): direcao(0)
{
}

ProjetilMegaman::ProjetilMegaman(sf::Vector2f posicao, bool direita): Projetil()
{
	if (direita)
		direcao = 1;
	else
		direcao = -1;

	setCoords(posicao);
	setTamanho(sf::Vector2f(15.f, 15.f));
}

ProjetilMegaman::~ProjetilMegaman()
{
}
#include <iostream>
void ProjetilMegaman::mover(float dt)
{
	if (getAtivo()) {
		sf::Vector2f posicao;
		posicao = getCoords();

		posicao.x += direcao * velocidade * dt;
		setCoords(posicao);
	}
}

void ProjetilMegaman::executar(float dt)
{
	mover(dt);
	/*if (getCoords().x > 1100 || getCoords().x < 100) {
		desativar();
	}*/
}

std::string ProjetilMegaman::getTextureFile()
{
	return "Sprites/Projeteis/ProjetilMegaman.png";
}