#include "CutMan.h"
#include "../../Gerenciadores/Gerenciador_Colisoes.h"

#include <iostream>

CutMan::CutMan(): cooldownNoChao(0), timerAtirar(0), timerPerseguir(0), timerPular(0), tiro(nullptr), LE(nullptr), GC(nullptr), podeAtirar(true)
{
	setTamanho(sf::Vector2f(70.f, 95.f));

	setNumVidas(22 + nivel_maldade * 2);

	velMax = 200;

	forca = 2 + nivel_maldade;
}

CutMan::~CutMan()
{
}

void CutMan::associaListaEntidades(ListaEntidades* pLista)
{
	LE = pLista;
}

void CutMan::associaGerenciadorColisoes(Gerenciador_Colisoes* GC)
{
	this->GC = GC;
}

void CutMan::atirar()
{
	std::cout << "penes\n";
	sf::Vector2f pos = getCoords();

	if (!GC || !LE) std::cout << "BOOM!\n";

	ProjetilCutMan* tiro = new ProjetilCutMan(pos, nivel_maldade, pMega->getCoords(), this);
	tiro->associaListaEntidades(LE);
	tiro->setGerenciadorGrafico(pGG);
	GC->incluirProjetil(tiro);
	LE->incluirEntidade(tiro);
	podeAtirar = false;

	setTamanho(sf::Vector2f(70.f, 70.f));
	setCoords(sf::Vector2f(getCoords().x, getCoords().y + 25));
}

void CutMan::possoAtirar()
{
	podeAtirar = true;

	setCoords(sf::Vector2f(getCoords().x, getCoords().y - 25));
	setTamanho(sf::Vector2f(70.f, 95.f));
}

void CutMan::mover(float dt)
{
	sf::Vector2f posicao = getCoords();
	sf::Vector2f alvo = pMega->getCoords();

	cooldownNoChao += dt;
	if (cooldownNoChao > 0.1 && noChao)
	{
		noChao = false;
		cooldownNoChao = 0;
	}

	timerPerseguir += dt;
	timerPular += dt;

	if (timerPerseguir >= 1) 
	{
		if (noChao && timerPular >= 3)
		{
			velVertical = -300;
			noChao = false;
			timerPular = 0;
		}
	
		if (alvo.x > posicao.x)
		{
			velocidade += velMax;
		}

		else
		{
			velocidade -= velMax;
		}
	
		timerPerseguir = 0;
	}

	else
	{
		velVertical += gravidade * dt;
	}

	if (velocidade > velMax) //Limita a velocidade
		velocidade = velMax;
	else if (velocidade < velMax * (-1))
		velocidade = velMax * (-1);

	posicao.x += velocidade * dt;
	posicao.y += velVertical * dt;

	setCoords(posicao);
}

void CutMan::executar(float dt)
{
	mover(dt);

	if (podeAtirar)
	{ 
		timerAtirar += dt;

		if (timerAtirar >= 2)
		{
			atirar();
			timerAtirar = 0;
		}
	}
}

void CutMan::danificar(Megaman* p)
{
	std::cout << "Colidiu!\n";
}

std::string CutMan::getTextureFile()
{
	if(podeAtirar)
		return "Sprites/Inimigos/CutMan1-L.png";
	return "Sprites/Inimigos/CutMan1.png";
}