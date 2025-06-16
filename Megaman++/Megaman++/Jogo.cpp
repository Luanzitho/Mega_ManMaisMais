#include "Jogo.h"
#include "Entidades/Personagens/Megaman.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Jogo::Jogo() : GG(*Gerenciador_Grafico::getInstancia()), inMenu(true), playing(false), faseA(0), f1(new Fase1), twoPlayers(false), f2(new Fase2)
{
	f1->setCoords(sf::Vector2f(0.f, 0.f));
	f1->setGerenciadorGrafico(&GG);

	f2->setCoords(sf::Vector2f(0.f, 0.f));
	f2->setGerenciadorGrafico(&GG);
}

Jogo::~Jogo()
{
	encerrar();
}

void Jogo::executar()
{
	Menu* menu = new Menu();

	menu->setCoords(sf::Vector2f(0.f, 0.f));
	menu->setTamanho(sf::Vector2f(1280.f, 720.f));
	menu->setGame(this);

	sf::Clock tempo;
	float dt;

	while (GG.janelaEstaAberta())
	{
		dt = tempo.restart().asSeconds();
		GG.eventoFecharJanela();
		GG.limparJanela();
		if (inMenu)
			menu->executar(dt);
		else if (playing)
		{
			if(faseA==1 && !f1->getAcabou())
			{
				f1->executar(dt);
			}
			else if(faseA==1 && f1->getAcabou())
			{
				faseA = 2;
			}
			else if(faseA==2)
			{
				f2->executar(dt);
			}
		}
		GG.mostrarConteudoJanela();
	}
}

void Jogo::iniciar(int fase)
{
	if(inMenu)
	{
		inMenu = false;
		playing = true;
		faseA = fase;
	}
}


void Jogo::encerrar()
{
	//LEs->LEs.limpar();
	//delete LEs;

}

void Jogo::setPlayers(bool players)
{
	twoPlayers = players;
	if (twoPlayers)
	{
		//p2->setAtivo(true);
	}
	else
	{
		//p2->setAtivo(false);
	}
}

Gerenciador_Grafico* Jogo::getGerenciador()
{
	return &GG;
}
