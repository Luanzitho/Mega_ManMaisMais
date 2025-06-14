#include "Projetil.h"

Projetil::Projetil(): velocidade(0), dano(0), doMega(false), empuxo(0)
{
	LEs = nullptr;
}

Projetil::Projetil(float vel): velocidade(vel)
{
}

Projetil::~Projetil()
{
}

const bool Projetil::getDoMega()
{
	return doMega;
}

void Projetil::associaListaEntidades(ListaEntidades* pLista)
{
	LEs = pLista;
}