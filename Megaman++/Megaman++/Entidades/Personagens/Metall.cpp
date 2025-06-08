#include "Metall.h"

Metall::Metall()
{
	setNumVidas(2);

	setTamanho(sf::Vector2f(50.f, 50.f));
}

Metall::~Metall()
{
}

void Metall::executar(float dt)
{
	//esconder()
}

void Metall::mover(float dt)
{
	return; //Ele não se move no jogo
}

void Metall::danificar(Megaman* p)
{
	p->operator--();
}

std::string Metall::getTextureFile()
{
	return "Sprites/Inimigos/Metall.png";
}