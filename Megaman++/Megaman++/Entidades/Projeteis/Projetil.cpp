#include "Projetil.h"

Projetil::Projetil(): velocidade(500), dano(0), doMega(false)
{
	LEs = nullptr;
}

Projetil::~Projetil()
{
}

//void Projetil::desativar()
//{
//	ativo = false;
//	velocidade = 0;
//}

//const bool Projetil::getAtivo()
//{
//	return ativo;
//}

const bool Projetil::getDoMega()
{
	return doMega;
}

void Projetil::associaListaEntidades(ListaEntidades* pLista)
{
	LEs = pLista;
}