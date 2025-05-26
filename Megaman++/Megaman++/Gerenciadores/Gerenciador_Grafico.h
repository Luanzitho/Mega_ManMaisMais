#pragma once
#ifndef _GERENCIADOR_GRAFICO_H_
#define _GERENCIADOR_GRAFICO_H_

#include <SFML/Graphics.hpp>
#include "../Ente.h"

class Gerenciador_Grafico
{
private:
	Gerenciador_Grafico* pGG; //Deve ser útil, visto que só tem um objeto de Gerenciador_Grafico no diagrama e o outro é ponteiro
	sf::RenderWindow* window;
	sf::RectangleShape* corpo;
	sf::Texture* textura;
	sf::Sprite* sprite;

public:
	Gerenciador_Grafico();
	~Gerenciador_Grafico();
	void desenharEnte(Ente* pE, char file[], sf::Vector2f coords);
	Gerenciador_Grafico* getGerenciador_Grafico();
	//bool windowIsOpen(sf::RenderWindow* w); Conferir se a janela está aberta, ainda não pensei em como fazer o loop que confere isso,
	//então está apenas comentada como ideia
};

#endif // _GERENCIADOR_GRAFICO_H_