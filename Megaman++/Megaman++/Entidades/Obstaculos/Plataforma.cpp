#include "Plataforma.h"
#include <time.h>

Plataforma::Plataforma()
{
    srand(time(NULL));
    setId(9);
    altura = 50 * (rand() % 3 + 1);
  
    setTamanho(sf::Vector2f(50.f, altura));
}

int Plataforma::indicePlataforma = -1;

Plataforma::~Plataforma()
{
}

void Plataforma::executar(float dt)
{
    sf::Vector2f posicao = getCoords();

    sofrerAcaoDaGravidade(dt);
    velVertical -= empuxo * dt; //Contrapõe a gravidade

    posicao.y += velVertical * dt;

    setCoords(posicao);
}

void Plataforma::obstaculizar(Personagem* pPers)
{
    if (!pPers) return;

    sf::FloatRect rectPers(pPers->getCoords(), pPers->getTamanho());
    sf::FloatRect rectPlat(getCoords(), getTamanho());

    sf::Vector2f posPers = pPers->getCoords();
    sf::Vector2f tamPers = pPers->getTamanho();

    float velY = pPers->getVelVertical();
    float velX = pPers->getVelocidade();

    float topoPers = rectPers.top;
    float baixoPers = rectPers.top + rectPers.height;
    float topoPlat = rectPlat.top;
    float baixoPlat = rectPlat.top + rectPlat.height;
    float esquerdaPers = rectPers.left;
    float direitaPers = rectPers.left + rectPers.width;
    float esquerdaPlat = rectPlat.left;
    float direitaPlat = rectPlat.left + rectPlat.width;

    const float margem = 15.f;

    bool tocando = false;

    // --- COLISÃO POR CIMA ---
    if (velY > 0 && baixoPers - margem < topoPlat && baixoPers > topoPlat && direitaPers > esquerdaPlat + margem && esquerdaPers < direitaPlat - margem)
    {
        posPers.y = topoPlat - tamPers.y;
        pPers->setCoords(posPers);
        pPers->setVelVertical(0);
        tocando = true;
    }
    // --- COLISÃO POR BAIXO ---
    else if (velY < 0 && topoPers < baixoPlat && topoPers > baixoPlat - margem && direitaPers > esquerdaPlat + margem && esquerdaPers < direitaPlat - margem)
    {
        posPers.y = baixoPlat;
        pPers->setCoords(posPers);
        pPers->setVelVertical(0);
    }
    // --- COLISÃO PELA ESQUERDA (separação de eixo X) ---
    else if (velX > 0 && direitaPers > esquerdaPlat && esquerdaPers < esquerdaPlat && baixoPers > topoPlat + margem && topoPers < baixoPlat - margem)
    {
        posPers.x = esquerdaPlat - tamPers.x;
        pPers->setCoords(posPers);
        pPers->setVelocidade(0);
    }
    // --- COLISÃO PELA DIREITA (separação de eixo X) ---
    else if (velX < 0 && esquerdaPers < direitaPlat && direitaPers > direitaPlat && baixoPers > topoPlat + margem && topoPers < baixoPlat - margem)
    {
        posPers.x = direitaPlat;
        pPers->setCoords(posPers);
        pPers->setVelocidade(0);
    }

    pPers->setNoChao(tocando);
}

std::string Plataforma::getTextureFile()
{
    if (altura == 50)
        return "Sprites/Obstaculos/Plataforma1.png";
    else if (altura == 100)
        return "Sprites/Obstaculos/Plataforma2.png";
    else
        return "Sprites/Obstaculos/Plataforma3.png";
}

const float Plataforma::getAltura()
{
    return altura;
}

void Plataforma::salvar()
{
    int lugar = getId();
    dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()]["altura"] = altura;
	Obstaculo::salvar();
}

void Plataforma::carregar()
{
    int lugar = getId();
    indiceAtual = ++indicePlataforma;
    altura = dadosSalvos["id"][lugar][indiceAtual]["altura"];
    setTamanho(sf::Vector2f(50.f, altura));
    
    Obstaculo::carregar();
}
