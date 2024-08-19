#ifndef CREDITSSCREEN_HPP
#define CREDITSSCREEN_HPP
#include "Screen.hpp"

/**
 * @brief Classe responsável pela tela de créditos do jogo.
 * 
 * A classe `CreditsScreen` exibe os créditos do jogo e permite que o usuário 
 * retorne à tela anterior.
 */
class CreditsScreen : public Screen {
    public:
        /**
         * @brief Construtor da classe CreditsScreen.
         * 
         * @param screenManager Gerenciador de telas responsável por alternar entre as diferentes telas.
         * @param players Ponteiro para a lista de jogadores cadastrados no sistema.
         */
        CreditsScreen(ScreenManager* screenManager, Players* players);

        /**
         * @brief Renderiza os elementos visuais da tela de créditos.
         * 
         * Exibe os créditos e balões animados.
         * 
         * @param window Referência para a janela SFML onde os elementos serão renderizados.
         */
        void render(sf::RenderWindow &window) override;

        /**
         * @brief Manipula os eventos da tela de créditos.
         * 
         * Processa os cliques do mouse e outros eventos relacionados à tela de créditos.
         * 
         * @param window Referência para a janela SFML onde os eventos serão manipulados.
         */
        void handleEvents(sf::RenderWindow &window) override;

        /**
         * @brief Atualiza a lógica da tela de créditos.
         * 
         * Atualiza a animação dos balões e outros elementos da tela.
         * 
         * @param window Referência para a janela SFML onde a atualização ocorrerá.
         */
        void update(sf::RenderWindow &window) override;

        /**
         * @brief Carrega as texturas necessárias para a tela de créditos.
         * 
         * Carrega as imagens e texturas dos elementos visuais, como os balões e o botão de voltar.
         */
        void loadTextures() override;

        /**
         * @brief Gera os balões animados na tela.
         * 
         * Cria e posiciona os balões que aparecerão durante a exibição dos créditos.
         */
        void generateBaloes();

    private:
        sf::Clock clock;                         /**< Relógio para controlar o tempo das animações. */
        const float frameTime = 1.0f / 60.0f;    /**< Tempo de quadro fixo para controlar a animação. */

        sf::Texture colaboradoresTexture;        /**< Textura para exibir os créditos dos colaboradores. */
        sf::Sprite colaboradoresSprite;          /**< Sprite que exibe os créditos dos colaboradores. */

        sf::Texture backButtonTexture;           /**< Textura do botão de voltar. */
        sf::Texture hoverBackButtonTexture;      /**< Textura do botão de voltar em hover. */
        sf::Sprite backButton;                   /**< Sprite do botão de voltar. */

        sf::Texture balaoTexture;                /**< Textura dos balões animados. */
        std::vector<sf::Sprite> baloes;          /**< Vetor de sprites dos balões animados. */
};

#endif
