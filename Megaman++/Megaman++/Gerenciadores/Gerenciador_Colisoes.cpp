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
    /*
    float xE1, yE1, xE2, yE2; //Coordenadas
    float txE1, tyE1, txE2, tyE2; //Tamanhos

    xE1 = pe1->getCoords().x;
    yE1 = pe1->getCoords().y;
    txE1 = pe1->getTamanho().x;
    tyE1 = pe1->getTamanho().y;

    xE2 = pe2->getCoords().x;
    yE2 = pe2->getCoords().y;
    txE2 = pe2->getTamanho().x;
    tyE2 = pe2->getTamanho().y;

    float direitaE1 = xE1 + txE1;
    float baseE1 = yE1 + tyE1;

    float direitaE2 = xE2 + txE2;
    float baseE2 = yE2 + tyE2;

    if (direitaE1 < xE2 || xE1 > direitaE2 || baseE1 < yE2 || yE1 > baseE2)
        return false;
    */

    sf::FloatRect ret1(pe1->getCoords(), pe1->getTamanho());
    sf::FloatRect ret2(pe2->getCoords(), pe2->getTamanho());

    if (ret1.intersects(ret2)) {
        return true;
    }

    return false;
}

void Gerenciador_Colisoes::colisaoMegaObstacs()
{
}

void Gerenciador_Colisoes::colisaoMegaInimigos()
{
}

void Gerenciador_Colisoes::colisaoMegaProjeteis()
{
}

void Gerenciador_Colisoes::colisaoInimsProjeteis()
{
}

void Gerenciador_Colisoes::colisaoInimsObstacs(){}

void Gerenciador_Colisoes::incluirInimigo(Inimigo* pI) { if (pI) LIs.push_back(pI); }

void Gerenciador_Colisoes::incluirObstaculo(Obstaculo* pO) { if (pO) LOs.push_back(pO); }

void Gerenciador_Colisoes::incluirProjetil(Projetil* pP) { if (pP) LPs.insert(pP); }

void Gerenciador_Colisoes::incluirMegaman(Megaman* pM) { if (pM) p1 = pM; }

void Gerenciador_Colisoes::executar()
{

}