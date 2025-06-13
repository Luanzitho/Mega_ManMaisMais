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
    int i = 0;
  
    while (faseJson["layers"][i]["name"] != "Spawn Player")
    {
		i++;
    }
    p1->setCoords(sf::Vector2f ((float)(faseJson["layers"][i]["objects"][0]["x"]*3), (float)(faseJson["layers"][i]["objects"][0]["y"]*3)));
    p1->setExecutando(true);
    criarInimigos();
}

Fase1::~Fase1()
{

}

void Fase1::executar(float dt)
{
	desenharCenario();
    //p1->executar(dt);
    //std::cout << "Fase 1 executando" << std::endl;
    //p1->desenhar();
   /*for (int i = 0; i< plataformas.size(); i++)
	   plataformas[i]->desenhar();*/
    LEs->percorrer(dt, getTamanho());
	moveMapa();

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
    //std::mt19937 gen(rd());                     // motor aleatório (Mersenne Twister)
     //std::uniform_int_distribution<> dist(3, 10); // faixa: 3 a 10
     //int sorteado = dist(gen); // gera um número aleatório entre 3 e 10
    int i = 0;
    int inimigosSpawnados = 0;
    while (faseJson["layers"][i]["name"] != "Spawn Inimigos")
    {
        i++;
    }
    for (int j = 0; j < inimigos.size(); j++)
    {
        //std::uniform_int_distribution<> dist(0, 1); // faixa: 0 a 1
        //int qualInimigo = dist(gen); // gera um número aleatório entre 0 e 1
        //if (qualInimigo)inimigos.push_back(new Metall);
        //else inimigos.push_back(new BigEye);
        inimigos[j]->setCoords(sf::Vector2f((float)(faseJson["layers"][i]["objects"][j]["x"] * 3), (float)(faseJson["layers"][i]["objects"][j]["y"] * 3)));
        //inimigos[j]->associaListaEntidades(LEs);
        // met->
        // met->associaGerenciadorColisoes(&GC);
        //met->setGerenciadorGrafico(Gerenciador_Grafico::getInstancia());
        //met->conhecerJogador(p1);
    }
}

void Fase1::criarObstaculos()
{
}

/*std::string Fase1::getMapaFase()
{
    return "../Mapas/mapa1.tmj";
}*/
