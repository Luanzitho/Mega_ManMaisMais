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
	return; //Ele não se move no jogo
}

void Metall::danificar(Megaman* p)
{
	p->num_vidas = p->num_vidas-1;
}

std::string Metall::getTextureFile()
{
	return "Sprites/Inimigos/Metall.png";
}