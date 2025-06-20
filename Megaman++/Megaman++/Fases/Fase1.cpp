#include "Fase1.h"
#include <iostream>


Fase1::Fase1(): minInimigosMedios(3), minObsMolas(3)
{
    std::fstream jsonFile("Mapas/mapa1.tmj");
    if (jsonFile.is_open()) {
        jsonFile >> faseJson;
        jsonFile.close();
    }
    else
    {
        std::cout << "Erro ao abrir o arquivo JSON." << std::endl;
    }
	separaSprites();
    std::cout << "desenhou sprites1." << std::endl;
    criarChao();
    std::cout << "criou o chao 1." << std::endl;
	quantidadeLayers = faseJson["layers"].size();
    int i = 0;
    
    while (faseJson["layers"][i]["name"] != "Spawn Player" && i< quantidadeLayers)
    {
		i++;
    }
    if(i>= quantidadeLayers)
    {
        std::cout << "Erro tentar acaha camada Spawn Player." << std::endl;
    }
    else
    {
        p1->setCoords(sf::Vector2f((float)(faseJson["layers"][i]["objects"][0]["x"] * 3), (float)(faseJson["layers"][i]["objects"][0]["y"] * 3)));
	}
    p1->setExecutando(true);
    if(!p1)std::cout << "Erro ao criar player." << std::endl;
    incluirMegaGC(p1);
	LEs.incluirEntidade(p1);
    
    criarInimigos();
    std::cout << "criou inimigos 1." << std::endl;
    criarObstaculos();
    
    
}

Fase1::~Fase1()
{

}

void Fase1::executar(float dt)
{
	desenharCenario();
    LEs.percorrer(dt, getTamanho());
	moveMapa(dt);
    gerenciarColisoes();
    if (p1->getCoords().x > 1000)acabou=true;
}

void Fase1::criarMolas()
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
        for (int j = 0; j < minObsMolas; j++)
        {
            int qualObs;
            Obstaculo* p = new Mola;

            do
            {
                qualObs = aleatoriza(0, faseJson["layers"][i]["objects"].size() - 1); // gera um número aleatório

            } while (jaFoi[qualObs] != 0);//verifica se o ponto já foi usado
            jaFoi[qualObs] = 1; // marca que o ponto já foi usado
            p->setGerenciadorGrafico(pGG->getInstancia());
            p->setCoords(sf::Vector2f((float)(faseJson["layers"][i]["objects"][qualObs]["x"] * 3), (float)faseJson["layers"][i]["objects"][qualObs]["y"] * 3));
            p->setTamanho(sf::Vector2f((float)faseJson["layers"][i]["objects"][qualObs]["width"] * 3, (float)faseJson["layers"][i]["objects"][qualObs]["height"] * 3));
            obstaculos.push_back(p);
            incluirObstaculoGC(p);
            LEs.incluirEntidade(obstaculos[obstaculos.size() - 1]);
        }
    }
    
    
}

void Fase1::criarMinInimigosMedios()
{
    int i = 0;
    while (faseJson["layers"][i]["name"] != "Spawn Inimigos" && i< quantidadeLayers)
    {
        i++;
    }
    if (i >= quantidadeLayers)
    {
        std::cout << "Erro tentar acaha camada Spawn Inimigos." << std::endl;
    }
    else
    {
        for (int j = 0; j < minInimigosMedios; j++)
        {
            int lugar = 0;
            do
            {
                lugar = aleatoriza(0, faseJson["layers"][i]["objects"].size() - 1); // gera um número aleatório
            } while (jaFoi[lugar] != 0);
            jaFoi[lugar] = 1; // marca que o ponto já foi usado
            Inimigo* inimigo = new BigEye;
            inimigo->setGerenciadorGrafico(Gerenciador_Grafico::getInstancia());
            inimigo->associaListaEntidades(&LEs);
            inimigo->associaGerenciadorColisoes(getGC());
            inimigo->conhecerJogador(p1);
            inimigo->setCoords(sf::Vector2f((float)(faseJson["layers"][i]["objects"][lugar]["x"] * 3), (float)(faseJson["layers"][i]["objects"][lugar]["y"] * 3)));
            inimigos.push_back(inimigo);
            LEs.incluirEntidade(inimigos[inimigos.size() - 1]);
            incluirInimigoGC(inimigos[inimigos.size() - 1]);
        }
    }
    
}


void Fase1::criarInimigos()
{
	
    int sorteado = aleatoriza(0, 4); // gera um número aleatório entre 0 e 4
	jaFoi.clear(); // limpa o vetor de pontos já usados
    int i = 0;
    while (faseJson["layers"][i]["name"] != "Spawn Inimigos" && i< quantidadeLayers)
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
            int qualInimigo = aleatoriza(0, 1); // gera um número aleatório entre 0 e 1
            bool eMetall = (qualInimigo == 0); // se for 0, é Metall, senão é BigEye
            if (eMetall) minInimigosFaceis++; // incrementa o número de Metall se for Metall
            else minInimigosMedios++; // incrementa o número de BigEye se for BigEye
        }
        criarInimigosFaceis();

        criarMinInimigosMedios();
    }
    
    
}

void Fase1::criarObstaculos()
{
	jaFoi.clear(); // limpa o vetor de pontos já usados
    int sorteado = aleatoriza(0, 4); // gera um número aleatório entre 0 e 4

    int i = 0;
    while (faseJson["layers"][i]["name"] != "Obstaculos" && i<quantidadeLayers)
    {
        i++;
    }
    if (i >= quantidadeLayers)
    {
        std::cout << "Erro tentar acaha camada Obstaculos." << std::endl;
    }
    else
    {
        for (int j = 0; j < faseJson["layers"][i]["objects"].size(); j++)
        {
            jaFoi.push_back(0); // vetor para saber quais pontos já foram usados
        }
        for (int j = 0; j < sorteado; j++)
        {
            int qualObs = aleatoriza(0, 10); // gera um número aleatório entre 0 e 10
            bool eMola = (qualObs > 5); // se for maior que 5, é mola, senão é plataforma
            
            if (eMola)minObsMolas++; // incrementa o número de molas se for mola
            else minObstaculosFaceis++; // incrementa o número de plataformas se for plataforma
        }
		
        criarMolas();
        
        criarPlataformas();
        
    }
}
