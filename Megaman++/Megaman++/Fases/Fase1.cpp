#include "Fase1.h"
#include <iostream>


Fase1::Fase1(): minBigEyes(3), minMolas(3)
{
    setId(13);
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
    GC.incluirMegaman(p1);
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
    pontuacao = p1->getPontos();

    if ((!p1->getVivo() && !p2) || (!p1->getVivo() && !p2->getVivo())) morreu = true;
	GC.executar();
    if (p1->getCoords().x > 1100)acabou=true;
    
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
        for (int j = 0; j < minMolas; j++)
        {
            int qualObs;
            Obstaculo* p = new Mola;

            do
            {
                qualObs = aleatoriza(0, faseJson["layers"][i]["objects"].size() - 1); // gera um n�mero aleat�rio

            } while (jaFoi[qualObs] != 0);//verifica se o ponto j� foi usado
            jaFoi[qualObs] = 1; // marca que o ponto j� foi usado
            p->setGerenciadorGrafico(pGG->getInstancia());
            p->setCoords(sf::Vector2f((float)(faseJson["layers"][i]["objects"][qualObs]["x"] * 3), (float)faseJson["layers"][i]["objects"][qualObs]["y"] * 3));
            p->setTamanho(sf::Vector2f((float)faseJson["layers"][i]["objects"][qualObs]["width"] * 3, (float)faseJson["layers"][i]["objects"][qualObs]["height"] * 3));
            obstaculos.push_back(p);
			GC.incluirObstaculo(p);
            LEs.incluirEntidade(obstaculos[obstaculos.size() - 1]);
        }
    }
    
    
}

void Fase1::criarBigEyes()
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
        for (int j = 0; j < minBigEyes; j++)
        {
            int lugar = 0;
            do
            {
                lugar = aleatoriza(0, faseJson["layers"][i]["objects"].size() - 1); // gera um n�mero aleat�rio
            } while (jaFoi[lugar] != 0);
            jaFoi[lugar] = 1; // marca que o ponto j� foi usado
            Inimigo* inimigo = new BigEye;
            inimigo->setGerenciadorGrafico(Gerenciador_Grafico::getInstancia());
            inimigo->associaListaEntidades(&LEs);
            inimigo->associaGerenciadorColisoes(&GC);
            inimigo->conhecerJogador(p1);
            inimigo->setCoords(sf::Vector2f((float)(faseJson["layers"][i]["objects"][lugar]["x"] * 3), (float)(faseJson["layers"][i]["objects"][lugar]["y"] * 3)));
            inimigos.push_back(inimigo);
            LEs.incluirEntidade(inimigos[inimigos.size() - 1]);
			GC.incluirInimigo(inimigos[inimigos.size() - 1]);
        }
    }
    
}


void Fase1::criarInimigos()
{
	
    int sorteado = aleatoriza(0, 4); // gera um n�mero aleat�rio entre 0 e 4
	jaFoi.clear(); // limpa o vetor de pontos j� usados
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
            jaFoi.push_back(0); // vetor para saber quais pontos j� foram usados
        }

        for (int j = 0; j < sorteado; j++)
        {
            int qualInimigo = aleatoriza(0, 1); // gera um n�mero aleat�rio entre 0 e 1
            bool eMetall = (qualInimigo == 0); // se for 0, � Metall, sen�o � BigEye
            if (eMetall) minMetalls++; // incrementa o n�mero de Metall se for Metall
            else minBigEyes++; // incrementa o n�mero de BigEye se for BigEye
        }
        criarMetalls();

        criarBigEyes();
    }
    
    
}

void Fase1::criarObstaculos()
{
	jaFoi.clear(); // limpa o vetor de pontos j� usados
    int sorteado = aleatoriza(0, 1); // gera um n�mero aleat�rio entre 0 e 4

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
            jaFoi.push_back(0); // vetor para saber quais pontos j� foram usados
        }
        for (int j = 0; j < sorteado; j++)
        {
            int qualObs = aleatoriza(0, 10); // gera um n�mero aleat�rio entre 0 e 10
            bool eMola = (qualObs > 5); // se for maior que 5, � mola, sen�o � plataforma
            
            if (eMola) minMolas++; // incrementa o n�mero de molas se for mola
            else minPlataformas++; // incrementa o n�mero de plataformas se for plataforma
        }
		
        criarMolas();
        
        criarPlataformas();
        
    }
}

void Fase1::salvar()
{
    int lugar = getId();
    
    dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()]["minInimigosMedios"] = minBigEyes;
    dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()-1]["minObsMolas"] = minMolas;
    Fase::salvar();
}

void Fase1::carregar()
{
    Fase::carregar();
}
