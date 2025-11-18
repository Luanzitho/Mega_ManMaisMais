#include "Item.h"

Item::Item(): altura(16), largura(16), timerDespawn(0)
{
	direita = true;
	noChao = false;
}

Item::~Item()
{
}

void Item::salvar()
{
	int lugar = getId();
	dadosSalvos["id"][dadosSalvos["id"][lugar].size() - 1]["altura"] = altura;
	dadosSalvos["id"][dadosSalvos["id"][lugar].size() - 1]["larura"] = largura;
	dadosSalvos["id"][dadosSalvos["id"][lugar].size() - 1]["timerDespawn"] = timerDespawn;
	Entidade::salvar();
}

void Item::carregar()
{
	int lugar = getId();
	altura = dadosSalvos["id"][lugar][indiceAtual]["altura"];
	largura = dadosSalvos["id"][lugar][indiceAtual]["largura"];
	timerDespawn = dadosSalvos["id"][lugar][indiceAtual]["timerDespawn"];
	Entidade::carregar();
}