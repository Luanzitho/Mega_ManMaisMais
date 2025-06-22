#include "Metall.h"
#include <cmath>
#include <time.h>
#include "../../Gerenciadores/Gerenciador_Colisoes.h"
//#include <iostream>

Metall::Metall(): timerEsconder(0), timerAtirar(0)
{
	srand(time(NULL));
	setId(3);

	tamanho = rand() % 6 + 50;

	qtdPontos += 50;

	setTamanho(sf::Vector2f(float(tamanho), float(tamanho)));

	dano = 1;

	setNumVidas(nivel_maldade);
}

int Metall::indiceMetall = -1;

Metall::~Metall()
{
}

void Metall::atirar(const int tipo)
{
	sf::Vector2f pos = getCoords();

	if (pMega->getCoords().x > pos.x)
		direita = true;
	else
		direita = false;

	ProjetilMetall* tiro = new ProjetilMetall(pos, direita, tipo, nivel_maldade);
	//std::cout << "Atirando Metall: " << std::endl;
	LE->incluirEntidade(tiro);
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

	if(!noChao)
		sofrerAcaoDaGravidade(dt);

	if (abs(pMega->getCoords().x - getCoords().x) < 200 && timerAtirar >= 3)
	{
		revelar(); //Ele precisa sair antes de atirar
		atirar(1); //Tiro 1 - Linha reta
		atirar(2); //Tiro 2 - Diagonal cima
		atirar(3); //Tiro 3 - Diagonal baixo
		timerAtirar = 0;
		timerEsconder = 0;
	}
	else if (timerEsconder >= 2.5)
	{
		esconder();
	}
}

void Metall::mover(float dt)
{
	sf::Vector2f posicao = getCoords();
	
	posicao.y += velVertical * dt;

	setCoords(posicao);
}

void Metall::danificar(Megaman* p)
{
	p->machucar(dano);
}

void Metall::machucar(const int dmg)
{
	if (!escondido)
	{
		num_vidas = num_vidas - dmg;
	}

	if (num_vidas <= 0)
	{	
		cederPontos();
		destruir();
	}
}

std::string Metall::getTextureFile()
{
	if (nivel_maldade == 1)
	{
		if (!escondido)
		{
			if(direita)
				return "Sprites/Inimigos/Metall-dir.png";
			return "Sprites/Inimigos/Metall-esq.png";
		}
		else
		{
			if(direita)
				return "Sprites/Inimigos/MetallEscondido-dir.png";
			return "Sprites/Inimigos/MetallEscondido-esq.png";
		}
	}
	
	else if (nivel_maldade == 2)
	{
		if (!escondido)
		{
			if (direita)
				return "Sprites/Inimigos/Metall2-dir.png";
			return "Sprites/Inimigos/Metall2-esq.png";
		}
		else
		{
			if (direita)
				return "Sprites/Inimigos/MetallEscondido2-dir.png";
			return "Sprites/Inimigos/MetallEscondido2-esq.png";
		}
	}

	else
	{
		if (!escondido)
		{
			if (direita)
				return "Sprites/Inimigos/MetallBAD-dir.png";
			return "Sprites/Inimigos/MetallBAD-esq.png";
		}
		else
		{
			if (direita)
				return "Sprites/Inimigos/MetallEscondido2-dir.png";
			return "Sprites/Inimigos/MetallEscondido2-esq.png";
		}
	}
}

void Metall::salvar()
{
	int lugar = getId();
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()]["timerEsconder"] = timerEsconder;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["timerAtirar"] = timerAtirar;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["escondido"] = escondido;
	Inimigo::salvar();
}

void Metall::carregar()
{
	int lugar = getId();
	indiceAtual = ++indiceMetall;
	timerEsconder=dadosSalvos["id"][lugar][indiceAtual]["timerEsconder"];
	timerAtirar=dadosSalvos["id"][lugar][indiceAtual]["timerAtirar"];
	escondido=dadosSalvos["id"][lugar][indiceAtual]["escondido"];

	Inimigo::salvar();
}