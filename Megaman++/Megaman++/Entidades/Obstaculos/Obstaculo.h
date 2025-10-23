#pragma once

#include "../Entidade.h"
#include "../Personagens/Personagem.h"

class Obstaculo :public Entidade
{
protected:
	bool danoso;
	const float empuxo;

public:
	Obstaculo();
	~Obstaculo();
	int getFrame();
	sf::Vector2f getEscalaCorreta();
	virtual void executar(float dt) = 0;
	virtual void obstaculizar(Entidade* pEnti) = 0;
	virtual std::string getTextureFile() = 0;
	virtual void salvar();
	virtual void carregar();
};

