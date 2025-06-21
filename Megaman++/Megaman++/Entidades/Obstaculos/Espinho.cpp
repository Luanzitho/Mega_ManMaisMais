#include "Espinho.h"

Espinho::Espinho(): danosidade(2)
{
	danoso = true;
    setId(11);
    setTamanho(sf::Vector2f(64.f, 64.f));
}

Espinho::~Espinho()
{
}

void Espinho::executar(float dt)
{
    sf::Vector2f posicao = getCoords();

    sofrerAcaoDaGravidade(dt);
    velVertical -= empuxo * dt; //Contrapõe a gravidade

    posicao.y += velVertical * dt;

    setCoords(posicao);
}

void Espinho::obstaculizar(Personagem* pPers)
{
    if (!pPers) return;

    sf::FloatRect rectPers(pPers->getCoords(), pPers->getTamanho());
    sf::FloatRect rectEspinho(getCoords(), getTamanho());

    sf::Vector2f posPers = pPers->getCoords();
    sf::Vector2f tamPers = pPers->getTamanho();

    float velY = pPers->getVelVertical();
    float velX = pPers->getVelocidade();

    float topoPers = rectPers.top;
    float baixoPers = rectPers.top + rectPers.height;
    float topoEspinho = rectEspinho.top;
    float baixoEspinho = rectEspinho.top + rectEspinho.height;
    float esquerdaPers = rectPers.left;
    float direitaPers = rectPers.left + rectPers.width;
    float esquerdaEspinho = rectEspinho.left;
    float direitaEspinho = rectEspinho.left + rectEspinho.width;

    const float margem = 8.f;

    bool tocando = false;

    // --- COLISÃO POR CIMA ---
    if (velY > 0 && baixoPers - margem < topoEspinho && baixoPers > topoEspinho && direitaPers > esquerdaEspinho + margem && esquerdaPers < direitaEspinho - margem)
    {
        posPers.y = topoEspinho - tamPers.y;
        pPers->setCoords(posPers);
        if(danoso)
            pPers->machucar(danosidade);
        pPers->setVelVertical(0);
        tocando = true;
    }
    // --- COLISÃO POR BAIXO ---
    else if (velY < 0 && topoPers < baixoEspinho && topoPers > baixoEspinho - margem && direitaPers > esquerdaEspinho + margem && esquerdaPers < direitaEspinho - margem)
    {
        posPers.y = baixoEspinho;
        pPers->setCoords(posPers);
        pPers->setVelVertical(0);
    }
    // --- COLISÃO PELA ESQUERDA (separação de eixo X) ---
    else if (velX > 0 && direitaPers > esquerdaEspinho && esquerdaPers < esquerdaEspinho && baixoPers > topoEspinho + margem && topoPers < baixoEspinho - margem)
    {
        posPers.x = esquerdaEspinho - tamPers.x;
        pPers->setCoords(posPers);
        pPers->setVelocidade(0);
    }
    // --- COLISÃO PELA DIREITA (separação de eixo X) ---
    else if (velX < 0 && esquerdaPers < direitaEspinho && direitaPers > direitaEspinho && baixoPers > topoEspinho + margem && topoPers < baixoEspinho - margem)
    {
        posPers.x = direitaEspinho;
        pPers->setCoords(posPers);
        pPers->setVelocidade(0);
    }

    pPers->setNoChao(tocando);
    /*if (!pPers) return; //LÓGICA ANTIGA

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
        pPers->machucar(2);
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

    pPers->setNoChao(tocando);*/
}

std::string Espinho::getTextureFile()
{
    return "Sprites/Obstaculos/Espinho1.png";
}

void Espinho::salvar()
{
    int lugar = getId();
    dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()]["danosidade"] = danosidade;
    Obstaculo::salvar();
}