#include "Obstaculo.h"

Obstaculo::Obstaculo(): danoso(false), empuxo(300)
{
	setId(3);
}

Obstaculo::~Obstaculo()
{
}

int Obstaculo::getFrame() { return 0; }
//Funções para entidades com animação
sf::Vector2f Obstaculo::getEscalaCorreta() { return sf::Vector2f(0, 0); }

void Obstaculo::salvar() 
{
	int lugar = getId();
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()-1]["danoso"] = danoso;
	Entidade::salvar();
}

void Obstaculo::carregar()
{
	int lugar = getId();
	danoso = dadosSalvos["id"][lugar][indiceAtual]["danoso"];
	Entidade::carregar();
}
