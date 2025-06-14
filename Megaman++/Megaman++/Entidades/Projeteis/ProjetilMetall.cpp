#include "ProjetilMetall.h"
#include "../Personagens/Megaman.h"

ProjetilMetall::ProjetilMetall(): direcao(0)
{
	doMega = false;

	setId(5);
	
	dano = 2;
}

ProjetilMetall::ProjetilMetall(sf::Vector2f posicao, bool direita, int numTiro, int maldade): Projetil(300)
{
	if (direita)
		direcao = 1;
	else
		direcao = -1;

	setId(5);

	doMega = false;
	dano = maldade + 1;
	tipoTiro = numTiro;
	empuxo = 300;

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

		posicao.y += gravidade * dt; //Força da gravidade atuando sobre o projetil
		posicao.y -= empuxo * dt; //Contrapõe a gravidade

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

	if (getCoords().x > 1200 || getCoords().x < 100)
		destruir();
}

std::string ProjetilMetall::getTextureFile()
{
	return "Sprites/Projeteis/ProjetilMetall.png";
}