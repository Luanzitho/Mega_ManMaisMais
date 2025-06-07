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

void Gerenciador_Colisoes::executar() //Refer�ncia: Giovane do canal Gege++
{
     std::vector<Inimigo*>::iterator itInim;
     std::list<Obstaculo*>::iterator itObst;
     std::set<Projetil*>::iterator itProj;

     for (itInim = LIs.begin(); itInim != LIs.end(); itInim++) //Colis�o Megaman x Inimigo
     {
        if (verificarColisao(p1, *itInim))
            (*itInim)->danificar(p1);
     }
     
     for (itObst = LOs.begin(); itObst != LOs.end(); itObst++) //Colis�o Obst�culo x Algu�m
     {
         if (verificarColisao(p1, *itObst)) //Obst�culo x Megaman
             (*itObst)->obstacular();

         for (itInim = LIs.begin(); itInim != LIs.end(); itInim++) //Obst�culo x Inimigo
         {
             if (verificarColisao(*itInim, *itObst))
                 (*itObst)->obstacular();
         }
     }

     for (itProj = LPs.begin(); itProj != LPs.end(); itProj++) //Colis�o Proj�til x Algu�m
     {
         if (verificarColisao(p1, *itProj)) {} //Proj�til x Megaman
             //(*itProj)-> AGIR

         for (itInim = LIs.begin(); itInim != LIs.end(); itInim++) //Proj�til x Inimigo
         {
              if (verificarColisao(*itInim, *itProj)){} 
                 //(*itProj)-> AGIR
         }

         for (itObst = LOs.begin(); itObst != LOs.end(); itObst++) //Proj�til x Obst�culo
         {
             if(verificarColisao(*itObst, *itProj)){}
                //(*itProj)-> AGIR
         }
     }
}