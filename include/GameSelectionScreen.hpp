#ifndef SELECTIONSCREEN_HPP
#define SELECTIONSCREEN_HPP
#include "Screen.hpp"

/**
 * @brief Classe responsável pela tela de seleção de jogos.
 * 
 * A classe `GameSelectionScreen` permite ao usuário escolher um jogo para jogar 
 * e selecionar os jogadores participantes.
 */
class GameSelectionScreen : public Screen {

    public:
        /**
         * @brief Construtor da classe GameSelectionScreen.
         * 
         * @param screenManager Gerenciador de telas responsável por alternar entre as diferentes telas.
         * @param players Ponteiro para a lista de jogadores cadastrados no sistema.
         */
        GameSelectionScreen(ScreenManager* screenManager, Players* players);

        /**
         * @brief Manipula os eventos da tela de seleção de jogos.
         * 
         * Processa cliques e outros eventos relacionados à seleção de jogos e jogadores.
         * 
         * @param window Referência para a janela SFML onde os eventos serão manipulados.
         */
        void handleEvents(sf::RenderWindow &window) override;

        /**
         * @brief Atualiza a lógica da tela de seleção de jogos.
         * 
         * Atualiza as seleções dos jogos e dos jogadores com base nas interações do usuário.
         * 
         * @param window Referência para a janela SFML onde a atualização ocorrerá.
         */
        void update(sf::RenderWindow &window) override;

        /**
         * @brief Renderiza os elementos visuais da tela de seleção de jogos.
         * 
         * Exibe os botões de seleção de jogos, jogadores e outros elementos gráficos.
         * 
         * @param window Referência para a janela SFML onde os elementos serão renderizados.
         */
        void render(sf::RenderWindow &window) override;

        /**
         * @brief Carrega as texturas necessárias para a tela de seleção de jogos.
         * 
         * Carrega as imagens e texturas utilizadas pelos botões e demais elementos da tela.
         */
        void loadTextures() override;

        /**
         * @brief Atualiza o jogo selecionado com base nas interações do usuário.
         * 
         * Altera o jogo selecionado entre as opções disponíveis (Jogo da Velha, Lig4, etc.).
         */
        void updateSelectedGame();

        /**
         * @brief Atualiza os textos exibidos na tela.
         * 
         * Atualiza as informações sobre o jogo selecionado e os jogadores exibidos na tela.
         */
        void updateTexts();

    private:
        std::string SelectedGame;                /**< Nome do jogo selecionado pelo usuário. */
        std::vector<Player*> playerList;         /**< Lista de jogadores disponíveis para seleção. */
        unsigned player1Index;                   /**< Índice do primeiro jogador selecionado. */
        unsigned player2Index;                   /**< Índice do segundo jogador selecionado. */

        sf::Texture startButtonTexture;          /**< Textura do botão de iniciar jogo. */
        sf::Texture hoverStartButtonTexture;     /**< Textura do botão de iniciar jogo em hover. */
        sf::Sprite startButton;                  /**< Sprite do botão de iniciar jogo. */

        sf::Texture backButtonTexture;           /**< Textura do botão de voltar. */
        sf::Texture hoverBackButtonTexture;      /**< Textura do botão de voltar em hover. */
        sf::Sprite backButton;                   /**< Sprite do botão de voltar. */

        sf::Texture ticTacToeButtonTexture;      /**< Textura do botão de seleção do Jogo da Velha. */
        sf::Texture selectedTicTacToeButtonTexture; /**< Textura do botão do Jogo da Velha quando selecionado. */
        sf::Sprite ticTacToeButton;              /**< Sprite do botão de seleção do Jogo da Velha. */

        sf::Texture lig4ButtonTexture;           /**< Textura do botão de seleção do Lig4. */
        sf::Texture selectedLig4ButtonTexture;   /**< Textura do botão do Lig4 quando selecionado. */
        sf::Sprite lig4Button;                   /**< Sprite do botão de seleção do Lig4. */

        sf::Texture mineFieldButtonTexture;      /**< Textura do botão de seleção do Campo Minado. */
        sf::Texture selectedMineFieldButtonTexture; /**< Textura do botão do Campo Minado quando selecionado. */
        sf::Sprite mineFieldButton;              /**< Sprite do botão de seleção do Campo Minado. */

        sf::Texture reversiButtonTexture;        /**< Textura do botão de seleção do Reversi. */
        sf::Texture selectedReversiButtonTexture;/**< Textura do botão do Reversi quando selecionado. */
        sf::Sprite reversiButton;                /**< Sprite do botão de seleção do Reversi. */

        sf::Text selectedGame;                   /**< Texto exibindo o jogo atualmente selecionado. */
        sf::Text player1;                        /**< Texto exibindo o primeiro jogador selecionado. */
        sf::Text player2;                        /**< Texto exibindo o segundo jogador selecionado. */
        sf::Vector2f selectedGamePosition;       /**< Posição do texto do jogo selecionado. */
        sf::Vector2f player1Position;            /**< Posição do texto do primeiro jogador. */
        sf::Vector2f player2Position;            /**< Posição do texto do segundo jogador. */

        sf::Font textFont;                       /**< Fonte utilizada para os textos. */
        sf::Color mainColor;                     /**< Cor principal dos textos e elementos gráficos. */

        sf::Texture nextPlayerTexture;           /**< Textura do botão "Próximo jogador". */
        sf::Texture previousPlayerTexture;       /**< Textura do botão "Jogador anterior". */
        sf::Sprite nextPlayer1;                  /**< Sprite do botão "Próximo jogador 1". */
        sf::Sprite previousPlayer1;              /**< Sprite do botão "Jogador anterior 1". */
        sf::Sprite nextPlayer2;                  /**< Sprite do botão "Próximo jogador 2". */
        sf::Sprite previousPlayer2;              /**< Sprite do botão "Jogador anterior 2". */

        sf::Texture versusTexture;               /**< Textura do elemento "versus" entre os dois jogadores. */
        sf::Sprite versus;                       /**< Sprite do elemento "versus". */
};

#endif
