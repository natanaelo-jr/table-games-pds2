#ifndef TICTACTOESCREEN_HPP
#define TICTACTOESCREEN_HPP

#include "Screen.hpp"
#include "TicTacToe.hpp"

/**
 * @class TicTacToeScreen
 * @brief Classe responsável por gerenciar a tela do jogo Tic-Tac-Toe.
 * 
 * Esta classe lida com a renderização, atualização e eventos da tela do jogo Tic-Tac-Toe,
 * além de gerenciar os recursos gráficos e os jogadores.
 */
class TicTacToeScreen : public Screen {
    public:
        /**
         * @brief Construtor da classe TicTacToeScreen.
         * 
         * @param screenManager Gerenciador de telas que controla a navegação entre as telas.
         * @param player1 Ponteiro para o primeiro jogador.
         * @param player2 Ponteiro para o segundo jogador.
         * @param players Ponteiro para o objeto que gerencia os jogadores.
         */
        TicTacToeScreen(ScreenManager* screenManager, Player* player1, Player* player2, Players* players);

        /**
         * @brief Lida com os eventos da janela, como cliques e movimentação do mouse.
         * 
         * @param window Referência para a janela onde os eventos serão processados.
         */
        void handleEvents(sf::RenderWindow &window) override;

        /**
         * @brief Atualiza o estado da tela do jogo.
         * 
         * @param window Referência para a janela que será atualizada.
         */
        void update(sf::RenderWindow &window) override;

        /**
         * @brief Renderiza os elementos gráficos na tela.
         * 
         * @param window Referência para a janela onde os elementos serão desenhados.
         */
        void render(sf::RenderWindow &window) override;

        /**
         * @brief Atualiza a posição e o estado da peça fantasma.
         * 
         * @param window Referência para a janela onde a peça fantasma será atualizada.
         */
        void updatePhantomPiece(sf::RenderWindow &window);

        /**
         * @brief Carrega as texturas necessárias para os elementos gráficos da tela.
         */
        void loadTextures();

        /**
         * @brief Obtém as coordenadas de um tile a partir de seu retângulo delimitador.
         * 
         * @param tile Referência para o retângulo delimitador do tile.
         * @return Coordenadas do tile.
         */
        Coordinates getTileCoordinates(sf::FloatRect &tile);

        /**
         * @brief Obtém as jogadas possíveis na tela.
         * 
         * @return Vetor de retângulos delimitadores das jogadas possíveis.
         */
        std::vector<sf::FloatRect> getPossiblePlays();

        /**
         * @brief Processa uma jogada na tela.
         * 
         * @param playTile Referência para o retângulo delimitador da jogada que será processada.
         */
        void processPlay(sf::FloatRect &playTile);

    private:
        float tileSize; ///< Tamanho de cada tile no tabuleiro.
        TicTacToe* game; ///< Ponteiro para o objeto do jogo Tic-Tac-Toe.
        sf::Vector2f screenOffset; ///< Offset da tela em relação à posição padrão.
        sf::Texture pieceOTexture; ///< Textura da peça O.
        sf::Texture pieceXTexture; ///< Textura da peça X.
        sf::Texture boardTexture; ///< Textura do tabuleiro.
        sf::Sprite phantomPiece; ///< Sprite da peça fantasma.
        sf::Font font; ///< Fonte usada para os textos na tela.

        sf::Text player1Nick; ///< Texto do nome do jogador 1.
        sf::Text player2Nick; ///< Texto do nome do jogador 2.
        sf::Sprite player1Piece; ///< Sprite da peça do jogador 1.
        sf::Sprite player2Piece; ///< Sprite da peça do jogador 2.

        std::vector<sf::Sprite> pieces; ///< Vetor de sprites das peças no tabuleiro.
        sf::Sprite board; ///< Sprite do tabuleiro.

        sf::RectangleShape cardShape; ///< Forma retangular usada para um cartão na tela.
        sf::Sprite cardButton1; ///< Sprite do botão 1 do cartão.
        sf::Sprite cardButton2; ///< Sprite do botão 2 do cartão.
        sf::Text cardText; ///< Texto exibido no cartão.

        bool finishGame; ///< Indica se o jogo foi finalizado.
};

#endif