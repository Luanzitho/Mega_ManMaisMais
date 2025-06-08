#include "Gerenciador_Colisoes.h"

Gerenciador_Colisoes::Gerenciador_Colisoes()
{
    p1 = nullptr;
    LIs.clear();
    LOs.clear();
    LPs.clear();
}

Gerenciador_Colisoes::~Gerenciador_Colisoes()
{
}

const bool Gerenciador_Colisoes::verificarColisao(Entidade* pe1, Entidade* pe2) //Referência: Giu do PETECO
{
    sf::FloatRect rect1(pe1->getCoords(), pe1->getTamanho());
    sf::FloatRect rect2(pe2->getCoords(), pe2->getTamanho());

    if (rect1.intersects(rect2)) { //Houve colisão
        return true;
    }
    return false;
}

void Gerenciador_Colisoes::tratarColisaoMegaObstacs()
{
    std::list<Obstaculo*>::iterator itObst;

    for (itObst = LOs.begin(); itObst != LOs.end(); itObst++)
    {
        if (verificarColisao(p1, *itObst)) //Obstáculo x Megaman
        {
            (*itObst)->obstaculizar(p1);
        }
    }
}

void Gerenciador_Colisoes::tratarColisaoMegaInimigos()
{
    std::vector<Inimigo*>::iterator itInim;

    for (itInim = LIs.begin(); itInim != LIs.end(); itInim++) //Colisão Megaman x Inimigo
    {
        if (verificarColisao(p1, *itInim))
        {
            (*itInim)->danificar(p1);
        }
    }
}

void Gerenciador_Colisoes::tratarColisaoMegaProjeteis()
{
    std::set<Projetil*>::iterator itProj;

    for (itProj = LPs.begin(); itProj != LPs.end(); itProj++) //Colisão Projétil x Alguém
    {
        if (verificarColisao(p1, *itProj)) //Projétil x Megaman
        {
            //(*itProj)-> AGIR
        }
    }
}

void Gerenciador_Colisoes::tratarColisaoInimsProjeteis()
{
    std::set<Projetil*>::iterator itProj;
    std::vector<Inimigo*>::iterator itInim;

    for (itProj = LPs.begin(); itProj != LPs.end(); itProj++)
    {
        for (itInim = LIs.begin(); itInim != LIs.end(); itInim++) //Projétil x Inimigo
        {
            if (verificarColisao(*itInim, *itProj))
            {
                //(*itProj)-> AGIR
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

void Gerenciador_Colisoes::tratarColisaoProjObstacs()
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
        
        if (rect1.intersects(rect2)) { //Houve colisão
            (*itProj)->desativar();
        }
    }

}

void Gerenciador_Colisoes::incluirInimigo(Inimigo* pI) { if (pI) LIs.push_back(pI); }

void Gerenciador_Colisoes::incluirObstaculo(Obstaculo* pO) { if (pO) LOs.push_back(pO); }

void Gerenciador_Colisoes::incluirProjetil(Projetil* pP) { if (pP) LPs.insert(pP); }

void Gerenciador_Colisoes::incluirMegaman(Megaman* pM) { if (pM) p1 = pM; }

void Gerenciador_Colisoes::executar() //Referência: Giovane do canal Gege++
{
    tratarColisaoMegaObstacs();
    tratarColisaoMegaInimigos();
    tratarColisaoProjLimites();
    //tratarColisaoMegaProjeteis();
    //tratarColisaoInimsProjeteis();
    tratarColisaoInimsObstacs();
    //tratarColisaoProjObstacs();
}