#include "Menu.h"
#include <iostream>

Menu::Menu() : escolha(0), tela(0), enter(false), isPressed(false), start(false), cooldown(0.f)
{
	pJog = nullptr;
	pGG = Gerenciador_Grafico::getInstancia();
	font = new sf::Font();
	font->loadFromFile("Fontes/Pixelify_Sans/static/PixelifySans-Regular.ttf");
	options = { "Jogar", "Ranking", "Sair",
				"1 Jogador", "2 Jogadores", "Voltar",
				"Fase 1", "Fase 2", "Voltar"
				};
	coordsTexts = { {500.f, 400.f},{440.f, 500.f}, {540.f,600.f}, 
					{440.f, 400.f},{440.f, 500.f}, {440.f, 600.f},
					{440.f, 400.f},{440.f, 500.f}, {440.f, 600.f}
					};
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
	//while (!start) //redundante??
	//{
		//pGG->eventoFecharJanela();
		//pGG->limparJanela();
		pGG->desenharEnte(this);
		//std::cout << "Menu" << std::endl;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !isPressed) //movimento da escolha de op��es
		{
			if ((tela == 0 || tela==1 || tela==2) && escolha < 2)escolha++;
			isPressed = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isPressed && escolha > 0)
		{
			isPressed = true;
			escolha--;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !isPressed)
		{
			isPressed = true;
			selecionar();
		}
		
		desenhaInteracao();
		//pGG->mostrarConteudoJanela();
		cooldown += dt; //cooldown para evitar que o enter seja pressionado muitas vezes
		//std::cout << "Cooldown: " << cooldown << std::endl;
		if (isPressed && cooldown > 0.5) // conseguir uma forma de saber quando soltou o bot�o
		{
			isPressed = false;
			cooldown = 0.f;
		}
	//}
}

void Menu::setGame(Jogo* jog)
{
	pJog = jog;
}

std::string Menu::getTextureFile()
{
		return "Sprites/Menu/Menu1.png";
}

void Menu::selecionar()
{
	if (tela == 0)
	{
		if (escolha == 0)
			tela = 1; // tela para escolher a fase
		else if (escolha == 1)
			tela = 3; // ranking
		else if (escolha == 2) {
			tela = 4; //sair
			pJog->encerrar(); //rever esse encerrar, para fechar o programa corretamente
		}
		escolha = 0;
	}
	else if (tela == 1)
	{
		if (escolha == 0) { //quantidade de jogadores
			pJog->setPlayers(false);
			tela=2;
		}
		else if (escolha == 2)
		{
			pJog->setPlayers(true);
			tela=2;
		}
		else if (escolha == 2)
		{
			tela = 0;//voltar
		}
		escolha = 0; //limpa a variavel para quando voltar para o menu
	}
	else if(tela==2)
	{
		/*if (escolha == 0) { //Continuar

		}*/
		if (escolha == 0 || escolha == 1) { //fase selecionada
			pJog->iniciar(escolha + 1);
			//start = true; //iniciar o jogo
			tela = 0;//limpa a variave para quando voltar para o menu
		}
		else if (escolha == 2)
		{
			tela = 1;//voltar
		}
		escolha = 0; //limpa a variavel para quando voltar para o menu
	}
}

void Menu::desenhaInteracao()
{
	if (tela == 0)
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
		for (int i = 3; i < 6; i++)
		{
			if (i == escolha + 3)texts[i].setOutlineThickness(3.f);
			else texts[i].setOutlineThickness(0);
			pGG->desenhaTexto(texts[i]);
		}
	}
	else if (tela == 2)
	{
		for (int i = 6; i < 9; i++)
		{
			if (i == escolha + 6)texts[i].setOutlineThickness(3.f);
			else texts[i].setOutlineThickness(0);
			pGG->desenhaTexto(texts[i]);
		}
	}
}