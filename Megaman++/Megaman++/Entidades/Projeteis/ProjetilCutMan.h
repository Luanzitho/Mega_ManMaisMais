#pragma once

#include "Projetil.h"

class Megaman;
class CutMan;

class ProjetilCutMan :public Projetil
{
private:
	float timerRetornar;
	bool limite;
	CutMan* mestre;
	sf::Vector2f alvo;
	sf::Vector2f direcao;
	static int indiceProCut;

public:
	ProjetilCutMan();
	ProjetilCutMan(sf::Vector2f posicao, int maldade, sf::Vector2f alvo, CutMan* mestre);
	~ProjetilCutMan();
	void atingirMegaman(Megaman* p);
	void perseguir(float dt);
	void retornar(float dt);
	void executar(float dt);
	std::string getTextureFile();
	void salvar();
	void carregar();
	void procurarMestre(CutMan* cut);
};