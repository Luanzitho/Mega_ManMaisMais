#include "Entidade.h"

Entidade::Entidade(): vivo(true), gravidade(300), executando(false), direita(false), velocidade(0), velVertical(0), velMax(0), noChao(false)//x(-1), y(-1)
{
}

Entidade::~Entidade()
{
}

void Entidade::destruir()
{
	vivo = false;
}

const bool Entidade::getVivo()
{
	return vivo;
}

void Entidade::setVelocidade(const float v)
{
	velocidade = v;
}

float Entidade::getVelocidade()
{
	return velocidade;
}

void Entidade::setVelVertical(const float v)
{
	velVertical = v;
}

float Entidade::getVelVertical()
{
	return velVertical;
}

void Entidade::setNoChao(const bool noChao)
{
	this->noChao = noChao;
}

const bool Entidade::getNoChao()
{
	return noChao;
}

void Entidade::sofrerAcaoDaGravidade(float dt)
{
	velVertical += gravidade * dt;
}

const bool Entidade::getExecutando()
{
	return executando;
}

void Entidade::setExecutando(const bool exe)
{
	executando = executando;
}
