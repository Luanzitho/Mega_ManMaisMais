#include "Metall.h"

Metall::Metall()
{
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
	return; //Ele n�o se move no jogo
}

void Metall::danificar(Megaman* p)
{
	p->operator--();
}

std::string Metall::getTextureFile()
{
	return "Sprites/Inimigos/Metall.png";
}