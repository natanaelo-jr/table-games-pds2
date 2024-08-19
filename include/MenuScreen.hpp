#ifndef MENU_HPP
#define MENU_HPP
#include "Screen.hpp"

/**
 * @brief Classe responsável por representar a tela de menu principal.
 * 
 * A classe `MenuScreen` herda da classe `Screen` e implementa as funções necessárias
 * para manipular os eventos, atualizar e renderizar a tela de menu principal do jogo.
 */
class MenuScreen : public Screen {
    public:
        /**
         * @brief Construtor da classe MenuScreen.
         * 
         * @param screenManager Gerenciador de telas responsável por alternar entre as diferentes telas.
         * @param players Ponteiro para a lista de jogadores cadastrados no sistema.
         */
        MenuScreen(ScreenManager* screenManager, Players* players);

        /**
         * @brief Manipula os eventos do menu.
         * 
         * Este método é chamado para processar os eventos ocorridos na janela, como cliques
         * ou movimentação do mouse sobre os botões.
         * 
         * @param window Referência para a janela SFML onde os eventos serão manipulados.
         */
        void handleEvents(sf::RenderWindow &window) override;

        /**
         * @brief Atualiza a lógica do menu.
         * 
         * Este método é chamado para atualizar o estado do menu (por exemplo, mudar o
         * estado dos botões com base na interação do usuário).
         * 
         * @param window Referência para a janela SFML onde a atualização ocorrerá.
         */
        void update(sf::RenderWindow &window) override;

        /**
         * @brief Renderiza os elementos visuais do menu na janela.
         * 
         * Este método desenha os botões e outros elementos gráficos do menu na janela.
         * 
         * @param window Referência para a janela SFML onde os elementos serão renderizados.
         */
        void render(sf::RenderWindow &window) override;

        /**
         * @brief Carrega as texturas dos botões do menu.
         * 
         * Este método carrega as texturas utilizadas pelos botões do menu (normal e hover),
         * para que possam ser renderizadas corretamente na tela.
         */
        void loadTextures();

    private:
        sf::Texture playButtonTexture;           /**< Textura do botão "Jogar". */
        sf::Texture hoverPlayButtonTexture;      /**< Textura do botão "Jogar" quando em hover. */
        sf::Texture manageButtonTexture;         /**< Textura do botão "Gerenciar". */
        sf::Texture hoverManageButtonTexture;    /**< Textura do botão "Gerenciar" quando em hover. */
        sf::Texture rankingButtonTexture;        /**< Textura do botão "Ranking". */
        sf::Texture hoverRankingButtonTexture;   /**< Textura do botão "Ranking" quando em hover. */
        sf::Texture creditsButtonTexture;        /**< Textura do botão "Créditos". */
        sf::Texture hoverCreditsButtonTexture;   /**< Textura do botão "Créditos" quando em hover. */
        sf::Texture exitButtonTexture;           /**< Textura do botão "Sair". */
        sf::Texture hoverExitButtonTexture;      /**< Textura do botão "Sair" quando em hover. */

        sf::Sprite playButton;      /**< Sprite do botão "Jogar". */
        sf::Sprite rankingButton;   /**< Sprite do botão "Ranking". */
        sf::Sprite creditsButton;   /**< Sprite do botão "Créditos". */
        sf::Sprite manageButton;    /**< Sprite do botão "Gerenciar". */
        sf::Sprite exitButton;      /**< Sprite do botão "Sair". */
};

#endif
