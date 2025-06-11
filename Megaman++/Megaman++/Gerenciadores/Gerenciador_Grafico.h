#pragma once

#include <SFML/Graphics.hpp>
#include "../Ente.h"

class Ente;

class Gerenciador_Grafico
{
private:
	static Gerenciador_Grafico* instancia;
	sf::RenderWindow window;
	//sf::RectangleShape* corpo;
	//sf::Texture textura;
	//sf::Sprite* sprite;
	//Gerenciador_Grafico(); //Padrão singleton, vídeo do Burda

public:
	Gerenciador_Grafico(); //Padrão luanzin kkkk
	~Gerenciador_Grafico();
	static Gerenciador_Grafico* getInstancia();
	void desenharEnte(Ente* pE);
	bool janelaEstaAberta();
	void eventoFecharJanela();
	void limparJanela();
	void mostrarConteudoJanela();
	void desenhaTexto(sf::Text text);
	void desenhaSprite(sf::Sprite sprite);
};