#include "Jogo.h"
#include "Entidades/Personagens/Megaman.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Jogo::Jogo() : GG(*Gerenciador_Grafico::getInstancia()), inMenu(true), playing(false), faseA(0), f1(new Fase1), f2(new Fase2), fechar(false)
{
	f1->setCoords(sf::Vector2f(0.f, 0.f));
	f1->setGerenciadorGrafico(&GG);

	f2->setCoords(sf::Vector2f(0.f, 0.f));
	f2->setGerenciadorGrafico(&GG);
}

Jogo::~Jogo()
{
	//encerrar();
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
		{
			menu->executar(dt);
		}	
		else if (playing)
		{
			timer += dt;

			if(faseA==1 && !f1->getAcabou())
			{
				f1->executar(dt);

				if (timer > 0.3)
				{
					system("cls");
					std::cout << "Player 1 HP: " << f1->getPlayerHP(false) << std::endl;
					if (twoPlayers)
						std::cout << "Player 2 HP: " << f1->getPlayerHP(true) << std::endl;
					std::cout << "Pontos: " << f1->getPlayerPoints() << std::endl;
					std::cout << "FPS: " << 1.0 / dt << std::endl;

					timer = 0;
				}
			}
			else if(faseA==1 && f1->getAcabou())
			{
				faseA = 2;
			}
			else if(faseA==2 && !f2->getAcabou())
			{
				f2->executar(dt);

				if (timer > 0.3)
				{
					system("cls");
					std::cout << "Player 1 HP: " << f2->getPlayerHP(false) << std::endl;
					if (twoPlayers)
						std::cout << "Player 2 HP: " << f2->getPlayerHP(true) << std::endl;
					std::cout << "Pontos: " << f2->getPlayerPoints() << std::endl;
					std::cout << "FPS: " << 1.0 / dt << std::endl;

					timer = 0;
				}
			}
			if((faseA==2 && f2->getAcabou()) || f1->getMorreu() || f2->getMorreu())
			{
				inMenu = true;
				playing = false;
				menu->setTerminou(true, f2->getPontuacao());
				GG.limpaTexto();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				playing = false;
				inMenu= true;
				menu->setPause(true);
			}
		}
		
		GG.mostrarConteudoJanela();
		if(fechar)
		{
			GG.fecharJanela();
			std::cout << "Fechando o jogo...\n";
			
			break;
		}
	}
	encerrar();
	std::cout << "Jogo encerrado.\n";
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
	if (f1) { delete f1; f1 = nullptr; }
	if (f2) { delete f2; f2 = nullptr; }
	//GG.fecharJanela();
}

void Jogo::setPlayers(bool players)
{
	if (players)
	{
		f1->setTwoPlayers();
		f2->setTwoPlayers();
		twoPlayers = true;
	}
	else 
	{
		f1->setOnePlayer();
		f2->setOnePlayer();
		twoPlayers = false;
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

void Jogo::setFechar(bool fe)
{
	fechar = fe;
}


