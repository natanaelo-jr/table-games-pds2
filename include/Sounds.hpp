#ifndef SOUNDS_HPP
#define SOUNDS_HPP

#include <SFML/Audio.hpp>

class Sounds {
public: 
    void soundBark();
    void play();
    void soundExplosion();
    void soundClick();
    void soundLost();

private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
    
};

#endif
