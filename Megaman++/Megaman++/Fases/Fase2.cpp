#include "Fase2.h"
#include <iostream>


Fase2::Fase2(): maxChefoes(3), minEspinhos(3)
{
    setId(14);
    std::cout << "Fase 2 executando" << std::endl;
    std::fstream jsonFile("Mapas/mapa2.tmj");
    if (jsonFile.is_open()) {
        jsonFile >> faseJson;
        jsonFile.close();
    }
    else
    {
        std::cout << "Erro ao abrir o arquivo JSON." << std::endl;
    }
    //std::cout << "Fase 2 executando" << std::endl;
	separaSprites();
    std::cout << "desenhou sprites2." << std::endl;
    criarChao();
    std::cout << "criou o chao 2." << std::endl;
	quantidadeLayers = faseJson["layers"].size();
    int i = 0;
  
    while (faseJson["layers"][i]["name"] != "Spawn Player" && i< quantidadeLayers)
    {
		i++;
    }
    if (i >= quantidadeLayers)
    {
        std::cout << "Erro tentar acaha camada Spawn Player." << std::endl;
    }
    else
    {
        p1->setCoords(sf::Vector2f((float)(faseJson["layers"][i]["objects"][0]["x"] * 3), (float)(faseJson["layers"][i]["objects"][0]["y"] * 3)));
    }
    
    p1->setExecutando(true);
    GC.incluirMegaman(p1);
	LEs.incluirEntidade(p1);
   
   // criarInimigos();
    std::cout << "criou inimigos 2." << std::endl;
    criarObstaculos();
    std::cout << "criou obstaculos 2." << std::endl;
    
    
    
}

Fase2::~Fase2()
{

}

void Fase2::executar(float dt)
{
	
	desenharCenario();
    LEs.percorrer(dt, getTamanho());
   
	moveMapa(dt);
    pontuacao = p1->getPontos();
    if (!p1->getVivo())morreu = true;
	GC.executar();
    if (p1->getCoords().x > 1100)acabou = true;
}

void Fase2::criarChefoes()
{
    int i = 0;
    while (faseJson["layers"][i]["name"] != "Boss" && i < quantidadeLayers)
    {
        i++;
    }
    if (i >= quantidadeLayers)
    {
        std::cout << "Erro tentar acaha camada Boss." << std::endl;
    }
    else
    {
        for (int j = 0; j < maxChefoes; j++)
        {
            int qualObs = 0;
            Inimigo* p = new CutMan;

            p->setGerenciadorGrafico(pGG->getInstancia());
            p->associaGerenciadorColisoes(&GC);
            p->associaListaEntidades(&LEs);
            p->conhecerJogador(p1);
            p->setCoords(sf::Vector2f((float)(faseJson["layers"][i]["objects"][qualObs]["x"] * 3), (float)faseJson["layers"][i]["objects"][qualObs]["y"] * 3));
            //p->setTamanho(sf::Vector2f((float)faseJson["layers"][i]["objects"][qualObs]["width"] * 3, (float)faseJson["layers"][i]["objects"][qualObs]["height"] * 3));
            inimigos.push_back(p);
			GC.incluirInimigo(p);
            LEs.incluirEntidade(inimigos[inimigos.size() - 1]);
        }
    }
    i = 0;
    while (faseJson["layers"][i]["name"] != "Spawn Inimigos" && i < quantidadeLayers)
    {
        i++;
    }
    if (i >= quantidadeLayers)
    {
        std::cout << "Erro tentar acaha camada Boss." << std::endl;
    }
    else
    {
        for (int j = 1; j < maxChefoes; j++)
        {
            int qualObs = 0;
            Inimigo* p = new CutMan;
            do
            {
                qualObs = aleatoriza(0, faseJson["layers"][i]["objects"].size() - 1); // gera um número aleatório

            } while (jaFoi[qualObs] != 0);//verifica se o ponto já foi usado
            jaFoi[qualObs] = 1; // marca que o ponto já foi usado
            p->setGerenciadorGrafico(pGG->getInstancia());
            p->associaGerenciadorColisoes(&GC);
            p->associaListaEntidades(&LEs);
            p->conhecerJogador(p1);
            p->setCoords(sf::Vector2f((float)(faseJson["layers"][i]["objects"][qualObs]["x"] * 3), (float)faseJson["layers"][i]["objects"][qualObs]["y"] * 3));
            //p->setTamanho(sf::Vector2f((float)faseJson["layers"][i]["objects"][qualObs]["width"] * 3, (float)faseJson["layers"][i]["objects"][qualObs]["height"] * 3));
            inimigos.push_back(p);
            GC.incluirInimigo(p);
            LEs.incluirEntidade(inimigos[inimigos.size() - 1]);
        }
    }
    
}

void Fase2::criarEspinhos()
{
    int i = 0;
    while (faseJson["layers"][i]["name"] != "Obstaculos" && i < quantidadeLayers)
    {
        i++;
    }
    if (i >= quantidadeLayers)
    {
        std::cout << "Erro tentar acaha camada Obstaculos." << std::endl;
    }
    else
    {
        for (int j = 0; j < minEspinhos; j++)
        {
            int qualObs;
            Obstaculo* p = new Espinho;

            do
            {
                qualObs = aleatoriza(0, faseJson["layers"][i]["objects"].size() - 1); // gera um número aleatório

            } while (jaFoi[qualObs] != 0);//verifica se o ponto já foi usado
            jaFoi[qualObs] = 1; // marca que o ponto já foi usado
            p->setGerenciadorGrafico(pGG->getInstancia());
            p->setCoords(sf::Vector2f((float)(faseJson["layers"][i]["objects"][qualObs]["x"] * 3), (float)faseJson["layers"][i]["objects"][qualObs]["y"] * 3));
            p->setTamanho(sf::Vector2f((float)faseJson["layers"][i]["objects"][qualObs]["width"] * 3, (float)faseJson["layers"][i]["objects"][qualObs]["height"] * 3));
            obstaculos.push_back(p);
			GC.incluirObstaculo(p);
            LEs.incluirEntidade(obstaculos[obstaculos.size() - 1]);
        }
    }
}


void Fase2::criarInimigos()
{
    int sorteado = aleatoriza(0,1); // gera um número aleatório entre 3 e 10
	jaFoi.clear(); // limpa o vetor de pontos já usados
    int i = 0;
    while (faseJson["layers"][i]["name"] != "Spawn Inimigos" && i < quantidadeLayers)
    {
        i++;
    }
    if (i >= quantidadeLayers)
    {
        std::cout << "Erro tentar acaha camada Spawn Inimigos." << std::endl;
    } 
    else
    {
        for (int j = 0; j < faseJson["layers"][i]["objects"].size(); j++)
        {
            jaFoi.push_back(0); // vetor para saber quais pontos já foram usados
        }

        for (int j = 0; j < sorteado; j++)
        {
            int qualInimigo = aleatoriza(0, 10); // gera um número aleatório entre 0 e 10
            bool eMetall = (qualInimigo < 5); // se for menor que 5, é Metall
            if (eMetall)minInimigosFaceis++;
			else maxChefoes++;
        }
    }
    
    
    criarInimigosFaceis();
	criarChefoes();
}

void Fase2::criarObstaculos()
{
    int controle = 0;
    while (faseJson["layers"][controle]["name"] != "Obstaculos" && controle < quantidadeLayers)
    {
        controle++;
    }
    if (controle >= quantidadeLayers)
    {
        std::cout << "Erro tentar acaha camada Obstaculos." << std::endl;
    }
    else
    {
        int sorteado = aleatoriza(0, 4); // gera um número aleatório entre 3 e 10
        jaFoi.clear(); // limpa o vetor de pontos já usados
        for (int j = 0; j < faseJson["layers"][controle]["objects"].size(); j++)
        {
            jaFoi.push_back(0); // vetor para saber quais pontos já foram usados
        }
        for (int i = 0; i < sorteado; i++)
        {
            int qualObs = aleatoriza(0, 1); // gera um número aleatório entre 0 e 1
            bool eEspinho = (qualObs == 0); // se for 0, é espinho; se for 1, é plataforma

            if (eEspinho)minEspinhos++;
            else minObstaculosFaceis++;
        }
        criarPlataformas();
        criarEspinhos();
    }
   
}

void Fase2::salvar() {
    int lugar = getId();
    int idx = dadosSalvos["id"][lugar].size();
    dadosSalvos["id"][lugar][idx]["maxChefoes"] = maxChefoes;
    dadosSalvos["id"][lugar][idx]["minEspinhos"] = minEspinhos;
    Fase::salvar();
}

void Fase2::carregar() {
    int lugar = getId();
    int idx = dadosSalvos["id"][lugar].size() - 1;
    maxChefoes = dadosSalvos["id"][lugar][idx]["maxChefoes"];
    minEspinhos = dadosSalvos["id"][lugar][idx]["minEspinhos"];
    Fase::carregar();
}