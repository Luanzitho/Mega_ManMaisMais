#include <SFML/Graphics.hpp>

#include "Jogo.h"
#include "Ente.h"
#include "Entidades/Entidade.h"
#include "Entidades/Personagens/Megaman.h"
#include "Gerenciadores/Gerenciador_Grafico.h"

int main()
{
    //Jogo jog;
    //jog.executar();

    //TESTE MEGAMAN
    Megaman* p1;
    Megaman* p2;
    p1 = new Megaman(true);
    p2 = new Megaman(false);

    Gerenciador_Grafico* GG = Gerenciador_Grafico::getInstancia();

    p1->setCoords(sf::Vector2f(550.f, 680.f));
    p1->setTamanho(sf::Vector2f(100.f, 100.f));

    p2->setCoords(sf::Vector2f(550.f, 780.f));
    p2->setTamanho(sf::Vector2f(100.f, 100.f));

    while (GG->janelaEstaAberta())
    {
        GG->fecharJanela();
        GG->limparJanela();
        p1->executar();
        p2->executar();
        GG->desenharEnte(static_cast<Ente*>(p1));
        GG->desenharEnte(static_cast<Ente*>(p2));
        GG->mostrarConteudoJanela();
    }
    /*sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Megaman++");
    
    p1.setCoords(sf::Vector2f(1250.f, 680.f));
    p1.setTamanho(sf::Vector2f(100.f, 100.f));

    p2.setCoords(sf::Vector2f(550.f, 680.f));
    p2.setTamanho(sf::Vector2f(100.f, 100.f));

    sf::RectangleShape corpo, corpo2;
    sf::Texture textura, textura2;

    corpo.setSize(p1.getTamanho());
    corpo2.setSize(p2.getTamanho());

    textura.loadFromFile(p1.getTextureFile());
    corpo.setTexture(&textura);

    textura2.loadFromFile(p2.getTextureFile());
    corpo2.setTexture(&textura2);

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

        p1.executar();
        corpo.setPosition(p1.getCoords());
        window.draw(corpo);

        p2.executar();
        corpo2.setPosition(p2.getCoords());
        window.draw(corpo2);

        window.draw(shape);
        window.display();
    }*/
    return 0;
}