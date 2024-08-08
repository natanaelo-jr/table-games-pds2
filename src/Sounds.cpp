#include "Sounds.hpp"
#include <iostream>

void Sounds::soundBark() {

    buffer.loadFromFile("sounds/bark.wav");
    if(!buffer.loadFromFile("sounds/bark.wav"))
    {
        std::cout << "ERRO AO CARREGAR SOM" << std::endl;
    }
    sound.setBuffer(buffer);
    sound.play();
    while (sound.getStatus() == sf::Sound::Playing)
    {
    }
}

void Sounds::play() {

    buffer.loadFromFile("sounds/hino.wav");
    if(!buffer.loadFromFile("sounds/hino.wav"))
    {
        std::cout << "ERRO AO CARREGAR SOM" << std::endl;
    }
    sound.setBuffer(buffer);
    sound.play();
    while (sound.getStatus() == sf::Sound::Playing)
    {
    }
}

void Sounds::soundExplosion() {

    buffer.loadFromFile("sounds/explosion.wav");
    if(!buffer.loadFromFile("sounds/explosion.wav"))
    {
        std::cout << "ERRO AO CARREGAR SOM" << std::endl;
    }
    sound.setBuffer(buffer);
    sound.play();
    while (sound.getStatus() == sf::Sound::Playing)
    {
    }
}

void Sounds::soundClick() {

    buffer.loadFromFile("sounds/click.wav");
    if(!buffer.loadFromFile("sounds/click.wav"))
    {
        std::cout << "ERRO AO CARREGAR SOM" << std::endl;
    }
    sound.setBuffer(buffer);
    sound.play();
    while (sound.getStatus() == sf::Sound::Playing)
    {
    }
}

void Sounds::soundLost() {

    buffer.loadFromFile("sounds/lost.wav");
    if(!buffer.loadFromFile("sounds/lost.wav"))
    {
        std::cout << "ERRO AO CARREGAR SOM" << std::endl;
    }
    sound.setBuffer(buffer);
    sound.play();
    while (sound.getStatus() == sf::Sound::Playing)
    {
    }
}
