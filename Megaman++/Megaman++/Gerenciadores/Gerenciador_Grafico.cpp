#include "Gerenciador_Grafico.h"
#include "../Entidades/Personagens/Megaman.h"

Gerenciador_Grafico* Gerenciador_Grafico::instancia = nullptr;

Gerenciador_Grafico::Gerenciador_Grafico(): window(sf::VideoMode(1280, 720), "Megaman++")
{
    //instancia = new Gerenciador_Grafico();
}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
}

void Gerenciador_Grafico::desenharEnte(Ente* pE)
{
    sf::RectangleShape corpo;
    sf::Texture textura;
    
    textura.loadFromFile(pE->getTextureFile());

    sf::Vector2f tam = pE->getTamanho();
    sf::Vector2f pos = pE->getCoords();


    corpo.setSize(tam);
    corpo.setPosition(pos);
    corpo.setTexture(&textura);

    window.draw(corpo);
    
    /*
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
    }*/
}

Gerenciador_Grafico* Gerenciador_Grafico::getInstancia() //Para instanciar um único Gerenciador_Grafico
{ 
    if (!instancia)
    {
        instancia = new Gerenciador_Grafico();
    }
    return instancia; 
}

bool Gerenciador_Grafico::janelaEstaAberta()
{
    return window.isOpen();
}

void Gerenciador_Grafico::fecharJanela()
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
