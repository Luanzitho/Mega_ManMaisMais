#include "CutMan.h"
#include "../../Gerenciadores/Gerenciador_Colisoes.h"

//#include <iostream>

CutMan::CutMan(): cooldownNoChao(0), timerAtirar(0), timerPerseguir(0), timerPular(0), podeAtirar(true)
{
	setTamanho(sf::Vector2f(70.f, 95.f));
	setId(8);
	setNumVidas(22 + nivel_maldade * 2);

	velMax = 200;
	
	qtdPontos += 900;

	forca = 2 + nivel_maldade;
}

int CutMan::indiceCutMan = -1;

CutMan::~CutMan()
{
}


void CutMan::atirar()
{
	//std::cout << "POW\n";
	sf::Vector2f pos = getCoords();

	//if (!GC || !LE) std::cout << "BOOM!\n";

	ProjetilCutMan* tiro = new ProjetilCutMan(pos, nivel_maldade, pMega->getCoords(), this);
	tiro->associaListaEntidades(LE);
	tiro->setGerenciadorGrafico(pGG);
	GC->incluirProjetil(tiro);
	LE->incluirEntidade(tiro);
	podeAtirar = false;

	setTamanho(sf::Vector2f(70.f, 70.f));
	setCoords(sf::Vector2f(getCoords().x, getCoords().y + 25));
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

	cooldownNoChao += dt;
	if (cooldownNoChao > 0.1 && noChao)
	{
		noChao = false;
		cooldownNoChao = 0;
	}

	timerPerseguir += dt;
	timerPular += dt;

	if (timerPerseguir >= 1) 
	{
		if (noChao && timerPular >= 3)
		{
			velVertical = -300;
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
	
		timerPerseguir = 0;
	}

	//else
	//{
	//	velVertical += gravidade * dt;
	//}

	if (velocidade > velMax) //Limita a velocidade
		velocidade = velMax;
	else if (velocidade < velMax * (-1))
		velocidade = velMax * (-1);

	posicao.x += velocidade * dt;
	posicao.y += velVertical * dt;

	setCoords(posicao);
}

void CutMan::executar(float dt)
{
	mover(dt);

	if (!noChao)
		sofrerAcaoDaGravidade(dt);

	if (podeAtirar)
	{ 
		timerAtirar += dt;

		if (timerAtirar >= 2)
		{
			atirar();
			timerAtirar = 0;
		}
	}
}

void CutMan::danificar(Megaman* p)
{
	//std::cout << "Colidiu!\n";
	if (!p || p->getNumVidas() <= 0) return;

	p->machucar(forca);
}

std::string CutMan::getTextureFile()
{
	if (podeAtirar)
	{
		if (direita)
			return "Sprites/Inimigos/CutMan1-L-dir.png";
		return "Sprites/Inimigos/CutMan1-L-esq.png";
	}
	else
	{
		if (direita)
			return "Sprites/Inimigos/CutMan1-dir.png";
		return "Sprites/Inimigos/CutMan1-esq.png";
	}
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
