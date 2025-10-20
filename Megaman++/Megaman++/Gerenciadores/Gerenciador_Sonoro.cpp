#include "Gerenciador_Sonoro.h"

AudioManager* AudioManager::instancia = nullptr;

AudioManager::AudioManager()
{
}

AudioManager* AudioManager::getInstancia()
{
    if (!instancia)
    {
        instancia = new AudioManager();
    }
    return instancia;
}
//#include <iostream>
bool AudioManager::carregarMusica(const std::string& arquivo)
{
    //std::cout << "maoe";
    return musicaFundo.openFromFile(arquivo);
}

void AudioManager::tocarMusica(bool loop)
{
    musicaFundo.setLoop(loop);
    musicaFundo.play();
}

void AudioManager::pausarMusica() { musicaFundo.pause(); }

void AudioManager::pararMusica() { musicaFundo.stop(); }

void AudioManager::setVolumeMusica(float volume)
{
    musicaFundo.setVolume(volume);
}

bool AudioManager::carregarEfeito(const std::string& nome, const std::string& arquivo) //Efeitos sonoros
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

void AudioManager::tocarEfeito(const std::string& nome)
{
    if (sons.find(nome) != sons.end())
        sons[nome].play();
}

void AudioManager::setVolumeEfeitos(float volume)
{
    for (auto it = sons.begin(); it != sons.end(); ++it) //Iterador clássico para compatibilidade C++11
    {
        it->second.setVolume(volume);
    }
}
