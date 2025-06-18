#include "Fase.h"
#include <iostream>
Fase::Fase() : tilesGid(), imagemTiles(), faseJson(), tileWidth(16), columns(18), tileCount(180), tilesRects(), GC(), p1(new Megaman), plataformas(), LEs(new ListaEntidades), minInimigosFaceis(3), jaFoi(), ultimoSprite(0), acabou(false), p2(nullptr), minObstaculosFaceis(3)
{
    setTamanho(sf::Vector2f(1280.f, 720.f));

    p1->setGerenciadorGrafico(Gerenciador_Grafico::getInstancia());
    p1->associaGerenciadorColisoes(&GC);
    p1->associaListaEntidades(LEs);
}

Fase::~Fase()
{
    jaFoi.clear();
    tilesGid.clear();
    tilesRects.clear();
    delete p1;
    delete p2;
    tilesSprites.clear();
    fundo1.clear();
    fundo2.clear();
    fundo3.clear();
    plataformas.clear();
    chao.clear();
    inimigos.clear();
    obstaculos.clear();
    LEs->LEs.limpar();
    delete LEs;
}

void Fase::gerenciarColisoes()
{
    GC.executar();
}

void Fase::criarInimigosFaceis()
{
    int i = 0;
    std::mt19937 gen(rd());                     // motor aleatório (Mersenne Twister)
    while (faseJson["layers"][i]["name"] != "Spawn Inimigos")
    {
        i++;
    }
    for (int j = 0; j < minInimigosFaceis; j++)
    {
        int lugar = 0;
        std::uniform_int_distribution<> quantos(0, faseJson["layers"][i]["objects"].size() - 1);
        do
        {
            lugar = quantos(gen); // gera um número aleatório
        } while (jaFoi[lugar] != 0);
        jaFoi[lugar] = 1; // marca que o ponto já foi usado
        Inimigo* inimigo = new Metall;
        inimigo->setGerenciadorGrafico(Gerenciador_Grafico::getInstancia());
        inimigo->associaListaEntidades(LEs);
        inimigo->associaGerenciadorColisoes(&GC);
        inimigo->conhecerJogador(p1);
        inimigo->setCoords(sf::Vector2f((float)(faseJson["layers"][i]["objects"][lugar]["x"] * 3), (float)(faseJson["layers"][i]["objects"][lugar]["y"] * 3)));
        inimigos.push_back(inimigo);
        LEs->incluirEntidade(inimigos[inimigos.size()-1]);
        GC.incluirInimigo(inimigos[inimigos.size() - 1]);

    }
}

void Fase::criarChao()
{
    int controle = 0;
    while (faseJson["layers"][controle]["name"] != "chao")
    {
        controle++;
    }
    for (int i = 0; i < faseJson["layers"][controle]["objects"].size(); i++)
    {
        Plataforma* p = new Plataforma;
        p->setGerenciadorGrafico(pGG->getInstancia());
        p->setCoords(sf::Vector2f((float)(faseJson["layers"][controle]["objects"][i]["x"] * 3), (float)faseJson["layers"][controle]["objects"][i]["y"] * 3));
        p->setTamanho(sf::Vector2f((float)faseJson["layers"][controle]["objects"][i]["width"] * 3, (float)faseJson["layers"][controle]["objects"][i]["height"] * 3));
        chao.push_back(p);
        GC.incluirObstaculo(p);
        if (chao.size() > 1 && chao[i]->getCoords().x + chao[i]->getTamanho().x > chao[ultimoSprite]->getCoords().x + chao[ultimoSprite]->getTamanho().x)ultimoSprite = i;
        
    }
    
    controle = 0;
    while (faseJson["layers"][controle]["name"] != "Mola")
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

void Fase::criarPlataformas()
{
    int i = 0;
    while (faseJson["layers"][i]["name"] != "Obstaculos")
    {
        i++;
    }
    for (int j = 0; j < minObstaculosFaceis; j++)
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

void Fase::desenharCenario()
{
    for (int i = 0; i < tilesSprites.size(); i++)
    {
        if (((tilesSprites[i].getPosition().x * tilesSprites[i].getScale().x) > getCoords().x - tilesSprites[i].getScale().x*2) && ((tilesSprites[i].getPosition().x) < getTamanho().x))
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
    std::string imagemRelativa = faseJson["tilesets"][0]["image"];
    std::string caminhoImagem = "Mapas/" + imagemRelativa;
    if (!imagemTiles.loadFromFile(caminhoImagem))
    {
        std::cerr << "Erro ao carregar imagem: " << faseJson["tilesets"][0]["image"] << std::endl;
    }
    columns = faseJson["tilesets"][0]["columns"];
    tileWidth = faseJson["tilesets"][0]["tilewidth"];
    for (int id = 0; id < faseJson["tilesets"][0]["tilecount"]; ++id) {
        int tu = id % columns;     // coluna
        int tv = id / columns;     // linha

        sf::IntRect rect(tu * tileWidth, tv * tileWidth, tileWidth, tileWidth);
        tilesRects.push_back(rect);
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

int Fase::aleatoriza(int limite1, int limite2)
{
    std::mt19937 gen(rd());                     // motor aleatório (Mersenne Twister)
    std::uniform_int_distribution<> dist(limite1, limite2); // faixa

    return dist(gen);
}

void Fase::moveMapa(float dt)
{
    sf::FloatRect rect1(p1->getCoords(), p1->getTamanho());
	
    sf::FloatRect rect2(getCoords(),getTamanho());
    

    if (rect1.intersects(rect2) && chao[ultimoSprite]->getCoords().x + chao[ultimoSprite]->getTamanho().x > rect2.width) // Movimento do personagem
    {
        if(rect1.left >= rect2.width/2)
        {
            p1->setCoords(sf::Vector2f(rect2.width / 2, rect1.top));
            for (int i = 0; i < chao.size(); i++)
            {
                chao[i]->setCoords(sf::Vector2f(chao[i]->getCoords().x - p1->getVelocidade() * dt, chao[i]->getCoords().y));
            }
            for (int i = 0; i < plataformas.size(); i++)
            {
                plataformas[i]->setCoords(sf::Vector2f(plataformas[i]->getCoords().x - p1->getVelocidade() * dt, plataformas[i]->getCoords().y));
            }
            for (int i = 0; i < tilesSprites.size(); i++)
            {
                tilesSprites[i].setPosition(tilesSprites[i].getPosition().x - p1->getVelocidade() * dt, tilesSprites[i].getPosition().y);
            }
            for (int i = 0; i < inimigos.size(); i++)
            {
                inimigos[i]->setCoords(sf::Vector2f(inimigos[i]->getCoords().x - p1->getVelocidade() * dt, inimigos[i]->getCoords().y));
            }
            for (int i = 0; i < obstaculos.size(); i++)
            {
                obstaculos[i]->setCoords(sf::Vector2f(obstaculos[i]->getCoords().x - p1->getVelocidade() * dt, obstaculos[i]->getCoords().y));
            }
        }
    }
}

void Fase::incluirInimigoGC(Inimigo* inimigo)
{
    GC.incluirInimigo(inimigo);
}

void Fase::incluirMegaGC(Megaman* mega)
{
    GC.incluirMegaman(mega);
}

void Fase::incluirObstaculoGC(Obstaculo* Obstaculo)
{
    GC.incluirObstaculo(Obstaculo);
}

Gerenciador_Colisoes* Fase::getGC()
{
    return &GC;
}

bool Fase::getAcabou()
{
    return acabou;
}
void Fase::setTwoPlayers()
{
	p2 = new Megaman(false);
	p2->setGerenciadorGrafico(Gerenciador_Grafico::getInstancia());
	p2->associaGerenciadorColisoes(&GC);
    p2->associaListaEntidades(LEs);
	p2->setCoords(p1->getCoords());
    p2->setExecutando(true);
	GC.incluirMegaman(p2);
	LEs->incluirEntidade(p2);
}
