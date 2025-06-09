#include "Plataforma.h"

Plataforma::Plataforma(): altura(50)
{
	setTamanho(sf::Vector2f(50.f, float(altura)));
}

Plataforma::~Plataforma()
{
}

void Plataforma::executar(float dt)
{
}

void Plataforma::obstaculizar(Personagem* pPers)
{
    if (!pPers) return;

    sf::FloatRect rectPers(pPers->getCoords(), pPers->getTamanho());
    sf::FloatRect rectPlat(getCoords(), getTamanho());

    sf::Vector2f posPers = pPers->getCoords();
    sf::Vector2f tamPers = pPers->getTamanho();

    float velY = pPers->getVelVertical();

    float topoPers = rectPers.top;
    float baixoPers = rectPers.top + rectPers.height;
    float topoPlat = rectPlat.top;
    float baixoPlat = rectPlat.top + rectPlat.height;
    float esquerdaPers = rectPers.left;
    float direitaPers = rectPers.left + rectPers.width;
    float esquerdaPlat = rectPlat.left;
    float direitaPlat = rectPlat.left + rectPlat.width;

    const float margem = 8.f;

    bool tocando = false;

    // --- COLISÃO POR CIMA ---
    if (baixoPers - margem < topoPlat && baixoPers > topoPlat && direitaPers > esquerdaPlat + margem && esquerdaPers < direitaPlat - margem)
    {
        posPers.y = topoPlat - tamPers.y;
        pPers->setCoords(posPers);
        pPers->setVelVertical(0);
        tocando = true;
    }
    // --- COLISÃO POR BAIXO ---
    else if (velY < 0 && topoPers > baixoPlat - margem && direitaPers > esquerdaPlat + margem && esquerdaPers < direitaPlat - margem)
    {
        posPers.y = baixoPlat;
        pPers->setCoords(posPers);
        pPers->setVelVertical(0);
    }
    // --- COLISÃO PELA ESQUERDA ---
    else if (direitaPers > esquerdaPlat && esquerdaPers < esquerdaPlat && baixoPers > topoPlat + margem * 2 && topoPers < baixoPlat - margem * 2)
    {
        posPers.x = esquerdaPlat - tamPers.x;
        pPers->setCoords(posPers);
    }
    // --- COLISÃO PELA DIREITA ---
    else if (esquerdaPers < direitaPlat && direitaPers > direitaPlat && baixoPers > topoPlat + margem * 2 && topoPers < baixoPlat - margem * 2)
    {
        posPers.x = direitaPlat;
        pPers->setCoords(posPers);
    }

    pPers->setNoChao(tocando);
}

std::string Plataforma::getTextureFile()
{
	return "Sprites/Obstaculos/Plataforma1.png";
}