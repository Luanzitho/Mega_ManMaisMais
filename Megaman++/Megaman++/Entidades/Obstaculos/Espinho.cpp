#include "Espinho.h"

Espinho::Espinho(): danosidade(2)
{
	danoso = true;
    setId(11);
    setTamanho(sf::Vector2f(64.f, 64.f));
}

int Espinho::indiceEspinho = -1;

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

void Espinho::obstaculizar(Entidade* pEnti)
{
    if (!pEnti) return;

    sf::FloatRect rectEnti(pEnti->getCoords(), pEnti->getTamanho());
    sf::FloatRect rectEspinho(getCoords(), getTamanho());

    sf::Vector2f posEnti = pEnti->getCoords();
    sf::Vector2f tamEnti = pEnti->getTamanho();

    float velY = pEnti->getVelVertical();
    float velX = pEnti->getVelocidade();

    float topoEnti = rectEnti.top;
    float baixoEnti = rectEnti.top + rectEnti.height;
    float topoEspinho = rectEspinho.top;
    float baixoEspinho = rectEspinho.top + rectEspinho.height;
    float esquerdaEnti = rectEnti.left;
    float direitaEnti = rectEnti.left + rectEnti.width;
    float esquerdaEspinho = rectEspinho.left;
    float direitaEspinho = rectEspinho.left + rectEspinho.width;

    const float margem = 8.f;

    bool tocando = false;

    // --- COLISÃO POR CIMA ---
    if (velY > 0 && baixoEnti - margem < topoEspinho && baixoEnti > topoEspinho && direitaEnti > esquerdaEspinho + margem && esquerdaEnti < direitaEspinho - margem)
    {
        posEnti.y = topoEspinho - tamEnti.y;
        pEnti->setCoords(posEnti);
        if (danoso)
        {
            if (static_cast<Personagem*>(pEnti))
            {
				Personagem* pEntiAsPers = static_cast<Personagem*>(pEnti);
				pEntiAsPers->machucar(danosidade);
            }
        }
        pEnti->setVelVertical(0);
        tocando = true;
    }
    // --- COLISÃO POR BAIXO ---
    else if (velY < 0 && topoEnti < baixoEspinho && topoEnti > baixoEspinho - margem && direitaEnti > esquerdaEspinho + margem && esquerdaEnti < direitaEspinho - margem)
    {
        posEnti.y = baixoEspinho;
        pEnti->setCoords(posEnti);
        pEnti->setVelVertical(0);
    }
    // --- COLISÃO PELA ESQUERDA (separação de eixo X) ---
    else if (velX > 0 && direitaEnti > esquerdaEspinho && esquerdaEnti < esquerdaEspinho && baixoEnti > topoEspinho + margem && topoEnti < baixoEspinho - margem)
    {
        posEnti.x = esquerdaEspinho - tamEnti.x;
        pEnti->setCoords(posEnti);
        pEnti->setVelocidade(0);
    }
    // --- COLISÃO PELA DIREITA (separação de eixo X) ---
    else if (velX < 0 && esquerdaEnti < direitaEspinho && direitaEnti > direitaEspinho && baixoEnti > topoEspinho + margem && topoEnti < baixoEspinho - margem)
    {
        posEnti.x = direitaEspinho;
        pEnti->setCoords(posEnti);
        pEnti->setVelocidade(0);
    }

    pEnti->setNoChao(tocando);
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

void Espinho::carregar()
{
    int lugar = getId();
    indiceAtual = ++indiceEspinho;
    danosidade = dadosSalvos["id"][lugar][indiceAtual]["danosidade"];
    Obstaculo::carregar();
}