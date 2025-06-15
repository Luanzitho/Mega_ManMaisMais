#include "Inimigo.h"

Inimigo::Inimigo() : pMega(nullptr), dano(0), LE(nullptr), GC(nullptr)
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
void Inimigo::associaListaEntidades(ListaEntidades* pLista)
{
	LE = pLista;
}

void Inimigo::associaGerenciadorColisoes(Gerenciador_Colisoes* gc)
{
	GC = gc;
}