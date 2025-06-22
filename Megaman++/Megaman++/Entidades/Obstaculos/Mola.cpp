#include "Mola.h"

Mola::Mola(): elasticidade(-200.f)
{
    setId(10);
	elasticidade = elasticidade*(rand()%3+1); // Força de impulso da mola
}

int Mola::indiceMola = -1;

Mola::~Mola()
{
}

void Mola::executar(float dt)
{
    sf::Vector2f posicao = getCoords();

    sofrerAcaoDaGravidade(dt);
    velVertical -= empuxo * dt; //Contrapõe a gravidade

    posicao.y += velVertical * dt;

    setCoords(posicao);
}

void Mola::obstaculizar(Personagem* pPers)
{
    if (!pPers) return;

    sf::FloatRect rectPers(pPers->getCoords(), pPers->getTamanho());
    sf::FloatRect rectMola(getCoords(), getTamanho());

    sf::Vector2f posPers = pPers->getCoords();
    sf::Vector2f tamPers = pPers->getTamanho();

    float velY = pPers->getVelVertical();
    float velX = pPers->getVelocidade();

    float topoPers = rectPers.top;
    float baixoPers = rectPers.top + rectPers.height;
    float topoMola = rectMola.top;
    float baixoMola = rectMola.top + rectMola.height;
    float esquerdaPers = rectPers.left;
    float direitaPers = rectPers.left + rectPers.width;
    float esquerdaMola = rectMola.left;
    float direitaMola = rectMola.left + rectMola.width;

    const float margem = 15.f; // Ajuste conforme necessário

    bool tocando = false;

    // --- COLISÃO POR CIMA ---
    if (velY > 0 && baixoPers - margem < topoMola && baixoPers > topoMola && direitaPers > esquerdaMola + margem && esquerdaPers < direitaMola - margem)
    {
        posPers.y = topoMola - tamPers.y;
        pPers->setCoords(posPers);
        pPers->setVelVertical(elasticidade);
        //tocando = true;
    }
    // --- COLISÃO POR BAIXO ---
    else if (velY < 0 && topoPers < baixoMola && topoPers > baixoMola - margem && direitaPers > esquerdaMola + margem && esquerdaPers < direitaMola - margem)
    {
        posPers.y = baixoMola;
        pPers->setCoords(posPers);
        pPers->setVelVertical(0);
    }
    // --- COLISÃO PELA ESQUERDA (separação de eixo X) ---
    else if (velX > 0 && direitaPers > esquerdaMola && esquerdaPers < esquerdaMola && baixoPers > topoMola + margem && topoPers < baixoMola - margem)
    {
        posPers.x = esquerdaMola - tamPers.x;
        pPers->setCoords(posPers);
        pPers->setVelocidade(0);
    }
    // --- COLISÃO PELA DIREITA (separação de eixo X) ---
    else if (velX < 0 && esquerdaPers < direitaMola && direitaPers > direitaMola && baixoPers > topoMola + margem && topoPers < baixoMola - margem)
    {
        posPers.x = direitaMola;
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

    const float margem = 10.f;

    bool tocando = false;
    
    // --- COLISÃO POR CIMA ---
    if (baixoPers - margem < topoPlat && baixoPers > topoPlat && direitaPers > esquerdaPlat + margem && esquerdaPers < direitaPlat - margem)
    {
        posPers.y = topoPlat - tamPers.y;
        pPers->setCoords(posPers);
		pPers->setVelVertical(forca); // Impulso para cima ao tocar na mola
        //tocando = true;
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
    else if (esquerdaPers < direitaPlat && direitaPers > direitaPlat && baixoPers > topoPlat + margem * 3 && topoPers < baixoPlat - margem * 3)
    {
        posPers.x = direitaPlat;
        pPers->setCoords(posPers);
    }

    pPers->setNoChao(tocando);*/
}

std::string Mola::getTextureFile()
{
    return "Sprites/Obstaculos/Mola.png";
}

void Mola::salvar()
{
    int lugar = getId();
    dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()]["elasticidade"] = elasticidade;
    Obstaculo::salvar();
}

void Mola::carregar()
{
    int lugar = getId();
    indiceAtual = ++indiceMola;
    elasticidade = dadosSalvos["id"][lugar][indiceAtual]["elasticidade"];
    Obstaculo::carregar();
}
