#include "CutMan.h"
#include "../../Gerenciadores/Gerenciador_Colisoes.h"

//#include <iostream>

CutMan::CutMan(): cooldownNoChao(0), timerAtirar(0), timerPerseguir(0), timerPular(0), podeAtirar(true)
{
	setTamanho(sf::Vector2f(70.f, 95.f));
	setId(8);
	setNumVidas(22 + nivel_maldade * 2);

	velMax = VELOCIDADE_MAX;
	
	qtdPontos += 900;

	forca = 2 + nivel_maldade;

	pGS->carregarEfeito("CutManAtirar", "Sound/Effects/RollingCutter.wav");

	estadoAnimacao.numFrames = 14;
	estadoAnimacao.frameAtual = 0;
	estadoAnimacao.alturaSprite = 32;
	estadoAnimacao.larguraSprite = 32;

	tempoFrame = 0.2f; //Tempo entre frames
	tempoAcumulado = 0.f;
	animado = true;
}

int CutMan::indiceCutMan = -1;

CutMan::~CutMan()
{
}

void CutMan::atirar()
{
	sf::Vector2f pos = getCoords();

	//if (!GC || !LE) std::cout << "BOOM!\n";

	ProjetilCutMan* tiro = new ProjetilCutMan(pos, nivel_maldade, pMega->getCoords(), this);
	tiro->associaListaEntidades(LE);
	tiro->setGerenciadorGrafico(pGG);
	GC->incluirProjetil(tiro);
	LE->incluirEntidade(tiro);
	podeAtirar = false;

	pGS->tocarEfeito("CutManAtirar");

	setTamanho(sf::Vector2f(70.f, 70.f));
	setCoords(sf::Vector2f(getCoords().x, getCoords().y + 25));

	estadoAnimacao.Atacando = false;
}

void CutMan::possoAtirar()
{
	podeAtirar = true;

	setCoords(sf::Vector2f(getCoords().x, getCoords().y - 25));
	setTamanho(sf::Vector2f(70.f, 95.f));
}

void CutMan::mover(float dt)
{
	sf::Vector2f posicao = getCoords();
	sf::Vector2f alvo = pMega->getCoords();

	if (noChao) estadoAnimacao.Pulando = false;

	if (velocidade == 0 && noChao) estadoAnimacao.Parado = true;
	else estadoAnimacao.Parado = false;

	cooldownNoChao += dt;
	if (cooldownNoChao > 0.1 && noChao)
	{
		noChao = false;
		cooldownNoChao = 0;
	}
	if (!noChao && cooldownNoChao > 0.1) //Caso ele esteja caindo, mesmo sem usar o pulo, ele entra na animação de pulo
		estadoAnimacao.Pulando = true;

	timerPerseguir += dt;
	timerPular += dt;

	if (timerPerseguir >= TEMPO_PERSEGUIR) 
	{
		if (noChao && timerPular >= TEMPO_PULAR)
		{
			velVertical = ALTURA_PULO;
			estadoAnimacao.Pulando = true;
			noChao = false;
			timerPular = 0;
		}

		if (alvo.x > posicao.x)
		{
			direita = true;
			velocidade += velMax;
		}
		else
		{
			direita = false;
			velocidade -= velMax;
		}

		estadoAnimacao.Andando = true;
		timerPerseguir = 0;
	}

	if (velocidade > velMax) //Limita a velocidade
		velocidade = velMax;
	else if (velocidade < velMax * (-1))
		velocidade = velMax * (-1);

	posicao.x += velocidade * dt;
	posicao.y += velVertical * dt;

	setCoords(posicao);
}

int CutMan::getFrame()
{
	if (estadoAnimacao.Atacando == true)
	{
		return (6 + (int((timerFrame / tempoFrame)) % 2)); //Frames 6-7 (Arremessando a lâmina)
	}

	if (estadoAnimacao.Parado == true)
	{
		if(podeAtirar)
			return (int((timerFrame / tempoFrame)) % 2); //Frames 0-1 (Parado com a lâmina)
		return (8 + (int((timerFrame / tempoFrame)) % 2)); //Frames 8-9 (Parado sem a lâmina)
	}

	if (estadoAnimacao.Pulando == true)
	{
		if (podeAtirar) 
			return 5; //Pulo (lâmina)
		return 13; //Pulo (Sem lâmina)
	}

	if (estadoAnimacao.Andando == true)
	{
		if (podeAtirar)
			return 2 + (int((timerFrame / tempoFrame)) % 3); //Frames 2-4 (Andando com a lâmina)
		
		return 10 + (int((timerFrame / tempoFrame)) % 3); //Frames 10-12 (Andando sem a lâmina)
	}

	//return (int((timerFrame / tempoFrame)) % 2);
}

sf::Vector2f CutMan::getEscalaCorreta()
{ 
	return sf::Vector2f(100, 100);
}

void CutMan::executar(float dt)
{
	mover(dt);

	if (!noChao)
		sofrerAcaoDaGravidade(dt);

	if (podeAtirar)
	{ 
		timerAtirar += dt;

		if (timerAtirar >= TEMPO_ANIMACAO_TIRO) estadoAnimacao.Atacando = true;

		if (timerAtirar >= TEMPO_ATIRAR)
		{
			velocidade = 0;
			atirar();
			timerAtirar = 0;
		}
	}

	timerFrame += dt;
}

void CutMan::danificar(Megaman* p)
{
	//std::cout << "Colidiu!\n";
	if (!p || p->getNumVidas() <= 0) return;

	p->machucar(forca);
}

std::string CutMan::getTextureFile()
{
	return "Sprites/Inimigos/CutMan.png";
}

void CutMan::salvar()
{
	int lugar = getId();
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()]["forca"] = forca;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()-1]["podeAtirar"] = podeAtirar;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()-1]["timerAtirar"] = timerAtirar;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()-1]["timerPerseguir"] = timerPerseguir;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()-1]["timerPular"] = timerPular;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()-1]["cooldownNoChao"] = cooldownNoChao;
	Inimigo::salvar();
}

void CutMan::carregar()
{
	int lugar = getId();
	indiceAtual = ++indiceCutMan;
	forca = dadosSalvos["id"][lugar][indiceAtual]["forca"];
	podeAtirar = dadosSalvos["id"][lugar][indiceAtual]["podeAtirar"];
	timerAtirar = dadosSalvos["id"][lugar][indiceAtual]["timerAtirar"];
	timerPerseguir = dadosSalvos["id"][lugar][indiceAtual]["timerPerseguir"];
	timerPular = dadosSalvos["id"][lugar][indiceAtual]["timerPular"];
	cooldownNoChao = dadosSalvos["id"][lugar][indiceAtual]["cooldownNoChao"];

	Inimigo::carregar();
}

bool CutMan::getPossoAtirar()
{
	return podeAtirar;
}