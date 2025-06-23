#include "Projetil.h"

Projetil::Projetil(): dano(0), doMega(false), empuxo(300)
{
	LEs = nullptr;
}

Projetil::Projetil(const float vel, const int dmg): dano(dmg), empuxo(300)
{
	velocidade = vel;
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
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["dano"] = dano;
	//dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["velocidade"] = velocidade;

	Entidade::salvar();
}

void Projetil::carregar()
{
	int lugar = getId();
	doMega = dadosSalvos["id"][lugar][indiceAtual]["doMega"];
	dano = dadosSalvos["id"][lugar][indiceAtual]["dano"];
	//velocidade = dadosSalvos["id"][lugar][indiceAtual]["velocidade"];

	Entidade::carregar();
}