#include "Fase1.h"
#include <iostream>


Fase1::Fase1(): minInimigosMedios(3)
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
    criarObstaculos();
}

Fase1::~Fase1()
{

}

void Fase1::executar(float dt)
{
	desenharCenario();
    LEs->percorrer(dt, getTamanho());
	moveMapa(dt);
    gerenciarColisoes();
    if (p1->getCoords().x > 1000)acabou=true;
}

void Fase1::criarMolas()
{
    int i = 0;
    while (faseJson["layers"][i]["name"] != "Obstaculos")
    {
        i++;
    }
    for (int j = 0; j < 3; j++)
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
		LEs->incluirEntidade(obstaculos[obstaculos.size() - 1]);
    }
    for (int j = 0; j < 3; j++)
    {
        int qualObs;
        Obstaculo* p = new Plataforma;

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
        LEs->incluirEntidade(obstaculos[obstaculos.size() - 1]);
    }
}

void Fase1::criarMinInimigosMedios()
{
    int i = 0;
    std::mt19937 gen(rd());                     // motor aleatório (Mersenne Twister)
    while (faseJson["layers"][i]["name"] != "Spawn Inimigos")
    {
        i++;
    }
    for (int j = 0; j < minInimigosMedios; j++)
    {
        int lugar = 0;
        std::uniform_int_distribution<> quantos(0, faseJson["layers"][i]["objects"].size() - 1);
        do
        {
            lugar = quantos(gen); // gera um número aleatório
        } while (jaFoi[lugar] != 0);
		jaFoi[lugar] = 1; // marca que o ponto já foi usado
        Inimigo* inimigo = new BigEye;
        inimigo->setGerenciadorGrafico(Gerenciador_Grafico::getInstancia());
        inimigo->associaListaEntidades(LEs);
        inimigo->associaGerenciadorColisoes(getGC());
        inimigo->conhecerJogador(p1);
        inimigo->setCoords(sf::Vector2f((float)(faseJson["layers"][i]["objects"][lugar]["x"] * 3), (float)(faseJson["layers"][i]["objects"][lugar]["y"] * 3)));
        inimigos.push_back(inimigo);
        LEs->incluirEntidade(inimigos[inimigos.size() - 1]);
		incluirInimigoGC(inimigos[inimigos.size() - 1]);
    }
}

void Fase1::criarProjeteis()
{

}

void Fase1::criarInimigos()
{
    int sorteado = aleatoriza(0, 4); // gera um número aleatório entre 0 e 4

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
        int qualInimigo = aleatoriza(0, 1); // gera um número aleatório entre 0 e 1
        Inimigo* inimigo = nullptr;
        if (qualInimigo)inimigo = new Metall;
        else inimigo = new BigEye;
        
        do
        {
            qualInimigo = aleatoriza(0, faseJson["layers"][i]["objects"].size() - 1); // gera um número aleatório

		} while (jaFoi[qualInimigo] != 0);//verifica se o ponto já foi usado

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
    criarMinInimigosMedios();
}

void Fase1::criarObstaculos()
{
	jaFoi.clear(); // limpa o vetor de pontos já usados
    int sorteado = aleatoriza(0, 4); // gera um número aleatório entre 0 e 4

    int i = 0;
    while (faseJson["layers"][i]["name"] != "Obstaculos")
    {
        i++;
    }
    for (int j = 0; j < faseJson["layers"][i]["objects"].size(); j++)
    {
        jaFoi.push_back(0); // vetor para saber quais pontos já foram usados
    }
    criarMolas();
    for(int j=0; j<sorteado;j++)
    {
        int qualObs = aleatoriza(0, 10); // gera um número aleatório entre 0 e 10
        Obstaculo* p=nullptr;
        if (qualObs>5)p = new Mola;
        else p = new Plataforma;

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
		LEs->incluirEntidade(obstaculos[obstaculos.size() - 1]);
    }
}
