#pragma once

#include "../Ente.h"

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
	//float x;
	//float y;
	//ostream buffer;

public:
	Entidade();
	~Entidade();
	void destruir();
	const bool getVivo();
	void setVelocidade(float v);
	float getVelocidade();
	void setVelVertical(float v);
	float getVelVertical();
	void setNoChao(bool noChao);
	bool getNoChao();
	void sofrerAcaoDaGravidade(float dt);
	virtual void executar(float dt) = 0;
	virtual std::string getTextureFile() = 0;
	bool getExecutando();
	void setExecutando(bool exe);
	//virtual void salvar() = 0;

	//void salvarDataBuffer(); 
};