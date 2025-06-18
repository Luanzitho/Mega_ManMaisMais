#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include "../Ente.h"

class Ente;

class Gerenciador_Grafico
{
private:
	static Gerenciador_Grafico* instancia;
	sf::RenderWindow window;
	std::map<std::string, sf::Texture> texturas;
	//sf::RectangleShape* corpo;
	//sf::Texture textura;
	//sf::Sprite* sprite;
	Gerenciador_Grafico(); //Padrão singleton, vídeo do Burda

public:
	//Gerenciador_Grafico(); //Padrão luanzin kkkk
	~Gerenciador_Grafico();

	sf::Texture& getTextura(const std::string& caminho); //Para armazenar as texturas. Em teoria corrige os crashes por chamar toda hora a textura

	static Gerenciador_Grafico* getInstancia();
	void desenharEnte(Ente* pE);
	bool janelaEstaAberta();
	void eventoFecharJanela();
	void limparJanela();
	void mostrarConteudoJanela();
	void desenhaTexto(sf::Text text);
	void desenhaSprite(sf::Sprite sprite);
};