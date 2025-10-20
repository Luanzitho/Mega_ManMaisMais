#include "Jogo.h"
#include "Entidades/Personagens/Megaman.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gerenciadores/Gerenciador_Sonoro.h"

Jogo::Jogo() : GG(*Gerenciador_Grafico::getInstancia()), inMenu(true), playing(false), faseA(0), f1(new Fase1), f2(new Fase2), fechar(false)
{
	f1->setCoords(sf::Vector2f(0.f, 0.f));
	f1->setGerenciadorGrafico(&GG);

	f2->setCoords(sf::Vector2f(0.f, 0.f));
	f2->setGerenciadorGrafico(&GG);

	GS = AudioManager::getInstancia();
	GS->setVolumeMusica(75.f);

	GS->carregarEfeito("victory", "Sound/Effects/victory.wav");
	GS->carregarEfeito("gameover", "Sound/Effects/gameover.wav");
	GS->setVolumeEfeitos(100.f);
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
	bool delay = false;

	while (GG.janelaEstaAberta())
	{
		dt = tempo.restart().asSeconds();
		GG.eventoFecharJanela();
		GG.limparJanela();

		if (inMenu)
		{
			if (delay) //Para não tocar uma música por cima da outra
			{
				timer += dt;

				if (timer >= 5.f)
				{
					delay = false;
					//timer = 0;
					GS->pararMusica();
					GS->carregarMusica("Sound/Music/menu.wav");
					GS->tocarMusica();
				}
			}

			menu->executar(dt);
		}	
		else if (playing)
		{
			timer += dt;

			if(faseA==1 && !f1->getAcabou())
			{
				f1->executar(dt);

				if (timer > 0.2)
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
				GS->pararMusica();
				GS->carregarMusica("Sound/Music/boss.wav");
				GS->tocarMusica();
			}
			else if(faseA==2 && !f2->getAcabou())
			{
				f2->executar(dt);

				if (timer > 0.2)
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

				if (f1->getMorreu() || f2->getMorreu())
				{	
					GS->pararMusica();
					GS->tocarEfeito("gameover");
				}
				else
				{
					GS->pararMusica();
					GS->tocarEfeito("victory");
				}

				delay = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				playing = false;
				inMenu = true;
				menu->setPause(true);

				GS->pararMusica();
				GS->carregarMusica("Sound/Music/menu.wav");
				GS->tocarMusica();
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
		if (fase == 1)
		{
			GS->pararMusica();
			GS->carregarMusica("Sound/Music/lvl1.wav");
			GS->tocarMusica();
		}
		else if (fase == 2)
		{
			GS->pararMusica();
			GS->carregarMusica("Sound/Music/boss.wav");
			GS->tocarMusica();
		}
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
		{
			f1->carregar();
			GS->pararMusica();
			GS->carregarMusica("Sound/Music/lvl1.wav");
			GS->tocarMusica();
		}
		else
		{
			f2->carregar();
			GS->pararMusica();
			GS->carregarMusica("Sound/Music/boss.wav");
			GS->tocarMusica();
		}
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


