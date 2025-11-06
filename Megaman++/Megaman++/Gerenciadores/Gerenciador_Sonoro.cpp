#include "Gerenciador_Sonoro.h"

Gerenciador_Sonoro* Gerenciador_Sonoro::instancia = nullptr;

Gerenciador_Sonoro::Gerenciador_Sonoro()
{
}

Gerenciador_Sonoro* Gerenciador_Sonoro::getInstancia()
{
    if (!instancia)
    {
        instancia = new Gerenciador_Sonoro();
    }
    return instancia;
}

Gerenciador_Sonoro::~Gerenciador_Sonoro()
{
}

bool Gerenciador_Sonoro::carregarMusica(const std::string& arquivo)
{
    //std::cout << "maoe";
    return musicaFundo.openFromFile(arquivo);
}

void Gerenciador_Sonoro::tocarMusica(bool loop)
{
    musicaFundo.setLoop(loop);
    musicaFundo.play();
}

void Gerenciador_Sonoro::pausarMusica() { musicaFundo.pause(); }

void Gerenciador_Sonoro::pararMusica() { musicaFundo.stop(); }

void Gerenciador_Sonoro::setVolumeMusica(float volume)
{
    musicaFundo.setVolume(volume);
}

bool Gerenciador_Sonoro::carregarEfeito(const std::string& nome, const std::string& arquivo) //Efeitos sonoros
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(arquivo))
        return false;

    buffers[nome] = buffer;

    sf::Sound som;
    som.setBuffer(buffers[nome]);
    sons[nome] = som;

    return true;
}

void Gerenciador_Sonoro::tocarEfeito(const std::string& nome)
{
    if (sons.find(nome) != sons.end())
        sons[nome].play();
}

void Gerenciador_Sonoro::setVolumeEfeitos(float volume)
{
    for (auto it = sons.begin(); it != sons.end(); ++it)
    {
        it->second.setVolume(volume);
    }
}
