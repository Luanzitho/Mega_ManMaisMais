#include "ProjetilMegaman.h"

ProjetilMegaman::ProjetilMegaman()
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

void ProjetilMegaman::mover(float dt)
{
	sf::Vector2f posicao;
	posicao = getCoords();

	posicao.x += direcao * velocidade * dt;

	setCoords(posicao);
}

void ProjetilMegaman::executar(float dt)
{
	mover(dt);
}

std::string ProjetilMegaman::getTextureFile()
{
	return "Sprites/Projeteis/ProjetilMegaman.png";
}