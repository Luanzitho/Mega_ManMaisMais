#include "Fase.h"
#include <iostream>
Fase::Fase() : tilesGid(), imagemTiles(), faseJson(), tileWidth(16), columns(18), tileCount(180), tilesRects(), GC(), p1(new Megaman), plataformas()
{
    p1->setCoords(sf::Vector2f(550.f, 580.f));
    p1->setGerenciadorGrafico(pGG);
    GC.incluirMegaman(p1);
    //p1->setGerenciadorColisoes(&GC);
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
    for(int i=0; i< faseJson["layers"][1]["objects"].size();i++)
    {
        Plataforma* p= new Plataforma;
		p->setGerenciadorGrafico(pGG);
		p->setCoords(sf::Vector2f(faseJson["layers"][1]["objects"][i]["x"], faseJson["layers"][1]["objects"][i]["y"]));
		p->setTamanho(sf::Vector2f(faseJson["layers"][1]["objects"][i]["width"], faseJson["layers"][1]["objects"][i]["height"]));
        plataformas.push_back(p);
		std::cout << "Plataforma criada: " << faseJson["layers"][1]["objects"][i]["x"] << ", " << faseJson["layers"][1]["objects"][i]["y"] << std::endl;
        GC.incluirObstaculo(p);
        //faseJson["layers"][1]["objects"];
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
