#include "Fase1.h"
#include <iostream>


Fase1::Fase1() : maxChefoes(0)
{
    std::fstream jsonFile("Mapas/mapa1.tmj");
    if (jsonFile.is_open()) {
        jsonFile >> faseJson;
        jsonFile.close();
    }
    else
    {
        std::cerr << "Erro ao abrir o arquivo JSON." << std::endl;
    }
	separaSprites();
    criarPlataformas();
}
Fase1::~Fase1()
{

}
void Fase1::executar(float dt)
{
	desenharCenario();
    p1->executar(dt);
    //std::cout << "Fase 1 executando" << std::endl;
    p1->desenhar();
   /*for (int i = 0; i< plataformas.size(); i++)
	   plataformas[i]->desenhar();*/
    GC.executar();
    //criarInimigos();
    //criarChefoes();
    //criarObsMedios();
    //criarProjeteis();
}
void Fase1::criarChefoes()
{

}
void Fase1::criarObsMedios()
{

}
void Fase1::criarProjeteis()
{

}

void Fase1::criarInimigos()
{
}

void Fase1::criarObstaculos()
{
}

/*std::string Fase1::getMapaFase()
{
    return "../Mapas/mapa1.tmj";
}*/
