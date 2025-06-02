#include "Gerenciador_Colisoes.h"

Gerenciador_Colisoes::Gerenciador_Colisoes()
{
    LIs.clear();
    //LOs.clear();
    LPs.clear();
}

Gerenciador_Colisoes::~Gerenciador_Colisoes()
{
}

const bool Gerenciador_Colisoes::verificarColisao(Entidade* pe1, Entidade* pe2)
{
    return false;
}

void Gerenciador_Colisoes::colisaoJogsObstacs()
{
}

void Gerenciador_Colisoes::colisaoJogsInimigos()
{
}

void Gerenciador_Colisoes::colisaoJogsProjeteis()
{
}

void Gerenciador_Colisoes::colisaoInimsProjeteis()
{
}

void Gerenciador_Colisoes::incluirInimigo(Inimigo* pI) { if (pI) LIs.push_back(pI); }

//void Gerenciador_Colisoes::incluirObstaculo(Obstaculo* pO) { if (pO) LOs.push_back(pI); }

void Gerenciador_Colisoes::incluirProjetil(Projetil* pP) { if (pP) LPs.insert(pP); }

void Gerenciador_Colisoes::executar()
{

}