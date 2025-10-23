#include "Entidade.h"

Entidade::Entidade(): vivo(true), gravidade(300), executando(false), direita(false), velocidade(0), velVertical(0), velMax(0), noChao(false)//x(-1), y(-1)
{
	estadoAnimacao.Parado = true;
	estadoAnimacao.Andando = false;
	estadoAnimacao.Pulando = false;
	estadoAnimacao.Atacando = false;
	estadoAnimacao.Machucado = false;
	estadoAnimacao.Morrendo = false;

	estadoAnimacao.numFrames = 0;
	estadoAnimacao.frameAtual = 0;
	estadoAnimacao.alturaSprite = 0;
	estadoAnimacao.larguraSprite = 0;
	animado = false;
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

const bool Entidade::getDireita()
{
	return direita;
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
	executando = exe;
}

void Entidade::salvar()
{
	int lugar = getId();
	if (lugar < 0 || lugar >= dadosSalvos["id"].size()) return; // Verifica se o lugar é válido
	
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["vivo"] = vivo;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["direita"] = direita;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["noChao"] = noChao;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["velocidade"] = velocidade;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["velVertical"] = velVertical;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["velMax"] = velMax;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["noChao"] = noChao;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["executando"] = executando;

	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["timerFrame"] = timerFrame;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["tempoFrame"] = tempoFrame;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["tempoAcumulado"] = tempoAcumulado;
	
	//Parte da animação
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoParado"] = estadoAnimacao.Parado;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoAndando"] = estadoAnimacao.Andando;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoPulando"] = estadoAnimacao.Pulando;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoAtacando"] = estadoAnimacao.Atacando;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoMachucado"] = estadoAnimacao.Machucado;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoMorrendo"] = estadoAnimacao.Morrendo;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoAlturaSprite"] = estadoAnimacao.alturaSprite;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoLarguraSprite"] = estadoAnimacao.larguraSprite;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoNumFrames"] = estadoAnimacao.numFrames;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoFrameAtual"] = estadoAnimacao.frameAtual;

	Ente::salvar();
}

void Entidade::carregar()
{
	int lugar = getId();
	vivo = dadosSalvos["id"][lugar][indiceAtual]["vivo"];
	direita = dadosSalvos["id"][lugar][indiceAtual]["direita"];
	noChao = dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["direita"];
	velocidade = dadosSalvos["id"][lugar][indiceAtual]["velocidade"];
	velVertical = dadosSalvos["id"][lugar][indiceAtual]["velVertical"];
	velMax = dadosSalvos["id"][lugar][indiceAtual]["velMax"];
	noChao = dadosSalvos["id"][lugar][indiceAtual]["noChao"];
	executando = dadosSalvos["id"][lugar][indiceAtual]["executando"];

	timerFrame = dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["timerFrame"];
	tempoFrame = dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["tempoFrame"];
	tempoAcumulado = dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["tempoAcumulado"];

	estadoAnimacao.Parado = dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoParado"];
	estadoAnimacao.Andando = dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoAndando"];
	estadoAnimacao.Pulando = dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoPulando"];
	estadoAnimacao.Atacando = dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoAtacando"];
	estadoAnimacao.Machucado = dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoMachucado"];
	estadoAnimacao.Morrendo = dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoMorrendo"];
	estadoAnimacao.alturaSprite = dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoAlturaSprite"];
	estadoAnimacao.larguraSprite = dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoLarguraSprite"];
	estadoAnimacao.numFrames = dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoNumFrames"];
	estadoAnimacao.frameAtual = dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["estadoFrameAtual"];

	Ente::carregar();
}
