#include "Personagem.h"

Personagem::Personagem(): num_vidas(0), noChao(false), velocidade(0), velVertical(0)
{
}

Personagem::Personagem(int v): num_vidas(v)
{
}

Personagem::~Personagem()
{
}

void Personagem::operator++()
{
	num_vidas++;
}

void Personagem::operator--()
{
	num_vidas--;
}

void Personagem::setNumVidas(int v)
{
	num_vidas = v;
}

int Personagem::getNumVidas()
{
	return num_vidas;
}

void Personagem::setVelocidade(float v)
{
	velocidade = v;
}

float Personagem::getVelocidade()
{
	return velocidade;
}

void Personagem::setVelVertical(float v)
{
	velVertical = v;
}

float Personagem::getVelVertical()
{
	return velVertical;
}

void Personagem::setNoChao(bool noChao)
{
	this->noChao = noChao;
}

bool Personagem::getNoChao()
{
	return noChao;
}