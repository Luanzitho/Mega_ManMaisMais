#include "Projetil.h"

Projetil::Projetil(): velocidade(0), dano(0), doMega(false), empuxo(300)
{
	LEs = nullptr;
}

Projetil::Projetil(const float vel): velocidade(vel)
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