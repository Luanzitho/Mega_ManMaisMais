#include "Fase.h"
#include <iostream>
Fase::Fase() : tilesGid(), imagemTiles(), faseJson(), tileWidth(16), columns(18), tileCount(180), tilesRects(), GC(), p1(new Megaman), plataformas(), LEs(new ListaEntidades)
{
    met = new Metall();
    big = new BigEye();
	mola = new Mola();
	posPlayer1 = p1->getCoords();
	setTamanho(sf::Vector2f(1100.f, 720.f));

	inimigos.push_back(met);
	inimigos.push_back(big);

    //p1->setCoords(sf::Vector2f(400.f, 400.f));
    p1->setGerenciadorGrafico(Gerenciador_Grafico::getInstancia());
    p1->associaGerenciadorColisoes(&GC);
    p1->associaListaEntidades(LEs);
    GC.incluirMegaman(p1);
    //p1->setGerenciadorColisoes(&GC);
    LEs->incluirEntidade(p1);

    //met->setCoords(sf::Vector2f(700.f, 580.f));
    met->associaListaEntidades(LEs);
    met->associaGerenciadorColisoes(&GC);
    met->setGerenciadorGrafico(Gerenciador_Grafico::getInstancia());
    met->conhecerJogador(p1);

    //big->setCoords(sf::Vector2f(400.f, 50.f));
    big->setGerenciadorGrafico(Gerenciador_Grafico::getInstancia());
    big->conhecerJogador(p1);

    LEs->incluirEntidade(met);
    LEs->incluirEntidade(big);

    GC.incluirInimigo(met);
    GC.incluirInimigo(big);
}

Fase::~Fase()
{
}
void Fase::gerenciarColisoes()
{
}

void Fase::criarInimigosFaceis()
{
}

void Fase::criarPlataformas()
{
	int controle = 0;
    while(faseJson["layers"][controle]["name"]!= "chao")
    {
		controle++;
    }
    for (int i = 0; i < faseJson["layers"][controle]["objects"].size(); i++)
    {
        Plataforma* p = new Plataforma;
        p->setGerenciadorGrafico(pGG->getInstancia());
        p->setCoords(sf::Vector2f((float)(faseJson["layers"][controle]["objects"][i]["x"] * 3), (float)faseJson["layers"][controle]["objects"][i]["y"] * 3));
        p->setTamanho(sf::Vector2f((float)faseJson["layers"][controle]["objects"][i]["width"] * 3, (float)faseJson["layers"][controle]["objects"][i]["height"] * 3));
        plataformas.push_back(p);
        //std::cout << "Plataforma criada: " << faseJson["layers"][controle]["objects"][i]["x"] << ", " << faseJson["layers"][1]["objects"][i]["y"] << std::endl;
        GC.incluirObstaculo(p);
        //faseJson["layers"][1]["objects"];
    }
    controle = 0;
    while (faseJson["layers"][controle]["name"] != "Obstaculos")
    {
        controle++;
    }
    for (int i = 0; i < faseJson["layers"][controle]["objects"].size(); i++)
    {
        Plataforma* p = new Plataforma;
        p->setGerenciadorGrafico(pGG->getInstancia());
        p->setCoords(sf::Vector2f((float)(faseJson["layers"][controle]["objects"][i]["x"] * 3), (float)faseJson["layers"][controle]["objects"][i]["y"] * 3));
        p->setTamanho(sf::Vector2f((float)faseJson["layers"][controle]["objects"][i]["width"] * 3, (float)faseJson["layers"][controle]["objects"][i]["height"] * 3));
        plataformas.push_back(p);
        //std::cout << "Plataforma criada: " << faseJson["layers"][controle]["objects"][i]["x"] << ", " << faseJson["layers"][1]["objects"][i]["y"] << std::endl;
        GC.incluirObstaculo(p);
        //faseJson["layers"][1]["objects"];
    }
    controle = 0;
    while(faseJson["layers"][controle]["name"]!="Mola")
    {
        controle++;
    }
    for (int i = 0; i < faseJson["layers"][controle]["objects"].size(); i++)
    {
        Obstaculo* m = new Mola;
        m->setGerenciadorGrafico(pGG->getInstancia());
        m->setCoords(sf::Vector2f((float)(faseJson["layers"][controle]["objects"][i]["x"] * 3), (float)faseJson["layers"][controle]["objects"][i]["y"] * 3));
        m->setTamanho(sf::Vector2f((float)faseJson["layers"][controle]["objects"][i]["width"] * 3, (float)faseJson["layers"][controle]["objects"][i]["height"] * 3));
        obstaculos.push_back(m);
        std::cout << "Plataforma criada: " << faseJson["layers"][controle]["objects"][i]["x"] << ", " << faseJson["layers"][1]["objects"][i]["y"] << std::endl;
        GC.incluirObstaculo(m);
    }

}

void Fase::desenharCenario()
{
    for (int i = 0; i < tilesSprites.size(); i++)
    {
        if(((tilesSprites[i].getPosition().x*3.f)>0.f) && ((tilesSprites[i].getPosition().x) < 1100.f))
        pGG->desenhaSprite(tilesSprites[i]);
    }
}
void Fase::pegarCamada(int i)
{
    tilesGid = faseJson["layers"][i]["data"].get<std::vector<int>>();
    int x;
    int x2 = 0;
    for (int y = 0; y < faseJson["layers"][i]["height"]; y++)
    {
        if (x2 < tilesGid.size())
        {
            for (x = 0; x < faseJson["layers"][i]["width"]; x++, x2++)
            {
                int gid = tilesGid[x2]; // valor vindo do mapa
                if (gid > 0 && gid < tilesRects.size()) {
                    sf::Sprite sprite;
                    sprite.setTexture(imagemTiles);
                    sprite.setTextureRect(tilesRects[gid - 1]);
                    sprite.setPosition((float)(x * 48), (float)(y * 48));
                    sprite.setScale(3.0f, 3.0f); // Escala para 3x o tamanho original
                    tilesSprites.push_back(sprite);
                    //pGG->desenhaSprite(sprite);
                }
            }
        }
    }
}
void Fase::separaSprites()
{
    //tilesGid = faseJson["layers"][0]["data"].get<std::vector<int>>();
    std::string imagemRelativa = faseJson["tilesets"][0]["image"];
    std::string caminhoImagem = "Mapas/" + imagemRelativa;
    if (!imagemTiles.loadFromFile(caminhoImagem))
    {
        std::cerr << "Erro ao carregar imagem: " << faseJson["tilesets"][0]["image"] << std::endl;
    }
    columns = faseJson["tilesets"][0]["columns"];
    tileWidth = faseJson["tilesets"][0]["tilewidth"];
    for (int id = 0; id < faseJson["tilesets"][0]["tilecount"]; ++id) {
		//std::cout << "entrou" << std::endl;
        int tu = id % columns;     // coluna
        int tv = id / columns;     // linha

        sf::IntRect rect(tu * tileWidth, tv * tileWidth, tileWidth, tileWidth);
        tilesRects.push_back(rect);
        //tilesTextures.push_back(recortarTextura(imagemTiles, rect));
    }
    int i = 0;
    while (faseJson["layers"][i]["name"] != "BackGround1")i++;
    pegarCamada(i);
    i = 0;
    while (faseJson["layers"][i]["name"] != "BackGround2")i++;
    pegarCamada(i);
    i = 0;
    while (faseJson["layers"][i]["name"] != "BackGround3")i++;
    pegarCamada(i);
}

std::string Fase::getTextureFile()//rever o que retornar para desenhar o mapa
{
    return faseJson["tilesets"][0]["image"];
}

void Fase::moveMapa()
{
    if (posPlayer1.x != p1->getCoords().x) // Exemplo de movimento do personagem
    {
        for(int i =0; i<plataformas.size();i++)
        {
			plataformas[i]->setCoords(sf::Vector2f(plataformas[i]->getCoords().x + (posPlayer1.x - p1->getCoords().x), plataformas[i]->getCoords().y));
        }
        for (int i = 0; i < tilesSprites.size(); i++)
        {
            tilesSprites[i].setPosition(tilesSprites[i].getPosition().x + (posPlayer1.x - p1->getCoords().x), tilesSprites[i].getPosition().y);
        }
        for(int i=0; i< inimigos.size();i++)
        {
            inimigos[i]->setCoords(sf::Vector2f (inimigos[i]->getCoords().x + (posPlayer1.x - p1->getCoords().x), inimigos[i]->getCoords().y));
        }
        for (int i = 0; i < obstaculos.size(); i++)
        {
            obstaculos[i]->setCoords(sf::Vector2f(obstaculos[i]->getCoords().x + (posPlayer1.x - p1->getCoords().x), obstaculos[i]->getCoords().y));
        }
		posPlayer1 = p1->getCoords();
	}
}
