#include "Obstaculo.h"

Obstaculo::Obstaculo(): danoso(false), empuxo(300)
{
	setId(3);
}

Obstaculo::~Obstaculo()
{
}

void Obstaculo::salvar() 
{
	int lugar = getId();
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()-1]["danoso"] = danoso;
	Entidade::salvar();
}
