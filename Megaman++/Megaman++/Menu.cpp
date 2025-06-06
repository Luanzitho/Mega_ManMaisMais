#include "Menu.h"
#include <iostream>

Menu::Menu() : escolha(0), tela(0), enter(false), isPressed(false), start(false)
{
	pJog = nullptr;
	pGG = Gerenciador_Grafico::getInstancia();
	font = new sf::Font();
	font->loadFromFile("Fontes/Pixelify_Sans/static/PixelifySans-Regular.ttf");
	options = { "Jogar", "Ranking", "Sair", "Fase 1", "Fase 2"};
	coordsTexts = { {500.f, 400.f},{440.f, 500.f}, {540.f,600.f}, {500.f, 400.f},{440.f, 500.f} };
	texts.resize(options.size());
	for (int i = 0; i < options.size(); i++)
	{
		texts[i].setCharacterSize(100);
		texts[i].setString(options[i]);
		texts[i].setFillColor(sf::Color::White);
		texts[i].setFont(*font);
		texts[i].setPosition(coordsTexts[i]);
		texts[i].setOutlineColor(sf::Color::Black);
	}
	if (!font->loadFromFile("Fontes/Pixelify_Sans/static/PixelifySans-Regular.ttf")) {
		std::cout << "Erro ao carregar fonte!" << std::endl;
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
		pGG->eventoFecharJanela();
		pGG->limparJanela();
		pGG->desenharEnte(this);

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

		
		if(tela==0)
		{
			for (int i = 0; i < 3; i++)
			{
				if (i == escolha)texts[i].setOutlineThickness(3.f);
				else texts[i].setOutlineThickness(0);
				pGG->desenhaTexto(texts[i]);
			}
		}
		else if (tela == 1) 
		{
			for (int i = 3; i < 5; i++)
			{
				if (i == escolha)texts[i].setOutlineThickness(3.f);
				else texts[i].setOutlineThickness(0);
				pGG->desenhaTexto(texts[i]);
			}
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
		return "Sprites/Menu/Menu1.png";
	else if (tela == 1)
		return "Sprites/Menu/Menu1.png";
	else 
		return "Sprites/Menu/Menu1.png"; // retornar a imagem da tela atual
}