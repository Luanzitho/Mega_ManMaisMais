#include "Fase.h"
#include <iostream>
Fase::Fase() : tilesGid(), imagemTiles(), faseJson(), tileWidth(16), columns(18), tileCount(180), tilesRects(), GC(), p1(new Megaman), plataformas(), LEs(new ListaEntidades)
{
    met = new Metall();
    big = new BigEye();
	mola = new Mola();

    p1->setCoords(sf::Vector2f(400.f, 400.f));
    p1->setGerenciadorGrafico(Gerenciador_Grafico::getInstancia());
    p1->associaGerenciadorColisoes(&GC);
    p1->associaListaEntidades(LEs);
    GC.incluirMegaman(p1);
    //p1->setGerenciadorColisoes(&GC);
    LEs->incluirEntidade(p1);

    met->setCoords(sf::Vector2f(700.f, 580.f));
    met->associaListaEntidades(LEs);
    met->associaGerenciadorColisoes(&GC);
    met->setGerenciadorGrafico(Gerenciador_Grafico::getInstancia());
    met->conhecerJogador(p1);

    big->setCoords(sf::Vector2f(400.f, 50.f));
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
    int x;
    int x2 = 0;

    for (int y = 0; y < faseJson["layers"][0]["height"]; y++)
    {
        if (x2 < tilesGid.size())
        {
            for (x = 0; x < faseJson["layers"][0]["width"]; x++, x2++)
            {
                int gid = tilesGid[x2]; // valor vindo do mapa
                if (gid > 0 && gid<tilesRects.size()) {
                    sf::Sprite sprite;
                    sprite.setTexture(imagemTiles);
                    sprite.setTextureRect(tilesRects[gid-1]);
                    sprite.setPosition((float)(x * 48), (float)(y * 48));
                    sprite.setScale(3.0f, 3.0f); // Escala para 3x o tamanho original
                    pGG->desenhaSprite(sprite);
                }
            }
        }
    }
}

void Fase::separaSprites()
{
    tilesGid = faseJson["layers"][0]["data"].get<std::vector<int>>();
    std::string imagemRelativa = faseJson["tilesets"][0]["image"];
    std::string caminhoImagem = "Mapas/" + imagemRelativa;
    if (!imagemTiles.loadFromFile(caminhoImagem))
    {
        std::cerr << "Erro ao carregar imagem: " << faseJson["tilesets"][0]["image"] << std::endl;
    }
    for (int id = 0; id < faseJson["tilesets"][0]["tilecount"]; ++id) {
		//std::cout << "entrou" << std::endl;
        int tu = id % columns;     // coluna
        int tv = id / columns;     // linha

        sf::IntRect rect(tu * tileWidth, tv * tileWidth, tileWidth, tileWidth);
        tilesRects.push_back(rect);
        //tilesTextures.push_back(recortarTextura(imagemTiles, rect));
    }
}

std::string Fase::getTextureFile()//rever o que retornar para desenhar o mapa
{
    return faseJson["tilesets"][0]["image"];
}
