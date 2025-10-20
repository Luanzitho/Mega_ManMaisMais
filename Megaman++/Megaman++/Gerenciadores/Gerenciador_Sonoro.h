#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>

class AudioManager
{
private:
	static AudioManager* instancia;
    sf::Music musicaFundo; //Música de fundo
    std::map<std::string, sf::SoundBuffer> buffers; //Buffers dos efeitos
    std::map<std::string, sf::Sound> sons; //Sons que usam os buffers
    AudioManager(); //Construtor privado para singleton

public:
    static AudioManager* getInstancia();
    bool carregarMusica(const std::string& arquivo); //Música de fundo
    void tocarMusica(bool loop = true);
    void pausarMusica();
    void pararMusica();
    void setVolumeMusica(float volume);
    bool carregarEfeito(const std::string& nome, const std::string& arquivo); //Efeitos sonoros
    void tocarEfeito(const std::string& nome);
    void setVolumeEfeitos(float volume);
};