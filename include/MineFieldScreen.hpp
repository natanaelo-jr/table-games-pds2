#ifndef MINEFIELDSCREEN_HPP
#define MINEFIELDSCREEN_HPP

#include "Screen.hpp"
#include "MineField.hpp"

/**
 * @class MineFieldScreen
 * @brief Classe responsável por gerenciar a tela do jogo Campo Minado.
 * 
 * Esta classe lida com a renderização, atualização e eventos da tela do jogo Campo Minado,
 * além de gerenciar os recursos gráficos e o jogador.
 */
class MineFieldScreen : public Screen {
    public:
        /**
         * @brief Construtor da classe MineFieldScreen.
         * 
         * @param screenManager Gerenciador de telas que controla a navegação entre as telas.
         * @param player Ponteiro para o jogador.
         * @param players Ponteiro para o objeto que gerencia os jogadores.
         */
        MineFieldScreen(ScreenManager* screenManager, Player* player, Players* players);

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
         * @brief Carrega as texturas necessárias para os elementos gráficos da tela.
         */
        void loadTextures();

        /**
         * @brief Atualiza as peças no tabuleiro.
         */
        void updatePieces();

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

        /**
         * @brief Coloca uma bandeira em um tile específico.
         * 
         * @param coord Coordenadas do tile onde a bandeira será colocada.
         */
        void placeFlag(Coordinates coord);

        /**
         * @brief Remove uma bandeira de um tile específico.
         * 
         * @param coord Coordenadas do tile de onde a bandeira será removida.
         */
        void removeFlag(Coordinates coord);

        /**
         * @brief Verifica se há uma bandeira em um tile específico.
         * 
         * @param coord Coordenadas do tile a ser verificado.
         * @return true se houver uma bandeira no tile, false caso contrário.
         */
        bool isFlagOnTile(Coordinates coord);

    private:
        bool isNewGame; ///< Indica se o jogo é uma nova partida.
        float tileSize; ///< Tamanho de cada tile no tabuleiro.
        MineField* game; ///< Ponteiro para o objeto do jogo Campo Minado.
        sf::Vector2f screenOffset; ///< Offset da tela em relação à posição padrão.
        sf::Texture BombTexture; ///< Textura da bomba.
        sf::Texture BandTexture; ///< Textura da bandeira.
        sf::Texture QuadTexture; ///< Textura do quadrado/tile.
        sf::Texture boardTexture; ///< Textura do tabuleiro.
        sf::Font font; ///< Fonte usada para os textos na tela.
        sf::Font numberFont; ///< Fonte usada para os números no tabuleiro.

        sf::Text playerNick; ///< Texto do nome do jogador.
        sf::Sprite playerPiece; ///< Sprite da peça do jogador.

        std::vector<sf::Sprite> pieces; ///< Vetor de sprites das peças no tabuleiro.
        std::vector<sf::Sprite> flags; ///< Vetor de sprites das bandeiras no tabuleiro.
        std::vector<sf::Text> numbers; ///< Vetor de textos para os números no tabuleiro.
        sf::Sprite board; ///< Sprite do tabuleiro.

        sf::RectangleShape cardShape; ///< Forma retangular usada para um cartão na tela.
        sf::Sprite cardButton1; ///< Sprite do botão 1 do cartão.
        sf::Sprite cardButton2; ///< Sprite do botão 2 do cartão.
        sf::Text cardText; ///< Texto exibido no cartão.

        bool finishGame; ///< Indica se o jogo foi finalizado.
};

#endif