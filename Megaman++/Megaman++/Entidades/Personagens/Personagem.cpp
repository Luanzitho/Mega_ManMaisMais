#include "Personagem.h"

Personagem::Personagem(): num_vidas(0)
{
}

Personagem::Personagem(int v): num_vidas(v) //Acho até q dá pra remover hein
{
}

int Personagem::qualPersonagem = 0;

Personagem::~Personagem()
{
}

void Personagem::curar(const int hp)
{
	num_vidas = num_vidas + hp;
}

void Personagem::machucar(const int dmg)
{
	num_vidas = num_vidas - dmg;

	if (num_vidas <= 0)
		destruir();
}

void Personagem::setNumVidas(const int v)
{
	num_vidas = v;
}

int Personagem::getNumVidas()
{
	return num_vidas;
}

void Personagem::salvar()
{
	int lugar = getId();
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["numVidas"] = getNumVidas();

	Entidade::salvar();
}