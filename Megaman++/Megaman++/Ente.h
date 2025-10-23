#pragma once

#include "Gerenciadores/Gerenciador_Grafico.h"
//#include "Gerenciadores/Gerenciador_Colisoes.h"
#include <string>
#include <fstream>
#include "json.hpp"
#include "Gerenciadores/Gerenciador_Sonoro.h"

using namespace nlohmann;
class Gerenciador_Grafico;

class Ente
{
protected:
	int id;
	Gerenciador_Grafico* pGG;
	AudioManager* pGS;
	//Gerenciador_Colisoes* pGC;
	sf::Vector2f coords;
	sf::Vector2f tamanho;
	static json dadosSalvos;
	int indiceAtual;

	bool animado;

public:
	Ente();
	Ente(sf::Vector2f coordsIni, sf::Vector2f size);
	~Ente();
	void setGerenciadorGrafico(Gerenciador_Grafico* p);
	//void setGerenciadorColisoes(Gerenciador_Colisoes* p);
	void setId(const int id);
	bool operator==(int id) const;
	const int getId();
	void setAnimado(const bool animado);
	const bool getAnimado();
	virtual void executar(float dt) = 0;
	virtual std::string getTextureFile() = 0;
	const sf::Vector2f getTamanho();
	void setTamanho(const sf::Vector2f size);
	const sf::Vector2f getCoords(); 
	void setCoords(const sf::Vector2f coordenadas);
	void desenhar();
	virtual void salvar();
	virtual void carregar();
};