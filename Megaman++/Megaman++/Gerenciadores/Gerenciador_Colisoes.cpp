#include "Gerenciador_Colisoes.h"
#include <iostream>

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

const bool Gerenciador_Colisoes::verificarColisao(Entidade* pE1, Entidade* pE2) //Referência: Giu do PETECO
{
    sf::FloatRect rect1(pE1->getCoords(), pE1->getTamanho());
    sf::FloatRect rect2(pE2->getCoords(), pE2->getTamanho());

    if (rect1.intersects(rect2)) //Se true, houve colisão
    { 
        return true;
    }
    return false; //Se chegou aqui, não houve colisão
}

void Gerenciador_Colisoes::tratarColisaoMegaObstacs()
{
    std::list<Obstaculo*>::iterator itObst;

    for (itObst = LOs.begin(); itObst != LOs.end(); itObst++)
    {
        if (verificarColisao(p1, *itObst) && p1->getVivo()) //Obstáculo x Megaman player 1
        {
            (*itObst)->obstaculizar(p1);
        }
    }

    if (p2) //Só entra se o p2 existir
    {
        for (itObst = LOs.begin(); itObst != LOs.end(); itObst++)
        {
            if (verificarColisao(p2, *itObst) && p2->getVivo()) //Obstáculo x Megaman player 2
            {
                (*itObst)->obstaculizar(p2);
            }
        }
    }
}

void Gerenciador_Colisoes::tratarColisaoMegaInimigos()
{
    std::vector<Inimigo*>::iterator itInim;

    for (itInim = LIs.begin(); itInim != LIs.end(); itInim++) //Colisão Megaman x Inimigo
    {
        if ((*itInim)->getVivo() && verificarColisao(p1, *itInim) && p1->getVivo()) //Se o Inimigo estiver vivo E houve a colisão
        {
              (*itInim)->danificar(p1);
        }
    }

    if (p2) //Só entra se o p2 existir
    {
        for (itInim = LIs.begin(); itInim != LIs.end(); itInim++) //Colisão Megaman x Inimigo
        {
            if ((*itInim)->getVivo() && verificarColisao(p2, *itInim) && p2->getVivo()) //Se o Inimigo estiver vivo E houve a colisão
            {
                (*itInim)->danificar(p2);
            }
        }
    }
}

void Gerenciador_Colisoes::tratarColisaoMegaProjeteis() //Projétil do Inimigo colidindo com o Megaman
{
    std::set<Projetil*>::iterator itProj;

    for (itProj = LPs.begin(); itProj != LPs.end(); itProj++) //Colisão Projétil x Megaman
    {
        if (!((*itProj)->getDoMega())) //Só entra se não for do Megaman
        {
            if ((*itProj)->getVivo() && verificarColisao(p1, *itProj) && p1->getVivo()) //Se o projétil estiver vivo (ativo) && houve a colisão
            {
                if ((*itProj)->getId() == 5) //ID 5 -> ProjetilMetall
                {
                    ProjetilMetall* aux;
                    aux = static_cast<ProjetilMetall*>(*itProj);
                    aux->atingirMegaman(p1);
                }
                else //É Projetil, !doMega = false, ID!=5 -> ProjetilCutMan
                {
                    ProjetilCutMan* aux;
                    aux = static_cast<ProjetilCutMan*>(*itProj);
                    aux->atingirMegaman(p1);
                }
            }
        }
    }

    if (p2) //Só entra se o p2 existir
    {
        for (itProj = LPs.begin(); itProj != LPs.end(); itProj++) //Colisão Projétil x Megaman
        {
            if (!((*itProj)->getDoMega())) //Só entra se não for do Megaman
            {
                if ((*itProj)->getVivo() && verificarColisao(p2, *itProj) && p2->getVivo()) //Se o projétil estiver vivo (ativo) && houve a colisão
                {
                    if ((*itProj)->getId() == 5) //ID 5 - ProjetilMetall
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

void Gerenciador_Colisoes::tratarColisaoInimsProjeteis() //Projétil do Megaman colidindo com Inimigo
{
    std::set<Projetil*>::iterator itProj;
    std::vector<Inimigo*>::iterator itInim;
    ProjetilMegaman* aux;

    for (itProj = LPs.begin(); itProj != LPs.end(); itProj++)
    {
        for (itInim = LIs.begin(); itInim != LIs.end(); itInim++) //Projétil x Inimigo
        {
            if ((*itProj)->getDoMega()) { //Só entra se for Projétil do Megaman
                if ((*itProj)->getVivo() && verificarColisao(*itInim, *itProj)) //Se o projétil estiver vivo (ativo) && houve a colisão
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
        for (itInim = LIs.begin(); itInim != LIs.end(); itInim++) //Obstáculo x Inimigo
        {
            if (verificarColisao(*itInim, *itObst))
            {
                (*itObst)->obstaculizar(*itInim);
            }
        }
    }
}

void Gerenciador_Colisoes::tratarColisaoProjObstacs() //Acho que essa aqui dá para tirar, os projéteis atravessam as paredes em Megaman
{
    std::list<Obstaculo*>::iterator itObst;
    std::set<Projetil*>::iterator itProj;

    for (itProj = LPs.begin(); itProj != LPs.end(); itProj++)
    {
        for (itObst = LOs.begin(); itObst != LOs.end(); itObst++) //Projétil x Obstáculo
        {
            if (verificarColisao(*itObst, *itProj)) {}
                //(*itProj)-> AGIR
        }
    }
}

void Gerenciador_Colisoes::tratarColisaoProjLimites()
{
    
    std::set<Projetil*>::iterator itProj;
    sf::FloatRect rect2(sf::Vector2f(0,0), sf::Vector2f(1180.f, 720.f));


    for (itProj = LPs.begin(); itProj != LPs.end(); itProj++)
    {
        sf::FloatRect rect1((*itProj)->getCoords(), (*itProj)->getTamanho());
        
        if (rect1.intersects(rect2)) //Houve colisão
        { 
            (*itProj)->destruir();
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

void Gerenciador_Colisoes::executar() //Referência: Giovane do canal Gege++
{
    //std::cout << "posicao: " << p1->getCoords().x << ", " << p1->getCoords().y << std::endl;
    tratarColisaoMegaObstacs();
    tratarColisaoMegaInimigos();
    //tratarColisaoProjLimites();
    tratarColisaoMegaProjeteis();
    tratarColisaoInimsProjeteis();
    tratarColisaoInimsObstacs();
    //tratarColisaoProjObstacs();
}