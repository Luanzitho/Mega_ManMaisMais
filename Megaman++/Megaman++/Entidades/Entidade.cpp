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

bool Entidade::getExecutando()
{
	return executando;
}

void Entidade::setExecutando(bool exe)
{
	executando = executando;
}
