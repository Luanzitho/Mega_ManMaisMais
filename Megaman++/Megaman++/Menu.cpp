#include "Menu.h"
#include <iostream>

Menu::Menu() : escolha(0), tela(0), enter(false), isPressed(false), start(false), cooldown(0.f), fase(0), pause(false), pontuacao(0), terminou(false), rankingNomes(), rankingPontos()
{
	setId(12);
	pJog = nullptr;
	pGG = Gerenciador_Grafico::getInstancia();
	font = new sf::Font();
	font->loadFromFile("Fontes/Pixelify_Sans/static/PixelifySans-Regular.ttf"); // fonte do google: 
	options = { "Jogar", "Ranking", "Sair", //marco 
				"1 Jogador", "2 Jogadores", "Voltar",
				"Continuar","Fase 1", "Fase 2", "Voltar",
				"Continuar", "Salvar","Voltar ao menu",
				"Digite seu nome", "", ""
				};
	coordsTexts = { {500.f, 400.f},{440.f, 500.f}, {540.f,600.f},
					{440.f, 400.f},{440.f, 500.f}, {440.f, 600.f},
					{240.f, 400.f},{440.f, 500.f}, {440.f, 600.f},{840.f, 400.f},
					{ 440.f, 400.f },{440.f, 500.f}, {440.f, 600.f}, 
					{ 40.f, 400.f },{40.f, 500.f}, {40.f, 600.f}
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
	for (int i = 0; i < dadosSalvos["id"][getId()][0]["ranking"]["nomes"].size(); i++)
	{
		
		rankingNomes.push_back(dadosSalvos["id"][getId()][0]["ranking"]["nomes"][i]);
		rankingPontos.push_back(dadosSalvos["id"][getId()][0]["ranking"]["pontos"][i]);
		
	}
	ranking.resize(dadosSalvos["id"][getId()][0]["ranking"]["nomes"].size());
	for (int i = 0; i < rankingPontos.size(); i++)
	{
		ranking[i].setCharacterSize(100);
		ranking[i].setString(std::to_string(i + 1) + ". " + rankingNomes[i] + " - " + std::to_string(rankingPontos[i]));
		ranking[i].setFillColor(sf::Color::White);
		ranking[i].setFont(*font);
		ranking[i].setPosition(sf::Vector2f(40.f, coordsTexts[i>=2?i%2:i].y));
		//texts[i].setOutlineColor(sf::Color::Black);
		//pGG->desenhar(texto);
	}
}

Menu::~Menu()
{
	delete font;
	delete pGG;
	delete pJog;
	options.clear();
	texts.clear();
	coordsTexts.clear();
}

void Menu::executar(float dt)
{
	pGG->desenharEnte(this);
	//entradaUsuario = pGG->digitar(entradaUsuario);
	cooldown += dt; //cooldown para evitar que o enter seja pressionado muitas vezes
	if (pause)tela = 3;
	if (terminou)tela = 4;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !isPressed) //movimento da escolha de op��es
	{
		if(cooldown>0.25f)
		{
			if ((tela == 0 || tela == 1 || tela == 3) && escolha < 2) escolha++;
			else if (tela == 2 && escolha < 3)escolha++;
			else if (tela == 5 && escolha < 5)escolha++;
			isPressed = true;
			cooldown = 0;
		}
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isPressed && escolha > 0)
	{
		if(cooldown>0.25f)
		{
			isPressed = true;
			escolha--;
			cooldown = 0;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !isPressed)
	{
		if(cooldown>0.25f)
		{
			isPressed = true;
			selecionar();
			cooldown = 0;
		}
		
	}
	else
	{
		isPressed = false;
	}
		
	desenhaInteracao();
	
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
			tela = 5; // ranking
		else if (escolha == 2) {
			//tela = 4; //sair
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
		else if (escolha == 1)
		{
			pJog->setPlayers(true);
			tela=2;
		}
		else if (escolha == 2)
		{
			tela = 0;//voltar
		}
	}
	else if(tela==2)
	{
		if (escolha == 0) { //Continuar
			carregar();
			pJog->iniciar(fase, true);
			tela = 0;
		}
		if (escolha == 1 || escolha == 2) { //fase selecionada
			pJog->iniciar(escolha);
			fase = escolha;
			//start = true; //iniciar o jogo
			tela = 0;//limpa a variave para quando voltar para o menu
		}
		else if (escolha == 3)
		{
			tela = 1;//voltar
		}
	}
	else if(tela == 3)// menu de pause
	{
		if (escolha == 0) { //volta para o jogo atual
			pJog->iniciar(fase);
			tela = 0;
		}
		else if (escolha == 1)// salvar
		{
			salvar();
			pJog->salvar();
		}
		else if (escolha == 2)//voltar para o menu principal
		{
			pause = false;
			pJog->reiniciarFases();
			tela = 0;//voltar
		}
	}
	else if(tela == 4)// tela de fim
	{ 
		rankingNomes.push_back(pGG->getTexto());
		rankingPontos.push_back(pontuacao);
		for(int i=0; i<rankingPontos.size(); i++)
		{
			if(rankingPontos[rankingPontos.size()-1]>rankingPontos[i])
			{
				std::string swpN = rankingNomes[i];
				int swpP = rankingPontos[i];
				rankingPontos[i] = rankingPontos[rankingPontos.size() - 1];
				rankingNomes[i] = rankingNomes[rankingNomes.size() - 1];
				rankingPontos[rankingPontos.size() - 1] = swpP;
				rankingNomes[rankingNomes.size() - 1] = swpN;
			}
			if(i<=10)
			{
				dadosSalvos["id"][getId()][dadosSalvos["id"][getId()].size() - 1]["ranking"]["nomes"][i] = rankingNomes[i];
				dadosSalvos["id"][getId()][dadosSalvos["id"][getId()].size() - 1]["ranking"]["pontos"][i] = rankingPontos[i];
			}
			
		}
		ranking.resize(dadosSalvos["id"][getId()][0]["ranking"]["nomes"].size());
		for (int i = 0; i < rankingPontos.size(); i++)
		{
			ranking[i].setCharacterSize(100);
			ranking[i].setString(std::to_string(i + 1) + ". " + rankingNomes[i] + " - " + std::to_string(rankingPontos[i]));
			ranking[i].setFillColor(sf::Color::White);
			ranking[i].setFont(*font);
			ranking[i].setPosition(sf::Vector2f(40.f, coordsTexts[i >= 2 ? i % 2 : i].y));
			//texts[i].setOutlineColor(sf::Color::Black);
			//pGG->desenhar(texto);
		}
		salvar();
		terminou = false;
		pJog->reiniciarFases();
		tela = 0;
		
	}
	else if (tela == 5 && escolha == 5)// tela de ranking
	{
		tela = 0;
	}
	escolha = 0; //limpa a variavel para quando voltar para o menu
}

void Menu::desenhaInteracao()
{
	if (tela == 0)// menu principal
	{
		for (int i = 0; i < 3; i++)
		{
			if (i == escolha)texts[i].setOutlineThickness(3.f);
			else texts[i].setOutlineThickness(0);
			pGG->desenhar(texts[i]);
		}
	}
	else if (tela == 1)// quantidade de jogadores
	{
		for (int i = 3; i < 6; i++)
		{
			if (i == escolha + 3)texts[i].setOutlineThickness(3.f);
			else texts[i].setOutlineThickness(0);
			pGG->desenhar(texts[i]);
		}
	}
	else if (tela == 2)//escolha da fase
	{
		for (int i = 6; i < 10; i++)
		{
			if (i == escolha + 6)texts[i].setOutlineThickness(3.f);
			else texts[i].setOutlineThickness(0);
			pGG->desenhar(texts[i]);
		}
	}
	else if(tela == 3)// menu de pause
	{
		for (int i = 10; i < 13; i++)
		{
			if (i == escolha + 10)texts[i].setOutlineThickness(3.f);
			else texts[i].setOutlineThickness(0);
			pGG->desenhar(texts[i]);
		}
	}
	else if(tela==4)// tela de fim
	{
		texts[texts.size()-2].setString(pGG->getTexto());
		texts[texts.size()-1].setString("Sua pontução foi de: " + std::to_string(pontuacao));
		pGG->desenhar(texts[texts.size() - 3]);
		pGG->desenhar(texts[texts.size() - 2]);
		pGG->desenhar(texts[texts.size() - 1]);
	}
	else if(tela==5)// ranking
	{
		for (int i = 0; i < 2; i++)
		{
			if(i+escolha*2<=ranking.size()-1 && "" && i+escolha*2<=10)
			{
				pGG->desenhar(ranking[i + escolha * 2]);
			}
			else if(i+escolha*2>10)
			{
				texts[5].setOutlineThickness(3.f);
				pGG->desenhar(texts[5]);
			}
				
		}
	}
}

void Menu::setPause(bool pausado)
{
	pause = pausado;
}

void Menu::salvar()
{
	int lugar = getId();
	dadosSalvos= json::object({});
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()]["fase"] = fase;
	for (int i = 0; i < rankingPontos.size(); i++)
	{
		dadosSalvos["id"][getId()][dadosSalvos["id"][getId()].size() - 1]["ranking"]["nomes"][i] = rankingNomes[i];
		dadosSalvos["id"][getId()][dadosSalvos["id"][getId()].size() - 1]["ranking"]["pontos"][i] = rankingPontos[i];
	}
	Ente::salvar();
}

void Menu::carregar()
{
	int lugar = getId();
	indiceAtual = dadosSalvos["id"][lugar].size()-1;
	
	fase = dadosSalvos["id"][lugar][indiceAtual]["fase"];

	for (int i = 0; i < rankingPontos.size(); i++)
	{
		rankingNomes[i] = dadosSalvos["id"][getId()][indiceAtual]["ranking"]["nomes"][i];
		rankingPontos[i] = dadosSalvos["id"][getId()][indiceAtual]["ranking"]["pontos"][i];
	}
	Ente::carregar();
}

void Menu::setTerminou(bool termi, int pontos)
{
	terminou = termi;
	pontuacao = pontos;
}
