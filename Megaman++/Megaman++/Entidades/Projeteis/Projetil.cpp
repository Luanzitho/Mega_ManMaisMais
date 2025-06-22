#include "Projetil.h"

Projetil::Projetil(): velocidade(0), dano(0), doMega(false), empuxo(300)
{
	LEs = nullptr;
}

Projetil::Projetil(const float vel, const int dmg): velocidade(vel), dano(dmg), empuxo(300)
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

void Projetil::salvar()
{
	int lugar = getId();
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()-1]["doMega"] = doMega;
	Entidade::salvar();
}

void Projetil::carregar()
{
	int lugar = getId();
	doMega = dadosSalvos["id"][lugar][indiceAtual]["doMega"];
	Entidade::carregar();
}