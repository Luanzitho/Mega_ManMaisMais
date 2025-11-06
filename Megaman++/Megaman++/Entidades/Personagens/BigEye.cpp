#include "BigEye.h"
#include <time.h>

BigEye::BigEye() : aceleracao(150), timerAtaque(0)
{
	srand(time(NULL));
	setId(4);
	raio = rand() % 41 + 80;

	setTamanho(sf::Vector2f(raio, 120.f));

	velMax = VELOCIDADE_MAX;

	qtdPontos += 200;

	if (nivel_maldade == 1)
	{
		dano = 2;
		setNumVidas(15);
	}
	else if (nivel_maldade == 2)
	{
		dano = 4;
		setNumVidas(15);
	}
	else if (nivel_maldade == 3)
	{
		dano = 4;
		setNumVidas(20);
	}

	danoNormal = dano;

	pGS->carregarEfeito("BigEye", "Sound/Effects/bigeye.wav");
	pGS->setVolumeEfeitos(100.f);

	estadoAnimacao.numFrames = 6;
	estadoAnimacao.frameAtual = 0;
	estadoAnimacao.alturaSprite = 48;
	estadoAnimacao.larguraSprite = 32;

	tempoFrame = 0.1f; //Tempo entre frames
	tempoAcumulado = 0.f;
	animado = true;
}

BigEye::~BigEye()
{
}
int BigEye::indiceBig = -1;// inicia os indices para carregar o save

void BigEye::saltar() //Salto normal
{
	velVertical = ALTURA_PULO;
}

void BigEye::saltar(int chance) //Salto carregado (+ dano)
{
	velVertical = ALTURA_PULO_CRITICO;
	dano = dano * chance; //Dano em dobro no crítico
}

void BigEye::mover(float dt)
{
	sf::Vector2f posicao = getCoords();
	sf::Vector2f alvo = pMega->getCoords();

	int chanceCritico = rand() % 5; //Big Eye tem chance de dar um ataque crítico (maior dano)

	if (velocidade > velMax) //Limita a velocidade
		velocidade = velMax;
	else if (velocidade < velMax * (-1))
		velocidade = velMax * (-1);
	else
		velocidade = velocidade * 0.9;

	if (!noChao) //Só se movimenta se estiver no ar
	{
		estadoAnimacao.Pulando = true;
		estadoAnimacao.Atacando = false;
		
		if (direita)
			velocidade += velMax;
		else
			velocidade -= velMax;

		posicao.x += velocidade * dt;
	}
	else //Se estiver no chão, procura o player e pula se o timer estiver em 3.5
	{
		timerAtaque += dt; //Quando o timer atinge o tempo o BigEye pode pular
		estadoAnimacao.Pulando = false;

		velocidade = 0;

		if (alvo.x > getCoords().x) //Só confere as coordenadas do player quando o Big Eye está no chão
			direita = true;
		else
			direita = false;
		
		if (timerAtaque >= TEMPO_ANIMACAO_PULO)
			estadoAnimacao.Atacando = true;

		if (timerAtaque >= TEMPO_PULO)
		{
			if (chanceCritico == 2)
			{
				saltar(chanceCritico);
			}
			else
			{
				saltar();
				dano = danoNormal;
			}
			pGS->tocarEfeito("BigEye");

			noChao = false;

			timerAtaque = 0;
		}
	}

	posicao.y += velVertical * dt;

	setCoords(posicao);
}

int BigEye::getFrame()
{
	if (estadoAnimacao.Atacando == true)
		return ((nivel_maldade * 2) - 1);
	return ((nivel_maldade * 2) - 2);
}

sf::Vector2f BigEye::getEscalaCorreta()
{
	return sf::Vector2f(raio, 120.f);
}

void BigEye::executar(float dt)
{
	mover(dt);

	if (!noChao)
		sofrerAcaoDaGravidade(dt);
}

void BigEye::danificar(Megaman* p)
{
	p->machucar(dano);
}

std::string BigEye::getTextureFile()
{
	/*
	if (nivel_maldade == 1)
	{
		if (direita)
			return "Sprites/Inimigos/BigEye1-blue-dir.png";
		return "Sprites/Inimigos/BigEye1-blue-esq.png";
	}
	else if (nivel_maldade == 2)
	{
		if (direita)
			return "Sprites/Inimigos/BigEye1-red-dir.png";
		return "Sprites/Inimigos/BigEye1-red-esq.png";
	}
	else
	{
		if (direita)
			return "Sprites/Inimigos/BigEye1-BAD-dir.png";
		return "Sprites/Inimigos/BigEye1-BAD-esq.png";
	}*/
	return "Sprites/Inimigos/BigEye.png";
}

void BigEye::salvar()
{
	int lugar = getId();
	//salva os dados pertinentes a classe atual
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()]["aceleracao"] = aceleracao;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["timerAtaque"] = timerAtaque;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["danoNormal"] = danoNormal;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["raio"] = raio;
	Inimigo::salvar();
}

void BigEye::carregar()
{
	int lugar = getId();
	indiceAtual = ++indiceBig;
	//carrega os atributos da classe atual
	aceleracao=dadosSalvos["id"][lugar][indiceAtual]["aceleracao"];
	timerAtaque=dadosSalvos["id"][lugar][indiceAtual]["timerAtaque"];
	danoNormal=dadosSalvos["id"][lugar][indiceAtual]["danoNormal"];
	raio=dadosSalvos["id"][lugar][indiceAtual]["raio"] = raio;
	Inimigo::carregar();
}