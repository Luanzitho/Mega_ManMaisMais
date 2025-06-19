#include "ProjetilMetall.h"
#include "../Personagens/Megaman.h"

ProjetilMetall::ProjetilMetall(): direcao(0)
{
	doMega = false;

	setId(5);
}

ProjetilMetall::ProjetilMetall(sf::Vector2f posicao, bool direita, int numTiro, int maldade): Projetil(250, maldade + 1)
{
	if (direita)
		direcao = 1;
	else
		direcao = -1;

	setId(5);

	doMega = false;
	noChao = false;
	tipoTiro = numTiro;

	setCoords(posicao);
	setTamanho(sf::Vector2f(15.f, 15.f));	
}

ProjetilMetall::~ProjetilMetall(){}

void ProjetilMetall::atingirMegaman(Megaman* p)
{
	if (!p || p->getNumVidas() <= 0) return;

	p->machucar(dano);
	destruir();
}

void ProjetilMetall::mover(float dt)
{
	if (getVivo()) {
		sf::Vector2f posicao;
		posicao = getCoords();

		if (tipoTiro == 1) //Tiro em linha reta
		{
			posicao.x += direcao * velocidade * dt;
		}
		else if (tipoTiro == 2) //Diagonal cima
		{
			posicao.x += direcao * velocidade * dt;
			posicao.y -= velocidade * dt;
		}
		else //Diagonal baixo
		{
			posicao.x += direcao * velocidade * dt;
			posicao.y += velocidade * dt;
		}
		
		setCoords(posicao);
	}
}

void ProjetilMetall::executar(float dt)
{
	mover(dt);
	sofrerAcaoDaGravidade(dt); 
	velVertical -= empuxo * dt; //Contrapõe a gravidade

	if (getCoords().x > 1200 || getCoords().x < 100)
		destruir();
}

std::string ProjetilMetall::getTextureFile()
{
	return "Sprites/Projeteis/ProjetilMetall.png";
}