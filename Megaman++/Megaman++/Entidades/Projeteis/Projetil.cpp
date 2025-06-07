#include "Projetil.h"

Projetil::Projetil(): ativo(true), velocidade(500), dano(1)
{
	LEs = nullptr;
}

Projetil::~Projetil()
{
}

void Projetil::desativar()
{
	ativo = false;
	velocidade = 0;
}

const bool Projetil::getAtivo()
{
	return ativo;
}

void Projetil::associaListaEntidades(ListaEntidades* pLista)
{
	LEs = pLista;
}