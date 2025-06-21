#include "Entidade.h"

Entidade::Entidade(): vivo(true), gravidade(300), executando(false), direita(false), velocidade(0), velVertical(0), velMax(0), noChao(false)//x(-1), y(-1)
{
}
int Entidade::qualEntidade = 0;
Entidade::~Entidade()
{
}

void Entidade::destruir()
{
	vivo = false;
}

const bool Entidade::getVivo()
{
	return vivo;
}

void Entidade::setVelocidade(const float v)
{
	velocidade = v;
}

float Entidade::getVelocidade()
{
	return velocidade;
}

void Entidade::setVelVertical(const float v)
{
	velVertical = v;
}

float Entidade::getVelVertical()
{
	return velVertical;
}

void Entidade::setNoChao(const bool noChao)
{
	this->noChao = noChao;
}

const bool Entidade::getNoChao()
{
	return noChao;
}

void Entidade::sofrerAcaoDaGravidade(float dt)
{
	velVertical += gravidade * dt;
}

const bool Entidade::getExecutando()
{
	return executando;
}

void Entidade::setExecutando(const bool exe)
{
	executando = executando;
}
void Entidade::salvar()
{
	int lugar = getId();
	if (lugar < 0 || lugar >= dadosSalvos["id"].size()) return; // Verifica se o lugar é válido
	
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["direita"] = direita;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["velocidade"] = velocidade;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["velVertical"] = velVertical;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["velMax"] = velMax;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["noChao"] = noChao;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["executando"] = executando;

	Ente::salvar();
}
