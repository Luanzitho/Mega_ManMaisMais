#include "Menu.h"
#include <iostream>

Menu::Menu() : escolha(0), tela(0), enter(false), isPressed(false), start(false)
{
	pJog = nullptr;
	font = new sf::Font();
	font->loadFromFile("Fontes/Pixels.ttf");
	options = { "Jogar", "Rankinng", "Sair"};
	coordsTexts = { {0.f, 0.f},{640.f, 460.f}, {640.f,560.f}};
	texts.resize((int)options.size());
	for (int i = 0; i < options.size(); i++)
	{
		texts[i].setCharacterSize(240.f);
		texts[i].setFillColor(sf::Color::White);
		texts[i].setFont(*font);
		texts[i].setPosition(coordsTexts[i]);
		texts[i].setOutlineColor(sf::Color::Black);
	}
}

Menu::~Menu()
{
	delete font;
	delete pGG;
}

void Menu::executar(float dt)
{
	//sf::Vector2f pos = sf::Vector2f(230.f, 444.f), tam = sf::Vector2f(850.f, 60.f);// obs: acertar melhor o desenho no menu
	
	while (!start)
	{
		pGG->fecharJanela();
		pGG->limparJanela();		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !isPressed) //movimento da escolha de op��es
		{
			if (tela == 0 && escolha < 4)escolha++;
			else if (tela == 1 && escolha < 2)escolha++;
			isPressed = true;
			//pos.y += tam.y;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isPressed && escolha > 0)
		{
			isPressed = true;
			escolha--;
			//pos.y -= tam.y;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (tela == 0)
			{
				if (escolha == 0)
					tela = 1; // tela para escolher a fase
				else if (escolha == 1)
					tela = 2; // ranking
				else if (escolha == 2) {
					tela = 3; //sair
					pJog->encerrar();
				}
				escolha = 0;
			}
			else if (tela == 1)
			{
				if (escolha == 0) {//fase 1
					pJog->iniciar(escolha+1);
				}
				else if (escolha == 1) {//fase 2
				}
				else if(escolha==3)
				{ //voltar
				
				}
			}
		}

		pGG->desenharEnte(this);

		for (int i = 0; i < texts.size(); i++)
		{
			if (i == escolha)texts[i].setOutlineThickness(3.f);
			else texts[i].setOutlineThickness(0);
			pGG->desenhaTexto(texts[i]);
			//std::cout << texts[i].getPosition().x << "," << texts[i].getPosition().y << std::endl;
			//std::cout << texts[i].getFont()->getInfo().family << std::endl;
		}

		//system("Pause");
		
		//pGG->desenhaRetangulo(pos, tam);
		pGG->mostrarConteudoJanela();
		if (isPressed) // conseguir uma forma de saber quando soltou o bot�o
		{
			isPressed = false;
		}
	}
}

void Menu::setGame(Jogo* jog)
{
	pJog = jog;
}

std::string Menu::getTextureFile()
{
	if (tela == 0)
		return "Sprites/Menu/MenuMegaman2.png";
	else if (tela == 1)
		return "Sprites/Menu/MenuMegaman3.png";
}