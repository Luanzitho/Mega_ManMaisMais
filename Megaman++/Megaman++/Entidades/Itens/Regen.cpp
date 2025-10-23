#include "Regen.h"
#include "../Personagens/Megaman.h"

Regen::Regen() : timerDespawn(0.f)
{
	std::mt19937 gen(rd()); //Motor aleatório (Mersenne Twister)

	tipoRegen = std::uniform_int_distribution<>(1, 3)(gen); //Variação entre 1 e 3

	if (tipoRegen == 1)
	{
		setTamanho(sf::Vector2f(16.f, 16.f));
		altura = largura = 16.f;
		regenAmount = 3.f;
	}
	else if (tipoRegen == 2)
	{
		regenAmount = 10.f;
		altura = largura = 40.f;
		setTamanho(sf::Vector2f(50.f, 50.f));
	}
	else
	{
		regenAmount = 28.f;
		altura = 50;
		largura = 40;
		setTamanho(sf::Vector2f(40.f, 50.f));
	}

	estadoAnimacao.numFrames = 6;
	estadoAnimacao.frameAtual = 0;
	estadoAnimacao.alturaSprite = 16;
	estadoAnimacao.larguraSprite = 16;

	tempoFrame = 0.2f; //Tempo entre frames
	tempoAcumulado = 0.f;
	animado = true;

	pGS->carregarEfeito("HealSmall", "Sound/Effects/healsmall.wav");
	pGS->carregarEfeito("HealBig", "Sound/Effects/healbig.wav");
	pGS->carregarEfeito("1up", "Sound/Effects/1up.wav");
}

Regen::~Regen()
{
}

void Regen::executar(float dt)
{
	timerDespawn += dt;
	timerFrame += dt;

	if (!noChao)
		sofrerAcaoDaGravidade(dt);

	if (timerDespawn >= 5.f)
		destruir();
}

void Regen::regenerar(Megaman* p)
{
	if (tipoRegen == 1)
		pGS->tocarEfeito("HealSmall");
	else if (tipoRegen == 2)
		pGS->tocarEfeito("HealBig");
	else
		pGS->tocarEfeito("1up");

	p->curar(regenAmount);
	destruir();
}

std::string Regen::getTextureFile()
{
	return "Sprites/Itens/regen.png";
}

void Regen::serPego(Megaman* p)
{
	regenerar(p);
}

void Regen::mover(float dt)
{
	sf::Vector2f posicao = getCoords();

	posicao.y += velVertical * dt;

	setCoords(posicao);
}

int Regen::getFrame()
{ 
	int offset = (int)(timerFrame / tempoFrame) % 2; // 0 ou 1
	return (tipoRegen - 1) * 2 + offset;
}

sf::Vector2f Regen::getEscalaCorreta()
{
	if (tipoRegen == 1)
		return sf::Vector2f(32.f, 32.f);
	else if (tipoRegen == 2)
		return sf::Vector2f(50.f, 50.f);
	else
		return sf::Vector2f(50.f, 60.f);
}

void Regen::associaListaEntidades(ListaEntidades* pLista)
{
	LE = pLista;
}

void Regen::associaGerenciadorColisoes(Gerenciador_Colisoes* gc)
{
	GC = gc;
}

void Regen::salvar()
{
	Item::salvar();
	dadosSalvos["id"][getId()][indiceAtual]["regenAmount"] = regenAmount;
}

void Regen::carregar()
{
	Item::carregar();
	regenAmount = dadosSalvos["id"][getId()][indiceAtual]["regenAmount"];
}