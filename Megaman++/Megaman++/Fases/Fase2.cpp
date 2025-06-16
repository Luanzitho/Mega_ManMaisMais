#include "Fase2.h"
#include <iostream>


Fase2::Fase2(): minInimigosMedios(3)
{
    std::fstream jsonFile("Mapas/mapa2.tmj");
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
    criarChao();
    int i = 0;
  
    while (faseJson["layers"][i]["name"] != "Spawn Player")
    {
		i++;
    }
    p1->setCoords(sf::Vector2f ((float)(faseJson["layers"][i]["objects"][0]["x"]*3), (float)(faseJson["layers"][i]["objects"][0]["y"]*3)));
    p1->setExecutando(true);
    incluirMegaGC(p1);
	LEs->incluirEntidade(p1);
    criarInimigos();
}

Fase2::~Fase2()
{

}

void Fase2::executar(float dt)
{
	
	desenharCenario();
    //p1->executar(dt);
    //p1->desenhar();
   /*for (int i = 0; i< plataformas.size(); i++)
	   plataformas[i]->desenhar();*/
    LEs->percorrer(dt, getTamanho());
   
	moveMapa(dt);
    //std::cout << "Fase 1 executando" << std::endl;

    gerenciarColisoes();
    //std::cout << "Fase 1 executando" << std::endl;
    //criarInimigos();
    //criarChefoes();
    //criarObsMedios();
    //criarProjeteis();
}

void Fase2::criarChefoes()
{

}

void Fase2::criarObsMedios()
{

}

void Fase2::criarMinInimigosMedios()
{

}

void Fase2::criarProjeteis()
{

}

void Fase2::criarInimigos()
{
    int sorteado = aleatoriza(0,4); // gera um número aleatório entre 3 e 10
    
    int i = 0;
    while (faseJson["layers"][i]["name"] != "Spawn Inimigos")
    {
        i++;
    }
    //std::vector<int> jaFoi;
    for (int j = 0; j < faseJson["layers"][i]["objects"].size(); j++)
    {
        jaFoi.push_back(0); // vetor para saber quais pontos já foram usados
    }
   
    for (int j = 0; j < sorteado; j++)
    {
        //std::uniform_int_distribution<> qual(0, 1); // faixa: 0 a 1 para saber qual inimigo criar
        int qualInimigo = aleatoriza(0,1); // gera um número aleatório entre 0 e 1
        Inimigo* inimigo = nullptr;
        if (qualInimigo)inimigo = new Metall;
        else inimigo = new BigEye;

        //std::uniform_int_distribution<> quantos(0, faseJson["layers"][i]["objects"].size() - 1); // faixa com o total de pontos para o inimigo spawnar
        do
        {
            qualInimigo = aleatoriza(0, faseJson["layers"][i]["objects"].size() - 1); // gera um número aleatório
           
        } while (jaFoi[qualInimigo] != 0);
        jaFoi[qualInimigo] = 1; // marca que o ponto já foi usado
        inimigo->setGerenciadorGrafico(Gerenciador_Grafico::getInstancia());
        inimigo->associaListaEntidades(LEs);
        inimigo->associaGerenciadorColisoes(getGC());
        inimigo->conhecerJogador(p1);
        inimigo->setCoords(sf::Vector2f((float)(faseJson["layers"][i]["objects"][qualInimigo]["x"] * 3), (float)(faseJson["layers"][i]["objects"][qualInimigo]["y"] * 3)));
        inimigos.push_back(inimigo);
        LEs->incluirEntidade(inimigos[j]);
        incluirInimigoGC(inimigos[j]);
    }
    criarInimigosFaceis();
}

void Fase2::criarObstaculos()
{
    int controle = 0;
    while (faseJson["layers"][controle]["name"] != "Obstaculos")
    {
        controle++;
    }
    for (int i = 0; i < faseJson["layers"][controle]["objects"].size(); i++)
    {
        Espinho* p = new Espinho;
        p->setGerenciadorGrafico(pGG->getInstancia());
        p->setCoords(sf::Vector2f((float)(faseJson["layers"][controle]["objects"][i]["x"] * 3), (float)faseJson["layers"][controle]["objects"][i]["y"] * 3));
        p->setTamanho(sf::Vector2f((float)faseJson["layers"][controle]["objects"][i]["width"] * 3, (float)faseJson["layers"][controle]["objects"][i]["height"] * 3));
        obstaculos.push_back(p);
        //std::cout << "Plataforma criada: " << faseJson["layers"][controle]["objects"][i]["x"] << ", " << faseJson["layers"][1]["objects"][i]["y"] << std::endl;
        incluirObstaculoGC(p);
        //faseJson["layers"][1]["objects"];
    }
}
