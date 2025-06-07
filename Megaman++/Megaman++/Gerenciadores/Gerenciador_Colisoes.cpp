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

void Gerenciador_Colisoes::executar() //Referência: Giovane do canal Gege++
{
     std::vector<Inimigo*>::iterator itInim;
     std::list<Obstaculo*>::iterator itObst;
     std::set<Projetil*>::iterator itProj;

     for (itInim = LIs.begin(); itInim != LIs.end(); itInim++) //Colisão Megaman x Inimigo
     {
        if (verificarColisao(p1, *itInim))
            (*itInim)->danificar(p1);
     }
     
     for (itObst = LOs.begin(); itObst != LOs.end(); itObst++) //Colisão Obstáculo x Alguém
     {
         if (verificarColisao(p1, *itObst)) //Obstáculo x Megaman
             (*itObst)->obstacular();

         for (itInim = LIs.begin(); itInim != LIs.end(); itInim++) //Obstáculo x Inimigo
         {
             if (verificarColisao(*itInim, *itObst))
                 (*itObst)->obstacular();
         }
     }

     for (itProj = LPs.begin(); itProj != LPs.end(); itProj++) //Colisão Projétil x Alguém
     {
         if (verificarColisao(p1, *itProj)) {} //Projétil x Megaman
             //(*itProj)-> AGIR

         for (itInim = LIs.begin(); itInim != LIs.end(); itInim++) //Projétil x Inimigo
         {
              if (verificarColisao(*itInim, *itProj)){} 
                 //(*itProj)-> AGIR
         }

         for (itObst = LOs.begin(); itObst != LOs.end(); itObst++) //Projétil x Obstáculo
         {
             if(verificarColisao(*itObst, *itProj)){}
                //(*itProj)-> AGIR
         }
     }
}