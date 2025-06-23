#include "ProjetilMegaman.h"
#include "../Personagens/Inimigo.h"

ProjetilMegaman::ProjetilMegaman(): direcao(0)
{
	doMega = true;

	setId(7);
}

int ProjetilMegaman::indiceProMega = -1;

ProjetilMegaman::ProjetilMegaman(sf::Vector2f posicao, bool direita): Projetil(500, 1)
{
	if (direita)
		direcao = 1;
	else
		direcao = -1;

	doMega = true;

	setId(7);

	setCoords(posicao);
	setTamanho(sf::Vector2f(30.f, 30.f));
}

ProjetilMegaman::~ProjetilMegaman()
{
}

void ProjetilMegaman::atingirInimigo(Inimigo* pI)
{
	if (!pI || pI->getNumVidas() <= 0) return;

	pI->machucar(dano);
	destruir();
}

void ProjetilMegaman::mover(float dt)
{
	sf::Vector2f posicao = getCoords();

	posicao.y += velVertical * dt;
	posicao.x += direcao * velocidade * dt;

	setCoords(posicao);
}

void ProjetilMegaman::executar(float dt)
{
	mover(dt);
	sofrerAcaoDaGravidade(dt);
	velVertical -= empuxo * dt; //Contrapõe a gravidade

	if (getCoords().x > 1300 || getCoords().x < -100)
		destruir();
}

std::string ProjetilMegaman::getTextureFile()
{
	return "Sprites/Projeteis/ProjetilMegaman.png";
}

void ProjetilMegaman::salvar()
{
	int lugar = getId();
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()]["direcao"] = direcao;
	Projetil::salvar();
}

void ProjetilMegaman::carregar()
{
	int lugar = getId();
	indiceAtual = ++indiceProMega;
	direcao = dadosSalvos["id"][lugar][indiceAtual]["direcao"];
	Projetil::carregar();
}