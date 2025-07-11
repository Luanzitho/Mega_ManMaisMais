#include "Gerenciador_Colisoes.h"
//#include <iostream>

Gerenciador_Colisoes::Gerenciador_Colisoes()
{
    LIs.clear();
    LOs.clear();
    LPs.clear();

    p1 = nullptr;
    p2 = nullptr;
}

Gerenciador_Colisoes::~Gerenciador_Colisoes()
{
    LIs.clear();
    LOs.clear();
    LPs.clear();

	p1 = nullptr;
    p2 = nullptr;
}

const bool Gerenciador_Colisoes::verificarColisao(Entidade* pE1, Entidade* pE2) //Refer�ncia: Giu do PETECO
{
    sf::FloatRect rect1(pE1->getCoords(), pE1->getTamanho());
    sf::FloatRect rect2(pE2->getCoords(), pE2->getTamanho());

    if (rect1.intersects(rect2)) //Se true, houve colis�o
    { 
        return true;
    }
    return false; //Se chegou aqui, n�o houve colis�o
}

void Gerenciador_Colisoes::tratarColisaoMegaObstacs()
{
    std::list<Obstaculo*>::iterator itObst;

    for (itObst = LOs.begin(); itObst != LOs.end(); itObst++)
    {
        if (verificarColisao(p1, *itObst) && p1->getVivo()) //Obst�culo x Megaman player 1
        {
            (*itObst)->obstaculizar(p1);
        }
    }

    if (p2) //S� entra se o p2 existir
    {
        for (itObst = LOs.begin(); itObst != LOs.end(); itObst++)
        {
            if (verificarColisao(p2, *itObst) && p2->getVivo()) //Obst�culo x Megaman player 2
            {
                (*itObst)->obstaculizar(p2);
            }
        }
    }
}

void Gerenciador_Colisoes::tratarColisaoMegaInimigos()
{
    std::vector<Inimigo*>::iterator itInim;

    for (itInim = LIs.begin(); itInim != LIs.end(); itInim++) //Colis�o Megaman x Inimigo
    {
        if ((*itInim)->getVivo() && verificarColisao(p1, *itInim) && p1->getVivo()) //Se o Inimigo estiver vivo E houve a colis�o
        {
              (*itInim)->danificar(p1);
        }
    }

    if (p2) //S� entra se o p2 existir
    {
        for (itInim = LIs.begin(); itInim != LIs.end(); itInim++) //Colis�o Megaman player 2 x Inimigo
        {
            if ((*itInim)-> getVivo() && verificarColisao(p2, *itInim) && p2->getVivo()) //Se o Inimigo estiver vivo E houve a colis�o
            {
                (*itInim)->danificar(p2);
            }
        }
    }
}

void Gerenciador_Colisoes::tratarColisaoMegaProjeteis() //Proj�til do Inimigo colidindo com o Megaman
{
    std::set<Projetil*>::iterator itProj;

    for (itProj = LPs.begin(); itProj != LPs.end(); itProj++) //Colis�o Proj�til x Megaman
    {
        if (!((*itProj)->getDoMega())) //S� entra se n�o for do Megaman
        {
            if ((*itProj)->getVivo() && verificarColisao(p1, *itProj) && p1->getVivo()) //Se o proj�til estiver vivo (ativo) && houve a colis�o
            {
                if ((*itProj) && (*(*itProj)) == 5) //ID 5 -> ProjetilMetall
                {
                    ProjetilMetall* aux;
                    aux = static_cast<ProjetilMetall*>(*itProj);
                    aux->atingirMegaman(p1);
                }
                else //� Projetil, ID!=5 -> ProjetilCutMan
                {
                    ProjetilCutMan* aux;
                    aux = static_cast<ProjetilCutMan*>(*itProj);
                    aux->atingirMegaman(p1);
                }
            }
        }
    }

    if (p2) //S� entra se o p2 existir
    {
        for (itProj = LPs.begin(); itProj != LPs.end(); itProj++) //Colis�o Proj�til x Megaman
        {
            if (!((*itProj)->getDoMega())) //S� entra se n�o for do Megaman
            {
                if ((*itProj)->getVivo() && verificarColisao(p2, *itProj) && p2->getVivo()) //Se o proj�til estiver vivo (ativo) && houve a colis�o
                {
                    if ((*itProj) && (*(*itProj)) == 5) //ID 5 - ProjetilMetall
                    {
                        ProjetilMetall* aux;
                        aux = static_cast<ProjetilMetall*>(*itProj);
                        aux->atingirMegaman(p2);
                    }
                    else //Projetil, doMega = false, ID!=5 - ProjetilCutMan
                    {
                        ProjetilCutMan* aux;
                        aux = static_cast<ProjetilCutMan*>(*itProj);
                        aux->atingirMegaman(p2);
                    }
                }
            }
        }
    }
}

void Gerenciador_Colisoes::tratarColisaoInimsProjeteis() //Proj�til do Megaman colidindo com Inimigo
{
    std::set<Projetil*>::iterator itProj;
    std::vector<Inimigo*>::iterator itInim;
    ProjetilMegaman* aux;

    for (itProj = LPs.begin(); itProj != LPs.end(); itProj++)
    {
        for (itInim = LIs.begin(); itInim != LIs.end(); itInim++) //Proj�til x Inimigo
        {
            if ((*itProj)->getDoMega()) { //S� entra se for Proj�til do Megaman
                if ((*itProj)->getVivo() && verificarColisao(*itInim, *itProj) && (*itInim)->getVivo()) //Se o proj�til estiver vivo (ativo) && houve a colis�o
                {
                    aux = static_cast<ProjetilMegaman*>(*itProj);
                    aux->atingirInimigo(*itInim);
                }
            }
        }
    }
}

void Gerenciador_Colisoes::tratarColisaoInimsObstacs()
{
    std::list<Obstaculo*>::iterator itObst;
    std::vector<Inimigo*>::iterator itInim;

    for (itObst = LOs.begin(); itObst != LOs.end(); itObst++)
    {
        for (itInim = LIs.begin(); itInim != LIs.end(); itInim++) //Obst�culo x Inimigo
        {
            if (verificarColisao(*itInim, *itObst))
            {
                (*itObst)->obstaculizar(*itInim);
            }
        }
    }
}

void Gerenciador_Colisoes::verificarRemovidos()
{
    std::vector<Inimigo*>::iterator itInim = LIs.begin();
    std::set<Projetil*>::iterator itProj = LPs.begin();

    while (itInim != LIs.end()) //Percorre o vector de inimigos em busca de ponteiros vazios para remover
    {
        if (!((*itInim)->getVivo()))
        {
            itInim = LIs.erase(itInim);
        }
        else
        {
            ++itInim;
        }
    }

    while (itProj != LPs.end()) //Percorre o set de proj�teis em busca de ponteiros vazios para remover
    {
        if (!((*itProj)->getVivo()))
        {
            itProj = LPs.erase(itProj);
        }
        else
        {
            ++itProj;
        }
    }
}

void Gerenciador_Colisoes::incluirInimigo(Inimigo* pI) { if (pI) LIs.push_back(pI); }

void Gerenciador_Colisoes::incluirObstaculo(Obstaculo* pO) { if (pO) LOs.push_back(pO); }

void Gerenciador_Colisoes::incluirProjetil(Projetil* pP) { if (pP) LPs.insert(pP); }

void Gerenciador_Colisoes::incluirMegaman(Megaman* pm) 
{ 
    if (!pm) return;

    if (!p1) p1 = pm;
    else p2 = pm;
}

void Gerenciador_Colisoes::setListaEntidades(ListaEntidades* pLista)
{
    LEs = pLista;
}

void Gerenciador_Colisoes::executar() //Refer�ncia: Giovane do canal Gege++
{
    //std::cout << "posicao: " << p1->getCoords().x << ", " << p1->getCoords().y << std::endl;
    verificarRemovidos();
    LEs->verificaAbatidos(); //Para tentar corrigir os erros de acesso inv�lido
    
    tratarColisaoMegaObstacs();
    tratarColisaoMegaInimigos();
    tratarColisaoMegaProjeteis();
    tratarColisaoInimsProjeteis();
    tratarColisaoInimsObstacs();

}
void Gerenciador_Colisoes::limpar()
{
    LIs.clear();
    LOs.clear();
    LPs.clear();

    p1 = nullptr;
    p2 = nullptr;
}