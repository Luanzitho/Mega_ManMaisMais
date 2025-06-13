#include "Entidade.h"

Entidade::Entidade(): vivo(true), gravidade(300), executando(false)//: x(-1), y(-1)
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
void Entidade::setVelocidade(float v)
{
	velocidade = v;
}

float Entidade::getVelocidade()
{
	return velocidade;
}

void Entidade::setVelVertical(float v)
{
	velVertical = v;
}

float Entidade::getVelVertical()
{
	return velVertical;
}

void Entidade::setNoChao(bool noChao)
{
	this->noChao = noChao;
}

bool Entidade::getNoChao()
{
	return noChao;
}

bool Entidade::getExecutando()
{
	return executando;
}

void Entidade::setExecutando(bool exe)
{
	executando = executando;
}
