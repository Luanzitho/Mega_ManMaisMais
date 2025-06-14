#pragma once

#include "../Ente.h"
#include "../Listas/ListaEntidades.h"
#include "../Gerenciadores/Gerenciador_Colisoes.h"
#include "../Entidades/Obstaculos/Plataforma.h"
#include "../Entidades/Personagens/BigEye.h"
#include "../Entidades/Personagens/Metall.h"
#include "../Entidades/Personagens/CutMan.h"
#include "../Entidades/Obstaculos/Mola.h"

#include <fstream>
#include <vector>
#include "../json.hpp"

using namespace nlohmann;

class Fase:public Ente
{
private:
	
protected:
	Gerenciador_Colisoes GC;
	json faseJson;
	std::vector<int> tilesGid;
	sf::Texture imagemTiles;
	std::vector<sf::IntRect> tilesRects;
	sf::Vector2f posPlayer1;
	//std::vector<sf::Texture> tilesTextures;
	int tileWidth;
	int columns;
	int tileCount;
	Megaman* p1;
	Metall* met; //A REMOVER
	BigEye* big; //A REMOVER
	CutMan* cut; //A REMOVER
	std::vector<sf::Sprite> tilesSprites;
	std::vector<sf::Sprite> fundo1;
	std::vector<sf::Sprite> fundo2;
	std::vector<sf::Sprite> fundo3;
	std::vector<Plataforma*> plataformas;
	std::vector<Inimigo*> inimigos;
	std::vector<Obstaculo*> obstaculos;
	ListaEntidades* LEs;
	Mola* mola;

public:
	Fase();
	~Fase();
	virtual void executar(float dt) = 0;
	void gerenciarColisoes();
	void criarInimigosFaceis();
	void criarPlataformas();
	virtual void criarInimigos() = 0;
	virtual void criarObstaculos() = 0;
	void desenharCenario();
	void pegarCamada(int i);
	void separaSprites();
	std::string getTextureFile();
	void moveMapa();
	//sf::Texture recortarTextura(const sf::Texture& original, sf::IntRect recorte);
	//virtual std::string getMapaFase()=0;

};

