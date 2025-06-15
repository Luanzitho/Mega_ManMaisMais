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
    //std::cout << "Fase 1 executando" << std::endl;
	separaSprites();
    criarPlataformas();
    int i = 0;
  
    while (faseJson["layers"][i]["name"] != "Spawn Player")
    {
		i++;
    }
    p1->setCoords(sf::Vector2f ((float)(faseJson["layers"][i]["objects"][0]["x"]*3), (float)(faseJson["layers"][i]["objects"][0]["y"]*3)));
    p1->setExecutando(true);
	GC.incluirMegaman(p1);
	LEs->incluirEntidade(p1);
    criarInimigos();
}

Fase1::~Fase1()
{

}

void Fase1::executar(float dt)
{
	
	desenharCenario();
    //p1->executar(dt);
    //p1->desenhar();
   /*for (int i = 0; i< plataformas.size(); i++)
	   plataformas[i]->desenhar();*/
    LEs->percorrer(dt, getTamanho());
   
	moveMapa(dt);
    //std::cout << "Fase 1 executando" << std::endl;

    GC.executar();
    //std::cout << "Fase 1 executando" << std::endl;
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
    std::mt19937 gen(rd());                     // motor aleatório (Mersenne Twister)
    std::uniform_int_distribution<> dist(3, 10); // faixa: 3 a 10 para saber quantos inimigos criar
    int sorteado = dist(gen); // gera um número aleatório entre 3 e 10
    
    int i = 0;
    while (faseJson["layers"][i]["name"] != "Spawn Inimigos")
    {
        i++;
    }
    std::vector<int> jaFoi;
    for (int i = 0; i < 10; i++)
    {
        jaFoi.push_back(0); // vetor para saber quais pontos já foram usados
    }
    for (int j = 0; j < sorteado; j++)
    {
        std::uniform_int_distribution<> qual(0, 1); // faixa: 0 a 1 para saber qual inimigo criar
        int qualInimigo = qual(gen); // gera um número aleatório entre 0 e 1
        Inimigo* inimigo = nullptr;
        if (qualInimigo)inimigo = new Metall;
        else inimigo = new BigEye;

        std::uniform_int_distribution<> quantos(0, faseJson["layers"][i]["objects"].size() - 1); // faixa com o total de pontos para o inimigo spawnar
        do
        {
            qualInimigo = quantos(gen); // gera um número aleatório
        } while (jaFoi[qualInimigo] != 0);
        jaFoi[qualInimigo] = 1; // marca que o ponto já foi usado
        inimigo->setGerenciadorGrafico(Gerenciador_Grafico::getInstancia());
        inimigo->associaListaEntidades(LEs);
        inimigo->associaGerenciadorColisoes(&GC);
        inimigo->conhecerJogador(p1);
        inimigo->setCoords(sf::Vector2f((float)(faseJson["layers"][i]["objects"][qualInimigo]["x"] * 3), (float)(faseJson["layers"][i]["objects"][qualInimigo]["y"] * 3)));
        inimigos.push_back(inimigo);
        LEs->incluirEntidade(inimigos[j]);
        //std::cout << "Inimigos sorteados: " << sorteado << std::endl;
        GC.incluirInimigo(inimigos[j]);
    }
}

void Fase1::criarObstaculos()
{
}

/*std::string Fase1::getMapaFase()
{
    return "../Mapas/mapa1.tmj";
}*/
