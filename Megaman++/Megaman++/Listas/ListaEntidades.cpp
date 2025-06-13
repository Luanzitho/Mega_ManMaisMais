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

void ListaEntidades::percorrer(float dt, sf::Vector2f tam)
{
    if (LEs.getpPrimeiro()) {
        Lista<Entidade>::Elemento<Entidade>* aux = LEs.getpPrimeiro();
        sf::FloatRect rect2(sf::Vector2f(0.f,0.f), tam);
        while (aux != nullptr)
        {
            Entidade* pEntidade = aux->getInfo();
            sf::FloatRect rect1(pEntidade->getCoords(), pEntidade->getTamanho());

            if (rect1.intersects(rect2) && pEntidade) { //Houve colisão
                pEntidade->executar(dt);
                pEntidade->desenhar();
            }
            aux = aux->getProximo();
        }
    }
    verificaAbatidos();
}

void ListaEntidades::verificaAbatidos()
{
    // 2. Marca entidades mortas para remoção
    std::vector<Entidade*> paraRemover;
    Lista<Entidade>::Elemento<Entidade>* aux = LEs.getpPrimeiro();
    while (aux != nullptr)
    {
        Entidade* pEntidade = aux->getInfo();
        if (pEntidade && !pEntidade->getVivo())
            paraRemover.push_back(pEntidade);

        aux = aux->getProximo();
    }
    // 3. Remove entidades marcadas
    for (Entidade* pEntidade : paraRemover)
    {
        LEs.remover(pEntidade);
        delete pEntidade; // Se você for responsável por deletar a entidade
    }
}


