#include "BigEye.h"
#include <time.h>

BigEye::BigEye() : aceleracao(150), timerAtaque(0)
{
	srand(time(NULL));
	setId(4);
	raio = rand() % 41 + 80;

	setTamanho(sf::Vector2f(raio, 120.f));

	velMax = 50;

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
}

BigEye::~BigEye()
{
}
int BigEye::indiceBig = -1;// inicia os indices para carregar o save

void BigEye::saltar() //Salto normal
{
	velVertical = -250;
}

void BigEye::saltar(int chance) //Salto carregado (+ dano)
{
	velVertical = -400;
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
		//velVertical += gravidade * dt;
		
		if (direita)
			velocidade += velMax;
		else
			velocidade -= velMax;

		posicao.x += velocidade * dt;
	}

	else //Se estiver no chão, procura o player e pula se o timer estiver em 3.5
	{
		timerAtaque += dt; //Quando o timer atinge 3.5 o BigEye pode pular

		velocidade = 0;

		if (alvo.x > getCoords().x) //Só confere as coordenadas do player quando o Big Eye está no chão
			direita = true;
		else
			direita = false;

		if (timerAtaque >= 1)
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

			noChao = false;

			timerAtaque = 0;
		}
	}

	posicao.y += velVertical * dt;

	setCoords(posicao);
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
	}
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