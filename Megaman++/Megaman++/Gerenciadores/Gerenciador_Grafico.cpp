#include "Gerenciador_Grafico.h"
#include "../Entidades/Personagens/Megaman.h"

Gerenciador_Grafico* Gerenciador_Grafico::instancia = nullptr;

Gerenciador_Grafico::Gerenciador_Grafico(): window(sf::VideoMode(1280, 720), "Megaman++")
{
    window.setFramerateLimit(60);
}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
}

Gerenciador_Grafico* Gerenciador_Grafico::getInstancia() //Para instanciar um único Gerenciador_Grafico
{ 
    if (!instancia)
    {
        instancia = new Gerenciador_Grafico();
    }
    return instancia; 
}

void Gerenciador_Grafico::desenharEnte(Ente* pE)
{
    if (!pE) return;
    
    sf::RectangleShape corpo;

    sf::Texture textura;
    textura.loadFromFile(pE->getTextureFile());

    sf::Vector2f tam = pE->getTamanho();
    sf::Vector2f pos = pE->getCoords();


    corpo.setSize(tam);
    corpo.setPosition(pos);
    corpo.setTexture(&textura);

    window.draw(corpo);
}

bool Gerenciador_Grafico::janelaEstaAberta()
{
    return window.isOpen();
}

void Gerenciador_Grafico::eventoFecharJanela()
{
    sf::Event evento;

    while (window.pollEvent(evento)) 
    {
        if (evento.type == sf::Event::Closed) 
        {
            window.close();
        }
    }
}

void Gerenciador_Grafico::limparJanela()
{
    window.clear();
}

void Gerenciador_Grafico::mostrarConteudoJanela()
{
    window.display();
}

void Gerenciador_Grafico::desenhaTexto(sf::Text text)
{
	window.draw(text);
}

void Gerenciador_Grafico::desenhaSprite(sf::Sprite sprite)
{
    window.draw(sprite);
}
