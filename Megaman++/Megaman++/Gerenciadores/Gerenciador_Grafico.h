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
	//sf::Texture* textura;
	//sf::Sprite* sprite;
	Gerenciador_Grafico(); //Padrão singleton, vídeo do Burda

public:
	
	~Gerenciador_Grafico();
	void desenharEnte(Ente* pE);
	static Gerenciador_Grafico* getInstancia();
	bool janelaEstaAberta();
	void fecharJanela();
	void limparJanela();
	void mostrarConteudoJanela();
};