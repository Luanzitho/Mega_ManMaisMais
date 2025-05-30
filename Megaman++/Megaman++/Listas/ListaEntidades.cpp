#include "ListaEntidades.h"

ListaEntidades::ListaEntidades()
{
}

ListaEntidades::~ListaEntidades()
{
}

void ListaEntidades::incluirEntidade(Entidade* pE)
{
	if (pE)
		LEs.incluir(pE);
}

void ListaEntidades::percorrer()
{
    Lista<Entidade>::Elemento<Entidade>* aux = LEs.getpPrimeiro();

    while (aux != nullptr)
    {
        Entidade* pEntidade = aux->getInfo();
        if (pEntidade)
        {
            pEntidade->executar();
            pEntidade->desenhar();
        }

        aux = aux->getProximo();
    }
}
