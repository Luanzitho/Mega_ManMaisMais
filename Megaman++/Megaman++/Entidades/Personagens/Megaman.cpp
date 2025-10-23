#include "Megaman.h"
#include "../../Gerenciadores/Gerenciador_Colisoes.h"

#include <iostream>

Megaman::Megaman() : Personagem(28), teclaApertada(false), cooldownTiro(0), player1(true), invencivel(false), framesInvencibilidade(0), cooldownNoChao(0)
{
	LE = nullptr;
	GC = nullptr;

	direita = true;

	setId(1);

	velMax = 200;

	setTamanho(sf::Vector2f(70.f, 70.f));

	estadoAnimacao.numFrames = 13;
	estadoAnimacao.frameAtual = 0;
	estadoAnimacao.alturaSprite = 64;
	estadoAnimacao.larguraSprite = 64;

	tempoFrame = 0.2f; //Tempo entre frames
	tempoAcumulado = 0.f;
	animado = true;

	pGS->carregarEfeito("tiroMegaman", "Sound/Effects/megabuster.wav");
	pGS->carregarEfeito("megamanDMG", "Sound/Effects/megamandmg.wav");
	pGS->carregarEfeito("Defeat", "Sound/Effects/defeat.wav");
	pGS->setVolumeEfeitos(100.f);
}
int Megaman::pontos(0);

Megaman::Megaman(bool player) : Personagem(28), teclaApertada(false), cooldownTiro(0), player1(player), invencivel(false), framesInvencibilidade(0), cooldownNoChao(0)
{
	LE = nullptr;
	GC = nullptr;

	setId(2);

	direita = true;

	velMax = 200;

	setTamanho(sf::Vector2f(70.f, 70.f));

	estadoAnimacao.numFrames = 13;
	estadoAnimacao.frameAtual = 0;
	estadoAnimacao.alturaSprite = 64;
	estadoAnimacao.larguraSprite = 64;

	tempoFrame = 0.2f; //Tempo entre frames
	tempoAcumulado = 0.f;
	animado = true;
}

Megaman::~Megaman()
{
	LE = nullptr;
	GC = nullptr;
}

void Megaman::associaListaEntidades(ListaEntidades* pLista)
{
	LE = pLista;
}

void Megaman::associaGerenciadorColisoes(Gerenciador_Colisoes* GC)
{
	this->GC = GC;
}

void Megaman::operator+=(const int pts)
{
	pontos = pontos + pts;
}

void Megaman::curar(const int hp)
{
	num_vidas = num_vidas + hp;
	if (num_vidas > 28)
		num_vidas = 28;
}

void Megaman::machucar(const int dmg)
{
	if (!invencivel)
	{
		num_vidas = num_vidas - dmg;
		estadoAnimacao.Machucado = true;
		pGS->tocarEfeito("megamanDMG");
	}

	if (num_vidas <= 0)
	{
		destruir();
		pGS->tocarEfeito("Defeat");
	}

	invencivel = true; //Fica invencível por alguns segundos quando toma dano
}

void Megaman::mover(float dt)
{
	sf::Vector2f posicao = getCoords();

	cooldownNoChao += dt;

	if (noChao)
	{
		estadoAnimacao.Pulando = false;
		if(velocidade != 0)
		{
			estadoAnimacao.Parado = false;
			estadoAnimacao.Andando = true;
		}
		else
		{
			estadoAnimacao.Parado = true;
			estadoAnimacao.Andando = false;
		}
	}

	if (cooldownNoChao > 0.2f)
	{
		cooldownNoChao = 0;
		noChao = false;
	}

	if (player1) //Player 1 usa as SETAS
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
		{ 
			velocidade = -velMax; 
			direita = false; 
			estadoAnimacao.Andando = true; 
			estadoAnimacao.Parado = false; 
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
		{ 
			velocidade = velMax; 
			direita = true; 
			estadoAnimacao.Andando = true; 
			estadoAnimacao.Parado = false; 
		}
		else velocidade = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && noChao) 
		{ 
			velVertical = -350.f; 
			noChao = false; 
			estadoAnimacao.Pulando = true; 
			estadoAnimacao.Parado = false; 
		}
	}
	else //Player 2 usa WASD
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
		{ 
			velocidade = -velMax; 
			direita = false; 
			estadoAnimacao.Andando = true; 
			estadoAnimacao.Parado = false; 
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
		{ 
			velocidade = velMax; 
			direita = true; 
			estadoAnimacao.Andando = true; 
			estadoAnimacao.Parado = false; 
		}
		else velocidade = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && noChao) 
		{ 
			velVertical = -350.f; 
			noChao = false; 
			estadoAnimacao.Pulando = true; 
			estadoAnimacao.Parado = false; 
		}
	}

	if (posicao.x + velocidade * dt > 0) posicao.x += velocidade * dt;
	posicao.y += velVertical * dt;

	setCoords(posicao);
}

void Megaman::atirar(float dt)
{
	cooldownTiro += dt;

	if (player1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (!teclaApertada && cooldownTiro >= 0.25)
			{
				estadoAnimacao.Atacando = true;

				sf::Vector2f pos = getCoords();
				pos.x += (direita ? 40.f : 15.f);
				pos.y += getTamanho().y / 4;

				ProjetilMegaman* tiro = new ProjetilMegaman(pos, direita);
				LE->incluirEntidade(tiro);
				tiro->associaListaEntidades(LE);
				tiro->setGerenciadorGrafico(pGG);
				GC->incluirProjetil(tiro);

				//pGS->carregarEfeito("tiroMegaman", "Sound/Effects/megabuster.wav");
				pGS->tocarEfeito("tiroMegaman");

				cooldownTiro = 0;
				teclaApertada = true;
			}
		}
		else
		{
			teclaApertada = false;
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			if (!teclaApertada && cooldownTiro >= 0.25)
			{
				estadoAnimacao.Atacando = true;

				sf::Vector2f pos = getCoords();
				pos.x += (direita ? 40.f : 15.f);
				pos.y += getTamanho().y / 4;

				ProjetilMegaman* tiro = new ProjetilMegaman(pos, direita);
				LE->incluirEntidade(tiro);
				tiro->associaListaEntidades(LE);
				tiro->setGerenciadorGrafico(pGG);
				GC->incluirProjetil(tiro);

				//pGS->carregarEfeito("tiroMegaman", "Sound/Effects/megabuster.wav");
				pGS->tocarEfeito("tiroMegaman");

				cooldownTiro = 0;
				teclaApertada = true;
			}
		}
		else
		{
			teclaApertada = false;
		}
	}

	if(cooldownTiro >= 0.15)
		estadoAnimacao.Atacando = false;
}

const bool Megaman::getInvencivel()
{
	return invencivel;
}

void Megaman::executar(float dt)
{
	mover(dt);
	atirar(dt);

	tempoAcumulado += dt;
	
	if (!noChao) sofrerAcaoDaGravidade(dt);

	if (invencivel) 
	{
		framesInvencibilidade += dt;
		if (framesInvencibilidade > 0.2f) estadoAnimacao.Machucado = false;
		if (framesInvencibilidade >= 2.f) { framesInvencibilidade = 0.f; invencivel = false; }
	}

	timerFrame += dt;
}

int Megaman::getFrame()
{
	if (estadoAnimacao.Machucado) {
		int offset = (int)(timerFrame / tempoFrame) % 2; // 0 ou 1
		return 11 + offset; // 11 ou 12
	}

	if (estadoAnimacao.Pulando)
	{
		if (estadoAnimacao.Atacando)
			return 10;
		return 9;
	}

	if (estadoAnimacao.Andando)
	{
		if (estadoAnimacao.Atacando)
			return 6 + (int((timerFrame / tempoFrame)) % 3); // frames 6-8
		else
			return 2 + (int((timerFrame / tempoFrame)) % 3); // frames 2-4
	}

	if (estadoAnimacao.Atacando)
	{
		return 5;
	}

	return (int((timerFrame / tempoFrame)) % 2); // frames 0-1
}

sf::Vector2f Megaman::getEscalaCorreta()
{
	return sf::Vector2f(100, 100);
}

std::string Megaman::getTextureFile()
{
	/*
	if (player1)
	{
		if (!invencivel)
		{
			if (direita)
				return "Sprites/Megaman/Parado/Parado1-dir.png";

			return "Sprites/Megaman/Parado/Parado1-esq.png";
		}
		else
		{
			if (direita)
				return "Sprites/Megaman/Parado/Parado1-Inv-dir.png";
			return "Sprites/Megaman/Parado/Parado1-Inv-esq.png";
		}
	}
	else
	{
		if (!invencivel)
		{
			if (direita)
				return "Sprites/Megaman/Parado/ParadoNH-dir.png";

			return "Sprites/Megaman/Parado/ParadoNH-esq.png";
		}
		else
		{
			if (direita)
				return "Sprites/Megaman/Parado/ParadoNH-Inv-dir.png";
			return "Sprites/Megaman/Parado/ParadoNH-Inv-esq.png";
		}
	}*/
	if(player1)
		return "Sprites/Megaman/megaman.png";
	return "Sprites/Megaman/megamanP2.png";
}

void Megaman::salvar()
{
	int lugar = getId();
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()]["player1"] = player1;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["invencivel"] = invencivel;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["pontos"] = pontos;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["teclaApertada"] = teclaApertada;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["cooldownTiro"] = cooldownTiro;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["framesInvencibilidade"] = framesInvencibilidade;

	Personagem::salvar();
}

void Megaman::carregar()
{
	int lugar = getId();
	player1 = dadosSalvos["id"][lugar][0]["player1"];
	invencivel = dadosSalvos["id"][lugar][0]["invencivel"];
	pontos = dadosSalvos["id"][lugar][0]["pontos"];
	teclaApertada = dadosSalvos["id"][lugar][0]["teclaApertada"];
	cooldownTiro = dadosSalvos["id"][lugar][0]["cooldownTiro"];
	framesInvencibilidade = dadosSalvos["id"][lugar][0]["framesInvencibilidade"];

	Personagem::carregar();
}

const int Megaman::getPontos()
{
	return pontos;
}
