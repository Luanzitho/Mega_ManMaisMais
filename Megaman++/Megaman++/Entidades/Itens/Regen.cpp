#include "Regen.h"
#include "../Personagens/Megaman.h"

Regen::Regen() : timerDespawn(0.f)
{
	std::mt19937 gen(rd()); //Motor aleatório (Mersenne Twister)

	tipoRegen = std::uniform_int_distribution<>(1, 3)(gen); //Variação entre 1 e 3

	if (tipoRegen == 1)
	{
		setTamanho(sf::Vector2f(16.f, 16.f));
		regenAmount = 3.f;
	}
	else if (tipoRegen == 2)
	{
		regenAmount = 10.f;
		setTamanho(sf::Vector2f(50.f, 50.f));
	}
	else
	{
		regenAmount = 20.f;
		setTamanho(sf::Vector2f(40.f, 50.f));
	}

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

	if(!noChao)
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
	if(tipoRegen == 1)
		return "Sprites/Itens/regenSmall.png";
	else if (tipoRegen == 2)
		return "Sprites/Itens/regenBig.png";
	else
		return "Sprites/Itens/energyDrink.png";
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