#include "Personagem.h"

Personagem::Personagem(): num_vidas(0), noChao(false), direita(true), velocidade(0), velVertical(0)
{
}

Personagem::Personagem(int v): num_vidas(v) //Acho até q dá pra remover hein
{
}

Personagem::~Personagem()
{
}

void Personagem::curar(int hp)
{
	num_vidas = num_vidas + hp;
}

void Personagem::machucar(int dmg)
{
	num_vidas = num_vidas - dmg;

	if (num_vidas <= 0)
		destruir();
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