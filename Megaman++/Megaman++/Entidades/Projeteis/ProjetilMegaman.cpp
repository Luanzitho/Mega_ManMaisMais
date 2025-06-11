#include "ProjetilMegaman.h"
#include "../Personagens/Inimigo.h"

ProjetilMegaman::ProjetilMegaman(): direcao(0)
{
	doMega = true;
	dano = 1;
}

ProjetilMegaman::ProjetilMegaman(sf::Vector2f posicao, bool direita): Projetil()
{
	if (direita)
		direcao = 1;
	else
		direcao = -1;

	doMega = true;
	dano = 1;

	setCoords(posicao);
	setTamanho(sf::Vector2f(30.f, 30.f));
}

ProjetilMegaman::~ProjetilMegaman()
{
}

void ProjetilMegaman::atingirInimigo(Inimigo* pI)
{
	if (!pI) return;

	pI->machucar(dano);
	destruir();
}

void ProjetilMegaman::mover(float dt)
{
	if (getVivo()) {
		sf::Vector2f posicao;
		posicao = getCoords();

		posicao.x += direcao * velocidade * dt;
		setCoords(posicao);
	}
}

void ProjetilMegaman::executar(float dt)
{
	mover(dt);
}

std::string ProjetilMegaman::getTextureFile()
{
	return "Sprites/Projeteis/ProjetilMegaman.png";
}