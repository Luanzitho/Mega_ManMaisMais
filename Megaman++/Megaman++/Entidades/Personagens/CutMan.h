#pragma once

#define TEMPO_ATIRAR 1.75
#define TEMPO_PULAR 3
#define TEMPO_PERSEGUIR 1

#define TEMPO_ANIMACAO_TIRO 1.75

#define ALTURA_PULO -300 
#define VELOCIDADE_MAX 200

#include "Inimigo.h"
#include "../Projeteis/ProjetilCutMan.h"

class CutMan:public Inimigo
{
private:
	short int forca;
	bool podeAtirar;
	float timerAtirar;
	float timerPerseguir;
	float timerPular;
	float cooldownNoChao;
	static int indiceCutMan;

public:
	CutMan();
	~CutMan();
	void atirar();
	void possoAtirar();
	void mover(float dt);
	int getFrame();
	sf::Vector2f getEscalaCorreta();
	void executar(float dt);
	void danificar(Megaman* p);
	std::string getTextureFile();
	void salvar();
	void carregar();
	bool getPossoAtirar();
	static void resetIndice() { indiceCutMan = -1; }
};

