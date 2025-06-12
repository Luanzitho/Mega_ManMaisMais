#include "Entidade.h"

Entidade::Entidade(): vivo(true), gravidade(300)//: x(-1), y(-1)
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
