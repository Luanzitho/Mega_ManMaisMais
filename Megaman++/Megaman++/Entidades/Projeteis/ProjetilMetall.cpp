#include "ProjetilMetall.h"
#include "../Personagens/Megaman.h"

ProjetilMetall::ProjetilMetall(): direcao(0)
{
	doMega = false;
	dano = 2;
}

ProjetilMetall::ProjetilMetall(sf::Vector2f posicao, bool direita): Projetil()
{
	if (direita)
		direcao = 1;
	else
		direcao = -1;

	doMega = false;
	dano = 2;

	setCoords(posicao);
	setTamanho(sf::Vector2f(30.f, 30.f));	
}

ProjetilMetall::~ProjetilMetall(){}

void ProjetilMetall::atingirMegaman(Megaman* p)
{
	if (!p) return;

	p->machucar(dano);
	destruir();
}

void ProjetilMetall::mover(float dt)
{
	if (getVivo()) {
		sf::Vector2f posicao;
		posicao = getCoords();

		posicao.x += direcao * velocidade * dt;
		setCoords(posicao);
	}
}

void ProjetilMetall::executar(float dt)
{
	mover(dt);
}

std::string ProjetilMetall::getTextureFile()
{
	return "Sprites/Projeteis/ProjetilMetall.png";
}