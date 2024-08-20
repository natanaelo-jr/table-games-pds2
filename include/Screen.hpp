#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/Graphics.hpp>
#include "ScreenManager.hpp"
#include <list>
#include "Players.hpp"

class ScreenManager;

/**
 * @class Screen
 * @brief Classe base abstrata para todas as telas do jogo.
 * 
 * A classe Screen define a interface para as diferentes telas do jogo, como a tela de jogo, 
 * menus, etc. Ela gerencia elementos gráficos comuns e oferece métodos para processamento
 * de eventos, atualização e renderização.
 */
class Screen {
    public:
        /**
         * @brief Construtor da classe Screen.
         * 
         * @param players Ponteiro para o objeto que gerencia os jogadores.
         * @param screenManager Ponteiro para o gerenciador de telas.
         */
        Screen(Players* players, ScreenManager* screenManager);

        /**
         * @brief Lida com os eventos da janela, como cliques e movimentação do mouse.
         * 
         * Este método deve ser implementado pelas classes derivadas.
         * 
         * @param window Referência para a janela onde os eventos serão processados.
         */
        virtual void handleEvents(sf::RenderWindow &window) = 0;

        /**
         * @brief Atualiza o estado da tela.
         * 
         * Este método deve ser implementado pelas classes derivadas.
         * 
         * @param window Referência para a janela que será atualizada.
         */
        virtual void update(sf::RenderWindow &window) = 0;

        /**
         * @brief Renderiza os elementos gráficos na tela.
         * 
         * Este método deve ser implementado pelas classes derivadas.
         * 
         * @param window Referência para a janela onde os elementos serão desenhados.
         */
        virtual void render(sf::RenderWindow &window) = 0;

        /**
         * @brief Carrega as texturas necessárias para os elementos gráficos da tela.
         * 
         * Este método deve ser implementado pelas classes derivadas.
         */
        virtual void loadTextures() = 0;

        /**
         * @brief Processa os eventos, atualização e renderização da tela.
         * 
         * @param window Referência para a janela que será processada.
         */
        void process(sf::RenderWindow &window);

        /**
         * @brief Configura a janela com propriedades específicas, como o cursor e ícone.
         * 
         * @param window Referência para a janela que será configurada.
         */
        void setupWindow(sf::RenderWindow &window);

        /**
         * @brief Obtém a cor de fundo da tela.
         * 
         * @return Cor de fundo da tela.
         */
        sf::Color getBackgroundColor();

        /**
         * @brief Verifica se o mouse está sobre uma determinada área na tela.
         * 
         * @param bounds Limites da área a ser verificada.
         * @param window Referência para a janela onde a verificação será feita.
         * @return Verdadeiro se o mouse está sobre a área, falso caso contrário.
         */
        bool isMouseOver(const sf::FloatRect &bounds, const sf::RenderWindow &window);

        /**
         * @brief Obtém o ponteiro para o objeto que gerencia os jogadores.
         * 
         * @return Ponteiro para o objeto Players.
         */
        Players* getPlayers();

        /**
         * @brief Obtém o ponteiro para o gerenciador de telas.
         * 
         * @return Ponteiro para o objeto ScreenManager.
         */
        ScreenManager* getScreenManager();

        sf::Texture backMenuTexture; ///< Textura para o botão de voltar ao menu.
        sf::Texture hoverBackMenuTexture; ///< Textura para o botão de voltar ao menu quando o mouse está sobre ele.
        sf::Texture playAgainTexture; ///< Textura para o botão de jogar novamente.
        sf::Texture hoverPlayAgainTexture; ///< Textura para o botão de jogar novamente quando o mouse está sobre ele.
        sf::Font cardFont; ///< Fonte usada para textos na tela.

    private:
        sf::Color backgroundColor; ///< Cor de fundo da tela.
        sf::Cursor cursor; ///< Cursor usado na janela.
        sf::Image cursorImage; ///< Imagem usada para o cursor.
        sf::Image icon; ///< Ícone da janela.
        Players* players; ///< Ponteiro para o objeto que gerencia os jogadores.
        ScreenManager* screenManager; ///< Ponteiro para o gerenciador de telas.
};

#endif