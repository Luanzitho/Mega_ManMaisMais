#include "Personagem.h"

Personagem::Personagem(): num_vidas(0)
{
}

Personagem::Personagem(int v):num_vidas(v) //Acho que dá para remover isso, agora que tem setNumVidas, dai so usar na construtora dos personagens
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
