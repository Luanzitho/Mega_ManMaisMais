#include "Personagem.h"

Personagem::Personagem(): num_vidas(0)
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
