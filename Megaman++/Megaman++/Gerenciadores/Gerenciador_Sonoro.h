#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>

class Gerenciador_Sonoro
{
private:
	static Gerenciador_Sonoro* instancia;
    sf::Music musicaFundo; //Música de fundo
    std::map<std::string, sf::SoundBuffer> buffers; //Buffers dos efeitos
    std::map<std::string, sf::Sound> sons; //Sons que usam os buffers
    Gerenciador_Sonoro(); //Construtor privado para singleton

public:
    static Gerenciador_Sonoro* getInstancia();
    ~Gerenciador_Sonoro();
    bool carregarMusica(const std::string& arquivo); //Música de fundo
    void tocarMusica(bool loop = true);
    void pausarMusica();
    void pararMusica();
    void setVolumeMusica(float volume);
    bool carregarEfeito(const std::string& nome, const std::string& arquivo); //Efeitos sonoros
    void tocarEfeito(const std::string& nome);
    void setVolumeEfeitos(float volume);
};