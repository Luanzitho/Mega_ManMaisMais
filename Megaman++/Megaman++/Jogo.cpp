#include "Jogo.h"
#include "Entidades/Personagens/Megaman.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Jogo::Jogo() : GG(*Gerenciador_Grafico::getInstancia()), inMenu(true), playing(false), faseA(0), f1(new Fase1), f2(new Fase2)
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
	GG.textoDigitado = &menu->entradaUsuario;

	sf::Clock tempo;
	float dt;

	while (GG.janelaEstaAberta())
	{
		dt = tempo.restart().asSeconds();
		GG.eventoFecharJanela();
		GG.limparJanela();
		if (inMenu)
		{
			menu->executar(dt);
		}	
		else if (playing)
		{
			if(faseA==1 && !f1->getAcabou())
			{
				f1->executar(dt);
				//std::cout << "executando fase 1" << std::endl;
			}
			else if(faseA==1 && f1->getAcabou())
			{
				faseA = 2;
			}
			else if(faseA==2 && !f2->getAcabou())
			{
				f2->executar(dt);
			}
			else if(faseA==2 && f2->getAcabou())
			{
				inMenu = true;
				playing = false;
				menu->setTerminou(true);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				playing = false;
				inMenu= true;
				menu->setPause(true);
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

void Jogo::iniciar(int fase, bool carregar)
{
	if (inMenu && carregar)
	{
		inMenu = false;
		playing = true;
		faseA = fase;
		if (fase == 1)
			f1->carregar();
		else
			f2->carregar();
	}
}


void Jogo::encerrar()
{
	delete f1;
	delete f2;
}

void Jogo::setPlayers(bool players)
{
	if (players)
	{
		f1->setTwoPlayers();
		f2->setTwoPlayers();
	}
	else 
	{
		f1->setOnePlayer();
		f2->setOnePlayer();
	}
}

Gerenciador_Grafico* Jogo::getGerenciador()
{
	return &GG;
}

void Jogo::reiniciarFases()
{
	//delete f1;
	//delete f2;
	free(f1);
	free(f2);
	f1 = new Fase1;
	f2 = new Fase2;
	f1->setCoords(sf::Vector2f(0.f, 0.f));
	f1->setGerenciadorGrafico(&GG);

	f2->setCoords(sf::Vector2f(0.f, 0.f));
	f2->setGerenciadorGrafico(&GG);
}

void Jogo::salvar()
{
	if (faseA == 1)
		f1->salvar();
	else if (faseA == 2)
		f2->salvar();
	// salvar as variaveis que precisar
}


