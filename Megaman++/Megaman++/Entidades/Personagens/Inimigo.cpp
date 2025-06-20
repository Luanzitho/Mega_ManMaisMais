#include "Inimigo.h"

Inimigo::Inimigo() : pMega(nullptr), dano(0), LE(nullptr), GC(nullptr)
{
	srand(time(NULL));

	setId(2);

	nivel_maldade = rand() % 3 + 1;

	qtdPontos = nivel_maldade * 100; //Cada nível de maldade do inimigo resulta em 100 pontos a mais para a quantidade padrão de pontos
}

Inimigo::~Inimigo()
{
	LE = nullptr;
	GC = nullptr;
	pMega = nullptr;
}

void Inimigo::conhecerJogador(Megaman* p)
{
	pMega = p;
}

void Inimigo::machucar(const int dmg)
{
	num_vidas = num_vidas - dmg;

	if (num_vidas <= 0)
	{
		cederPontos();
		destruir();
	}
}

void Inimigo::cederPontos()
{
	(*pMega) += qtdPontos;
}

void Inimigo::associaListaEntidades(ListaEntidades* pLista)
{
	LE = pLista;
}

void Inimigo::associaGerenciadorColisoes(Gerenciador_Colisoes* gc)
{
	GC = gc;
}