#include "Projetil.h"

Projetil::Projetil(): velocidade(0), dano(0), doMega(false), empuxo(300)
{
	LEs = nullptr;
}

Projetil::Projetil(const float vel, int dmg): velocidade(vel), dano(dmg), empuxo(300)
{
}

Projetil::~Projetil()
{
	LEs = nullptr;
}

const bool Projetil::getDoMega()
{
	return doMega;
}

void Projetil::associaListaEntidades(ListaEntidades* pLista)
{
	LEs = pLista;
}