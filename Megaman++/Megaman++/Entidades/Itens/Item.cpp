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
	Entidade::salvar();
	//dadosSalvos["id"][dadosSalvos["id"][lugar].size() - 1]["altura"] = altura;
	//dadosSalvos["id"][dadosSalvos["id"][lugar].size() - 1]["larura"] = largura;
	//dadosSalvos["id"][dadosSalvos["id"][lugar].size() - 1]["timerDespawn"] = timerDespawn;
}

void Item::carregar()
{
	Entidade::carregar();
	//altura = dadosSalvos["id"][indiceAtual]["altura"];
	//largura = dadosSalvos["id"][indiceAtual]["largura"];
	//timerDespawn = dadosSalvos["id"][indiceAtual]["timerDespawn"];
}