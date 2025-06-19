#include "Inimigo.h"

Inimigo::Inimigo() : pMega(nullptr), dano(0), LE(nullptr), GC(nullptr)
{
	srand(time(NULL));

	setId(2);

	nivel_maldade = rand() % 3 + 1;

	qtdPontos = nivel_maldade * 100; //Cada nível de maldade do inimigo resulta em 100 pontos a mais para a quantidade padrão de cada tipo de inimigo
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

void Inimigo::machucar(int dmg)
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
	pMega->addPontos(qtdPontos);
}

void Inimigo::associaListaEntidades(ListaEntidades* pLista)
{
	LE = pLista;
}

void Inimigo::associaGerenciadorColisoes(Gerenciador_Colisoes* gc)
{
	GC = gc;
}