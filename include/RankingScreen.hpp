#ifndef RANKINGSCREEN_HPP
#define RANKINGSCREEN_HPP

#include <Players.hpp>
#include "Screen.hpp"

/**
 * @brief Classe responsável pela tela de ranking dos jogadores.
 * 
 * A classe `RankingScreen` exibe a lista de jogadores em ordem de classificação,
 * permitindo navegar entre eles e visualizar suas estatísticas.
 */
class RankingScreen : public Screen {
    public:
        /**
         * @brief Construtor da classe RankingScreen.
         * 
         * @param screenManager Gerenciador de telas responsável por alternar entre as diferentes telas.
         * @param players Ponteiro para a lista de jogadores cadastrados no sistema.
         */
        RankingScreen(ScreenManager* screenManager, Players* players);

        /**
         * @brief Manipula os eventos da tela de ranking.
         * 
         * Processa cliques e outros eventos relacionados à navegação no ranking.
         * 
         * @param window Referência para a janela SFML onde os eventos serão manipulados.
         */
        void handleEvents(sf::RenderWindow &window) override;

        /**
         * @brief Atualiza a lógica da tela de ranking.
         * 
         * Atualiza a tela de ranking com base na interação do usuário e na navegação entre os jogadores.
         * 
         * @param window Referência para a janela SFML onde a atualização ocorrerá.
         */
        void update(sf::RenderWindow &window) override;

        /**
         * @brief Renderiza os elementos visuais da tela de ranking na janela.
         * 
         * @param window Referência para a janela SFML onde os elementos serão renderizados.
         */
        void render(sf::RenderWindow &window) override;

        /**
         * @brief Carrega as texturas necessárias para a tela de ranking.
         * 
         * Carrega imagens e texturas utilizadas pelos botões e cartões dos jogadores.
         */
        void loadTextures() override;

    private:
        unsigned currentPlayer = 0;          /**< Índice do jogador atual exibido no ranking. */

        std::vector<Player*> playersList;    /**< Lista de jogadores exibidos no ranking. */

        sf::Texture playerCardTexture;       /**< Textura do cartão de jogador. */
        sf::Sprite playerCard;               /**< Sprite do cartão de jogador. */

        sf::Texture backButtonTexture;       /**< Textura do botão de voltar. */
        sf::Texture hoverBackButtonTexture;  /**< Textura do botão de voltar em hover. */
        sf::Sprite backButton;               /**< Sprite do botão de voltar. */

        sf::Texture nextButtonTexture;       /**< Textura do botão "Próximo". */
        sf::Sprite nextButton;               /**< Sprite do botão "Próximo". */

        sf::Texture previousButtonTexture;   /**< Textura do botão "Anterior". */
        sf::Sprite previousButton;           /**< Sprite do botão "Anterior". */

        sf::Texture JogadorTexture;          /**< Textura representando o jogador. */
        sf::Sprite Jogador;                  /**< Sprite representando o jogador. */

        sf::Texture versusTexture;           /**< Textura representando o confronto "versus". */
        sf::Sprite versus;                   /**< Sprite representando o confronto "versus". */

        sf::Text name;                       /**< Texto para exibir o nome do jogador. */
        sf::Text nickname;                   /**< Texto para exibir o apelido do jogador. */
        sf::Text position;                   /**< Texto para exibir a posição do jogador no ranking. */

        sf::Text TicTacToeWins;              /**< Texto para exibir vitórias no Jogo da Velha. */
        sf::Text TicTacToeLosses;            /**< Texto para exibir derrotas no Jogo da Velha. */
        sf::Text Lig4Wins;                   /**< Texto para exibir vitórias no Lig4. */
        sf::Text Lig4Losses;                 /**< Texto para exibir derrotas no Lig4. */
        sf::Text MineFieldWins;              /**< Texto para exibir vitórias no Campo Minado. */
        sf::Text MineFieldLosses;            /**< Texto para exibir derrotas no Campo Minado. */
        sf::Text ReversiWins;                /**< Texto para exibir vitórias no Reversi. */
        sf::Text ReversiLosses;              /**< Texto para exibir derrotas no Reversi. */

        sf::Color mainColor;                 /**< Cor principal dos elementos gráficos. */
        sf::Color green;                     /**< Cor verde para textos de vitórias. */
        sf::Color red;                       /**< Cor vermelha para textos de derrotas. */

        sf::Font textFont;                   /**< Fonte utilizada para os textos. */
};

#endif
