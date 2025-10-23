#include "Gerenciador_Grafico.h"
#include "../Entidades/Entidade.h"
#include "../Entidades/Personagens/Megaman.h"
#include <iostream>

Gerenciador_Grafico* Gerenciador_Grafico::instancia = nullptr;

Gerenciador_Grafico::Gerenciador_Grafico(): window(sf::VideoMode(1280, 720), "Mega Man++", sf::Style::Titlebar | sf::Style::Close)
{
    window.setFramerateLimit(60);

    sf::Image icone;
    //icone.loadFromFile("Sprites/Menu/icone.png");

    if (!icone.loadFromFile("Sprites/Menu/icone.png"))
    {
        std::cout << "Falha ao carregar icone!" << std::endl;
    }

    window.setIcon(icone.getSize().x, icone.getSize().y, icone.getPixelsPtr());

    posicionarConsole(1700, 100); //Posiciona o console ao lado da janela do jogo

	texturaHpBar.loadFromFile("Sprites/Megaman/HPBar/HPBar.png");
	spriteHpBar.setTexture(texturaHpBar);
}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
    //delete instancia;
}

Gerenciador_Grafico* Gerenciador_Grafico::getInstancia() //Para instanciar um único Gerenciador_Grafico
{ 
    if (!instancia)
    {
        instancia = new Gerenciador_Grafico();
    }
    return instancia; 
}

sf::Texture& Gerenciador_Grafico::getTextura(const std::string& caminho)
{
    auto it = texturas.find(caminho);
    if (it != texturas.end())
        return it->second;

    // Cria textura diretamente dentro do map
    texturas[caminho] = sf::Texture();
    if (!texturas[caminho].loadFromFile(caminho))
        std::cout << "Falha ao carregar textura: " << caminho << std::endl;

    return texturas[caminho];
}

void Gerenciador_Grafico::desenharEnte(Ente* pE)
{
    if (!pE) return;

    if(pE->getAnimado()) //Se tiver animações, entra aqui
    {
        Entidade* pEnt = static_cast<Entidade*>(pE);
        animarPersonagem(pEnt);
        return;
	}

    //Se tiver um único frame
    sf::RectangleShape corpo;
    const std::string& caminho = pE->getTextureFile();
    sf::Texture& textura = getTextura(caminho);

    sf::Vector2f tam = pE->getTamanho();
    sf::Vector2f pos = pE->getCoords();

    corpo.setSize(tam);
    corpo.setPosition(pos);
    corpo.setTexture(&textura);

    window.draw(corpo);
}

void Gerenciador_Grafico::animarPersonagem(Entidade* p)
{
    if (!p) return;

    sf::Sprite sprite;
    sf::Texture& textura = getTextura(p->getTextureFile());
    sprite.setTexture(textura);

    int frameAtual = p->getFrame();

    int texW = static_cast<int>(textura.getSize().x);
    int texH = static_cast<int>(textura.getSize().y);
    int numFrames = (p->estadoAnimacao.numFrames > 0) ? p->estadoAnimacao.numFrames : 1;
    int larguraSprite = texW / numFrames;
    int alturaSprite = texH;

    sprite.setTextureRect(sf::IntRect(frameAtual * larguraSprite, 0, larguraSprite, alturaSprite));

    sf::Vector2f tamanhoVisual = p->getEscalaCorreta();
    sf::Vector2f hitbox = p->getTamanho();

    //Correção da escala
    float scaleX = tamanhoVisual.x / static_cast<float>(larguraSprite);
    float scaleY = tamanhoVisual.y / static_cast<float>(alturaSprite);

    float xPos, yPos;
    yPos = p->getCoords().y + hitbox.y - tamanhoVisual.y;

    if (p->getDireita())
    {
        sprite.setScale(scaleX, scaleY);
        xPos = p->getCoords().x + (hitbox.x - tamanhoVisual.x) / 2.0f;
    }
    else
    {
        sprite.setScale(-scaleX, scaleY);
        xPos = p->getCoords().x + (hitbox.x + tamanhoVisual.x) / 2.0f; //Espelha a imagem se estiver olhando para a esquerda
    }

    sprite.setPosition(xPos, yPos);

    bool visivel = true;
    Megaman* m = dynamic_cast<Megaman*>(p); //Para o Mega Man quando estiver invencível
    if (m && m->getInvencivel())
    {
        //Pisca a cada 0.1s
        float tempoPiscar = 0.1f; // segundos
        float tempoAtual = relogioGlobal.getElapsedTime().asSeconds();

        int fase = static_cast<int>(tempoAtual / tempoPiscar);
        visivel = (fase % 2 == 0);
    }

    if (visivel)
        window.draw(sprite);
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

        
        // Captura as teclas digitadas (caracteres válidos)
        if (evento.type == sf::Event::TextEntered) {
            // Ignora teclas de controle (ex.: backspace, enter, etc)
            
            if (evento.text.unicode < 128 && evento.text.unicode >= 32) {
                std::cout << "entrou2" << std::endl;
                textoDigitado += static_cast<char>(evento.text.unicode);
            }

            // Se quiser, pode adicionar tratamento de Backspace:
            if (evento.text.unicode == 8 && !textoDigitado.empty()) { // 8 = Backspace
                textoDigitado.pop_back();
            }
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

void Gerenciador_Grafico::desenhar(sf::Text text)
{
	window.draw(text);
}

void Gerenciador_Grafico::desenhar(sf::Sprite sprite)
{
    window.draw(sprite);
}

void Gerenciador_Grafico::desenharBarraVida(Ente* pE, float hp, sf::Vector2f posicao)
{
    float largura = 3;
	float altura = 3;

    int cont = 28 - hp;

    spriteHpBar.setTextureRect(sf::IntRect(0+8*cont, 0, 8, 56));

    spriteHpBar.setScale(largura, altura);
	spriteHpBar.setPosition(posicao.x, posicao.y + 50);

	window.draw(spriteHpBar);
}

void Gerenciador_Grafico::desenharPontos(int qtdPontos, sf::Vector2f posicao)
{
    sf::Font fonte;
    if (!fonte.loadFromFile("Fontes/Pixelify_Sans/static/PixelifySans-Regular.ttf"))
    {
        std::cout << "Erro ao carregar fonte de pontos!" << std::endl;
        return;
    }

    sf::Text textoPontos;
    textoPontos.setFont(fonte);
    textoPontos.setString("Pontos: " + std::to_string(qtdPontos));
    textoPontos.setCharacterSize(36);
    textoPontos.setFillColor(sf::Color::White);
    textoPontos.setPosition(posicao);
	window.draw(textoPontos);
}

std::string Gerenciador_Grafico::getTexto()
{
    return textoDigitado;
}

void Gerenciador_Grafico::limpaTexto()
{
    textoDigitado.clear();
}

void Gerenciador_Grafico::fecharJanela()
{
	window.close();
}

