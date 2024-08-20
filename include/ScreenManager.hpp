#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include <stack>
#include <memory>
#include "Screen.hpp"

class Screen;

/**
 * @class ScreenManager
 * @brief Classe responsável por gerenciar as diferentes telas (estados) do jogo.
 * 
 * A classe ScreenManager gerencia uma pilha de telas (estados) e permite transições
 * entre elas, como adicionar, remover ou substituir telas ativamente.
 */
class ScreenManager {
    public:
        /**
         * @brief Adiciona uma nova tela no topo da pilha de estados.
         * 
         * @param state Ponteiro compartilhado para a nova tela a ser adicionada.
         */
        void push(std::shared_ptr<Screen> state);

        /**
         * @brief Remove a tela do topo da pilha de estados.
         */
        void pop();

        /**
         * @brief Substitui a tela do topo da pilha por uma nova tela.
         * 
         * @param state Ponteiro compartilhado para a nova tela a ser definida no topo da pilha.
         */
        void change(std::shared_ptr<Screen> state);

        /**
         * @brief Obtém a tela atual (topo da pilha).
         * 
         * @return Ponteiro compartilhado para a tela atual.
         */
        std::shared_ptr<Screen> getCurrentState();

        /**
         * @brief Processa os eventos, atualização e renderização da tela atual.
         * 
         * @param window Referência para a janela que será processada.
         */
        void process(sf::RenderWindow &window);

        /**
         * @brief Configura a janela com propriedades específicas baseadas na tela atual.
         * 
         * @param window Referência para a janela que será configurada.
         */
        void setupWindow(sf::RenderWindow &window);

    private:
        std::stack<std::shared_ptr<Screen>> states; ///< Pilha de telas (estados) gerenciadas.
};

#endif // SCREENMANAGER_HPP