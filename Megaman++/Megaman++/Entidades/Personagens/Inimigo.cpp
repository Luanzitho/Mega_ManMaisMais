#include "Inimigo.h"

Inimigo::Inimigo(): nivel_maldade(0), pMega(nullptr)
{
	setId(2);
}

Inimigo::~Inimigo()
{
}

void Inimigo::conhecerJogador(Megaman* p)
{
	pMega = p;
}