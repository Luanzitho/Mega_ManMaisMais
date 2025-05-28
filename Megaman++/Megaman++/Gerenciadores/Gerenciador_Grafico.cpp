#include "Gerenciador_Grafico.h"

Gerenciador_Grafico::Gerenciador_Grafico()
{
    pGG = nullptr;
}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
}

void Gerenciador_Grafico::desenharEnte(Ente* pE)
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Megaman++");

    sf::RectangleShape corpo;
    sf::Texture* textura;

    textura = new sf::Texture();

    corpo.setSize(sf::Vector2f(50, 50));
    corpo.setPosition(sf::Vector2f(1550, 550));
    
    textura->loadFromFile(pE->getTextureFile());

    corpo.setTexture(textura);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        pE->executar();
        corpo.move(sf::Vector2f(0.01, 0));

        window.draw(corpo);
        window.draw(shape);
        window.display();
    }
}

Gerenciador_Grafico* Gerenciador_Grafico::getGerenciador_Grafico() { return pGG; }
