#include "ListaEntidades.h"

ListaEntidades::ListaEntidades(){}

ListaEntidades::~ListaEntidades(){}

void ListaEntidades::incluir(Entidade* pE)
{
	if(pE) //Testando se não é um ponteiro vazio
		LEs.incluir(pE);
}

void ListaEntidades::percorrer()
{
	//Entidade* pE=LEs.
	//for (int i = 0; i<LEs.getTam(); i++)
}
