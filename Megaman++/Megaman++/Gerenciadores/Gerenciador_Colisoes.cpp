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

const bool Gerenciador_Colisoes::verificarColisao(Entidade* pe1, Entidade* pe2) //Refer�ncia: Giu do PETECO
{
    sf::FloatRect rect1(pe1->getCoords(), pe1->getTamanho());
    sf::FloatRect rect2(pe2->getCoords(), pe2->getTamanho());

    if (rect1.intersects(rect2)) { //Houve colis�o
        /*if (pe1->getId() == 1) //Colis�o entre jogador e algu�m
        {
            if(pe2->getId()==2) //Jogador e inimigo
        }

        if(pe1->getId()==2) //Colis�o entre inimigo e algu�m

        if(pe1->getId()==3) //Colis�o entre obst�culo e algu�m
        */
        return true;
    }
    return false;
}

void Gerenciador_Colisoes::tratarColisaoMegaObstacs()
{
}

void Gerenciador_Colisoes::tratarColisaoMegaInimigos()
{
}

void Gerenciador_Colisoes::tratarColisaoMegaProjeteis()
{
}

void Gerenciador_Colisoes::tratarColisaoInimsProjeteis()
{
}

void Gerenciador_Colisoes::tratarColisaoInimsObstacs()
{
}

void Gerenciador_Colisoes::incluirInimigo(Inimigo* pI) { if (pI) LIs.push_back(pI); }

void Gerenciador_Colisoes::incluirObstaculo(Obstaculo* pO) { if (pO) LOs.push_back(pO); }

void Gerenciador_Colisoes::incluirProjetil(Projetil* pP) { if (pP) LPs.insert(pP); }

void Gerenciador_Colisoes::incluirMegaman(Megaman* pM) { if (pM) p1 = pM; }

void Gerenciador_Colisoes::executar()
{

}