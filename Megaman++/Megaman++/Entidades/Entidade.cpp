#include "Entidade.h"

Entidade::Entidade(): vivo(true)//: x(-1), y(-1)
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
