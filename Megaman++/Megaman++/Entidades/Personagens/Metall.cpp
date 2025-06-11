#include "Metall.h"
#include "../../Gerenciadores/Gerenciador_Colisoes.h"

Metall::Metall(): timerEsconder(0), timerAtirar(0), LE(nullptr), GC(nullptr)
{
	setNumVidas(2);

	setTamanho(sf::Vector2f(50.f, 50.f));
}

Metall::~Metall()
{
}

void Metall::associaListaEntidades(ListaEntidades* pLista)
{
	LE = pLista;
}

void Metall::associaGerenciadorColisoes(Gerenciador_Colisoes* GC)
{
	this->GC = GC;
}

void Metall::atirar()
{
	sf::Vector2f pos = getCoords();

	if (pMega->getCoords().x > pos.x)
		direita = true;
	else
		direita = false;

	ProjetilMetall* tiro = new ProjetilMetall(pos, direita);
	LE->incluirEntidade(tiro);
	tiro->associaListaEntidades(LE);
	tiro->setGerenciadorGrafico(pGG);
	GC->incluirProjetil(tiro);
}

void Metall::executar(float dt)
{
	timerAtirar += dt;
	timerEsconder += dt;

	if (timerAtirar >= 5)
	{
		atirar();
		timerAtirar = 0;
	}
	//esconder()
}

void Metall::mover(float dt)
{
	return; //Ele não se move no jogo
}

void Metall::danificar(Megaman* p)
{
	p->machucar(1);
}

std::string Metall::getTextureFile()
{
	return "Sprites/Inimigos/Metall.png";
}