#include "Item.h"

Item::Item()
{
	direita = true;
	noChao = false;
	velVertical -= 25;
}

Item::~Item()
{
}

void Item::salvar()
{
	Entidade::salvar();
}

void Item::carregar()
{
	Entidade::carregar();
}