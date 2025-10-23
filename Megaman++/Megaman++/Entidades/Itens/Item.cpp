#include "Item.h"

Item::Item()
{
	direita = true;
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