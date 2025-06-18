#pragma once

#include "../Ente.h"
#include "../Listas/ListaEntidades.h"
#include "../Gerenciadores/Gerenciador_Colisoes.h"
#include "../Entidades/Obstaculos/Plataforma.h"
#include "../Entidades/Personagens/BigEye.h"
#include "../Entidades/Personagens/Metall.h"
#include "../Entidades/Personagens/CutMan.h"
#include "../Entidades/Obstaculos/Mola.h"
#include "../Entidades/Obstaculos/Espinho.h"

#include <random>
#include <fstream>
#include <vector>
#include "../json.hpp"

using namespace nlohmann;

class GerenciadorColisoes {};

class Fase :public Ente
{
private:
	Gerenciador_Colisoes GC;

protected:
	std::vector<int> jaFoi;
	json faseJson;
	std::vector<int> tilesGid;
	sf::Texture imagemTiles;
	std::vector<sf::IntRect> tilesRects;
	std::random_device rd;
	int tileWidth;
	int columns;
	int tileCount;
	int ultimoSprite;
	Megaman* p1, *p2;
	std::vector<sf::Sprite> tilesSprites;
	std::vector<sf::Sprite> fundo1;
	std::vector<sf::Sprite> fundo2;
	std::vector<sf::Sprite> fundo3;
	std::vector<Plataforma*> plataformas;
	std::vector<Plataforma*> chao;
	std::vector<Inimigo*> inimigos;
	std::vector<Obstaculo*> obstaculos;
	ListaEntidades* LEs;
	//Mola* mola;
	bool acabou;
	int minInimigosFaceis;
	int minObstaculosFaceis;

public:
	Fase();
	~Fase();
	virtual void executar(float dt) = 0;
	void gerenciarColisoes();
	void criarInimigosFaceis();
	void criarChao();
	void criarPlataformas();
	virtual void criarInimigos() = 0;
	virtual void criarObstaculos() = 0;
	void desenharCenario();
	void pegarCamada(int i);
	void separaSprites();
	std::string getTextureFile();
	int aleatoriza(int limite1, int limite2);
	void moveMapa(float dt);
	void incluirInimigoGC(Inimigo* inimigo);
	void incluirMegaGC(Megaman* mega);
	void incluirObstaculoGC(Obstaculo* Obstaculo);
	Gerenciador_Colisoes* getGC();
	bool getAcabou();
	void setTwoPlayers();

};

