#include "ProjetilCutMan.h"

#include "../Personagens/Megaman.h"
#include "../Personagens/CutMan.h"

#include "../../Gerenciadores/Gerenciador_Colisoes.h"

#include <cmath>

ProjetilCutMan::ProjetilCutMan(): timerRetornar(0), mestre(nullptr), limite(false)
{
	setId(6);

	estadoAnimacao.numFrames = 4;
	estadoAnimacao.frameAtual = 0;
	estadoAnimacao.alturaSprite = 32;
	estadoAnimacao.larguraSprite = 32;

	tempoFrame = 0.1f; //Tempo entre frames
	tempoAcumulado = 0.f;
	animado = true;
}

int ProjetilCutMan::indiceProCut = -1;

ProjetilCutMan::ProjetilCutMan(sf::Vector2f posicao, int maldade, sf::Vector2f alvo, CutMan* mestre): Projetil(350, maldade + 4), timerRetornar(0), limite(false)
{
	setCoords(posicao);

	doMega = false;

	setId(6);

	this->alvo = alvo;
	this->mestre = mestre;

	direcao = alvo - getCoords(); //Referência normalização de vetor para disparas em 360º - Youtuber Suraj Sharma
	float comprimento = sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
	direcao /= comprimento;

	setTamanho(sf::Vector2f(40.f, 40.f));

	estadoAnimacao.numFrames = 4;
	estadoAnimacao.frameAtual = 0;
	estadoAnimacao.alturaSprite = 32;
	estadoAnimacao.larguraSprite = 32;

	tempoFrame = 0.1f; //Tempo entre frames
	tempoAcumulado = 0.f;
	animado = true;
}

ProjetilCutMan::~ProjetilCutMan()
{
	mestre = nullptr;
}

void ProjetilCutMan::atingirMegaman(Megaman* p)
{
	if (!p || p->getNumVidas() <= 0) return;

	p->machucar(dano);
	//std::cout << "Atingido!\n";
}

void ProjetilCutMan::perseguir(float dt)
{
	sf::Vector2f posicao = getCoords();

	posicao += direcao * velocidade * dt;
	setCoords(posicao);
}

void ProjetilCutMan::retornar(float dt)
{
	sf::Vector2f posicao = getCoords();

	direcao = mestre->getCoords() - getCoords(); //Referência normalização de vetor para disparas em 360º - Youtuber Suraj Sharma
	float comprimento = sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
	direcao /= comprimento;

	posicao += direcao * velocidade * dt;

	setCoords(posicao);

	if (abs(posicao.x - mestre->getCoords().x) < 20 && abs(posicao.y - mestre->getCoords().y) < 15) //A lâmina retorna para a cabeça dele
	{
		mestre->possoAtirar();
		destruir();
	}
}

int ProjetilCutMan::getFrame()
{
	return (1 + (int((timerFrame / tempoFrame)) % 3));
}

sf::Vector2f ProjetilCutMan::getEscalaCorreta()
{
	return sf::Vector2f(50.f, 50.f);
}

void ProjetilCutMan::executar(float dt)
{
	timerRetornar += dt;
	sofrerAcaoDaGravidade(dt);
	velVertical -= empuxo * dt; //Contrapõe a gravidade

	if (mestre && !(mestre->getVivo()))
		destruir();

	if (mestre && timerRetornar < 1 && !limite)
	{
		perseguir(dt);
	}

	if (mestre && timerRetornar >= 1 || limite)
	{
		retornar(dt);
	}

	timerFrame += dt;
}

std::string ProjetilCutMan::getTextureFile()
{
	return "Sprites/Projeteis/RollingCutter.png";
}

void ProjetilCutMan::salvar()
{
	int lugar = getId();
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()]["timerRetornar"] = timerRetornar;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()-1]["limite"] = limite;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()-1]["alvo"]["x"] = alvo.x;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["alvo"]["y"] = alvo.y;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["mestre"]["id"] = mestre->getId(); // Aqui é necessário salvar o ID do mestre, não o ponteiro
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["mestre"]["position"]["x"] = mestre->getCoords().x; // posicao do mestre para achar na hora que puxar o save
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["mestre"]["position"]["y"] = mestre->getCoords().y; // posicao do mestre para achar na hora que puxar o save
	Projetil::salvar();
}

void ProjetilCutMan::carregar()
{
	int lugar = getId();
	indiceAtual = ++indiceProCut;
	timerRetornar = dadosSalvos["id"][lugar][indiceAtual]["timerRetornar"];
	limite = dadosSalvos["id"][lugar][indiceAtual]["limite"];
	alvo.x = dadosSalvos["id"][lugar][indiceAtual]["alvo"]["x"];
	alvo.y = dadosSalvos["id"][lugar][indiceAtual]["alvo"]["y"];

	Projetil::carregar();
	
}

void ProjetilCutMan::procurarMestre(CutMan* cut)
{
	if (!cut) return;

	if (!cut->getPossoAtirar()) mestre = cut;
	/*if (ini->getCoords().x == dadosSalvos["id"][getId()][indiceAtual]["mestre"]["position"]["x"])
		if (ini->getCoords().y == dadosSalvos["id"][getId()][indiceAtual]["mestre"]["position"]["y"])
				mestre = ini;*/
}

