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

void Plataforma::obstaculizar(Entidade* pEnti)
{
    if (!pEnti) return;

    sf::FloatRect rectEnti(pEnti->getCoords(), pEnti->getTamanho());
    sf::FloatRect rectPlat(getCoords(), getTamanho());

    sf::Vector2f posEnti = pEnti->getCoords();
    sf::Vector2f tamEnti = pEnti->getTamanho();

    float velY = pEnti->getVelVertical();
    float velX = pEnti->getVelocidade();

    float topoEnti = rectEnti.top;
    float baixoEnti = rectEnti.top + rectEnti.height;
    float topoPlat = rectPlat.top;
    float baixoPlat = rectPlat.top + rectPlat.height;
    float esquerdaEnti = rectEnti.left;
    float direitaEnti = rectEnti.left + rectEnti.width;
    float esquerdaPlat = rectPlat.left;
    float direitaPlat = rectPlat.left + rectPlat.width;

    const float margem = 15.f;

    bool tocando = false;

    // --- COLISÃO POR CIMA ---
    if (velY > 0 && baixoEnti - margem < topoPlat && baixoEnti > topoPlat && direitaEnti > esquerdaPlat + margem && esquerdaEnti < direitaPlat - margem)
    {
        posEnti.y = topoPlat - tamEnti.y;
        pEnti->setCoords(posEnti);
        pEnti->setVelVertical(0);
        tocando = true;
    }
    // --- COLISÃO POR BAIXO ---
    else if (velY < 0 && topoEnti < baixoPlat && topoEnti > baixoPlat - margem && direitaEnti > esquerdaPlat + margem && esquerdaEnti < direitaPlat - margem)
    {
        posEnti.y = baixoPlat;
        pEnti->setCoords(posEnti);
        pEnti->setVelVertical(0);
    }
    // --- COLISÃO PELA ESQUERDA (separação de eixo X) ---
    else if (velX > 0 && direitaEnti > esquerdaPlat && esquerdaEnti < esquerdaPlat && baixoEnti > topoPlat + margem && topoEnti < baixoPlat - margem)
    {
        posEnti.x = esquerdaPlat - tamEnti.x;
        pEnti->setCoords(posEnti);
        pEnti->setVelocidade(0);
    }
    // --- COLISÃO PELA DIREITA (separação de eixo X) ---
    else if (velX < 0 && esquerdaEnti < direitaPlat && direitaEnti > direitaPlat && baixoEnti > topoPlat + margem && topoEnti < baixoPlat - margem)
    {
        posEnti.x = direitaPlat;
        pEnti->setCoords(posEnti);
        pEnti->setVelocidade(0);
    }

    pEnti->setNoChao(tocando);
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
