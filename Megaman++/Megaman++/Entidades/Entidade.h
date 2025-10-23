#pragma once

#include "../Ente.h"
#include "../Entidades/EstadoAnimacao.h"

class Entidade:public Ente
{
protected:
	bool vivo;
	const float gravidade;
	bool direita;
	float velocidade;
	float velVertical;
	float velMax;
	bool noChao;
	bool executando;
	static int qualEntidade;
	
	float timerFrame;
	float tempoFrame;
	float tempoAcumulado;

public:
	EstadoAnimacao estadoAnimacao;
	Entidade();
	~Entidade();
	void destruir();
	const bool getVivo();
	void setVelocidade(float v);
	float getVelocidade();
	void setVelVertical(float v);
	float getVelVertical();
	void setNoChao(bool noChao);
	const bool getDireita();
	const bool getNoChao();

	virtual int getFrame() = 0;
	virtual sf::Vector2f getEscalaCorreta() = 0;

	void sofrerAcaoDaGravidade(float dt);
	virtual void executar(float dt) = 0;
	virtual std::string getTextureFile() = 0;
	const bool getExecutando();
	void setExecutando(const bool exe);
	virtual void salvar();
	virtual void carregar();
	//virtual void salvar() = 0;

	//void salvarDataBuffer(); 
};