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