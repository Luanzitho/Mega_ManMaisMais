#include "Metall.h"
#include <cmath>
#include <time.h>
#include "../../Gerenciadores/Gerenciador_Colisoes.h"
#include <iostream>

Metall::Metall(): timerEsconder(0), timerAtirar(0)
{
	srand(time(NULL));

	tamanho = rand() % 6 + 50;

	setTamanho(sf::Vector2f(float(tamanho), float(tamanho)));

	dano = 1;

	if (nivel_maldade < 3)
	{
		setNumVidas(2);
	}

	else 
	{
		setNumVidas(4);
	}
}

Metall::~Metall()
{
}

/*void Metall::associaListaEntidades(ListaEntidades* pLista)
{
	LE = pLista;
}*/

/* {
	this->GC = GC;
}*/

void Metall::atirar(int tipo)
{
	sf::Vector2f pos = getCoords();

	if (pMega->getCoords().x > pos.x)
		direita = true;
	else
		direita = false;

	ProjetilMetall* tiro = new ProjetilMetall(pos, direita, tipo, nivel_maldade);
	std::cout << "Atirando Metall: " << std::endl;
	LE->incluirEntidade(tiro);
	std::cout << "Atirando Metall: " << std::endl;
	tiro->associaListaEntidades(LE);
	tiro->setGerenciadorGrafico(pGG);
	GC->incluirProjetil(tiro);
}

void Metall::esconder()
{
	escondido = true;
}

void Metall::revelar()
{
	escondido = false;
}

void Metall::executar(float dt)
{
	timerAtirar += dt;
	timerEsconder += dt;

	mover(dt);

	if (abs(pMega->getCoords().x - getCoords().x) < 200 && timerAtirar >= 3)
	{
		revelar(); //Ele precisa sair antes de atirar
		atirar(1); //Tiro 1 - Linha reta
		atirar(2); //Tiro 2 - Diagonal cima
		atirar(3); //Tiro 3 - Diagonal baixo
		timerAtirar = 0;
		timerEsconder = 0;
	}
	else if (timerEsconder >= 1.5)
	{
		esconder();
	}
}

void Metall::mover(float dt)
{
	sf::Vector2f posicao = getCoords();

	if (!noChao) //Só se movimenta se estiver no ar
	{
		velVertical += gravidade * dt;
	}
	else
	{
		velVertical = 0;
	}

	posicao.y += velVertical * dt;

	setCoords(posicao);
}

void Metall::danificar(Megaman* p)
{
	p->machucar(dano);
}

void Metall::machucar(int dmg)
{
	if (!escondido)
	{
		num_vidas = num_vidas - dmg;
	}

	if (num_vidas <= 0)
		destruir();
}

std::string Metall::getTextureFile()
{
	if (nivel_maldade == 1)
	{
		if (!escondido)
			return "Sprites/Inimigos/Metall.png";
		return "Sprites/Inimigos/MetallEscondido.png";
	}
	
	else if (nivel_maldade == 2)
	{
		if (!escondido)
			return "Sprites/Inimigos/Metall2.png";
		return "Sprites/Inimigos/MetallEscondido2.png";
	}

	else
	{
		if (!escondido)
			return "Sprites/Inimigos/MetallBAD.png";
		return "Sprites/Inimigos/MetallEscondido2.png";
	}
}