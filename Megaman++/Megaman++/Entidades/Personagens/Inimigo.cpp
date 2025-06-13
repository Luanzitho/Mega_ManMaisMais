#include "Inimigo.h"

Inimigo::Inimigo(): pMega(nullptr), dano(0)
{
	srand(time(NULL));

	setId(2);

	nivel_maldade = rand() % 3 + 1;
}

Inimigo::~Inimigo()
{
}

void Inimigo::conhecerJogador(Megaman* p)
{
	pMega = p;
}