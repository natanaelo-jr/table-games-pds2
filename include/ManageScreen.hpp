#ifndef MANAGESCREEN_HPP
#define MANAGESCREEN_HPP
#include "Screen.hpp"

/**
 * @brief Classe responsável pela tela de gerenciamento de jogadores.
 * 
 * A classe `ManageScreen` permite ao usuário adicionar e remover jogadores, 
 * bem como manipular seus dados, como apelido e nome.
 */
class ManageScreen : public Screen {
    public: 
        /**
         * @brief Construtor da classe ManageScreen.
         * 
         * @param screenManager Gerenciador de telas responsável por alternar entre as diferentes telas.
         * @param players Ponteiro para a lista de jogadores cadastrados no sistema.
         */
        ManageScreen(ScreenManager* screenManager, Players* players);

        /**
         * @brief Manipula os eventos da tela de gerenciamento.
         * 
         * Processa cliques do mouse e outros eventos da janela.
         * 
         * @param window Referência para a janela SFML onde os eventos serão manipulados.
         */
        void handleEvents(sf::RenderWindow &window) override;

        /**
         * @brief Atualiza a lógica da tela de gerenciamento.
         * 
         * Atualiza a interface da tela de gerenciamento com base nas interações do usuário.
         * 
         * @param window Referência para a janela SFML onde a atualização ocorrerá.
         */
        void update(sf::RenderWindow &window) override;

        /**
         * @brief Renderiza os elementos visuais da tela de gerenciamento na janela.
         * 
         * @param window Referência para a janela SFML onde os elementos serão renderizados.
         */
        void render(sf::RenderWindow &window) override;

        /**
         * @brief Manipula a entrada de texto dos jogadores.
         * 
         * Processa a entrada de texto quando o jogador insere ou edita seu nome ou apelido.
         * 
         * @param event Evento SFML de texto.
         */
        void handleTextInput(sf::Event &event);

        /**
         * @brief Carrega as texturas necessárias para a tela de gerenciamento.
         * 
         * Carrega imagens e texturas utilizadas pelos botões e campos de texto.
         */
        void loadTextures() override;

        /**
         * @brief Valida o apelido do jogador.
         * 
         * Verifica se o apelido inserido pelo jogador é válido.
         * 
         * @return true se o apelido for válido, false caso contrário.
         */
        bool validateNickname();

        /**
         * @brief Valida o nome do jogador.
         * 
         * Verifica se o nome inserido pelo jogador é válido.
         * 
         * @return true se o nome for válido, false caso contrário.
         */
        bool validateName();

        /**
         * @brief Configura as strings de texto para exibição.
         * 
         * Inicializa as strings de texto exibidas na tela de gerenciamento, como títulos e campos de entrada.
         */
        void setupStrings();

        /**
         * @brief Atualiza o conteúdo dos textos na tela de gerenciamento.
         * 
         * Atualiza os textos mostrados com base nas mudanças feitas pelo usuário.
         */
        void updateTexts();

    private:
        sf::RectangleShape nicknameCase;     /**< Campo retangular para inserção do apelido. */
        sf::RectangleShape nameCase;         /**< Campo retangular para inserção do nome. */
        sf::Text nicknameTitle;              /**< Título para o campo de apelido. */
        sf::Text nicknameString;             /**< String de entrada do apelido. */
        sf::Text nameTitle;                  /**< Título para o campo de nome. */
        sf::Text nameString;                 /**< String de entrada do nome. */
        bool isNickCaseSelected;             /**< Indica se o campo de apelido está selecionado. */
        bool isNameCaseSelected;             /**< Indica se o campo de nome está selecionado. */
        bool currentPlayerExists;            /**< Verifica se o jogador atual existe. */

        sf::Texture addButtonTexture;        /**< Textura do botão de adicionar jogador. */
        sf::Texture hoverAddButtonTexture;   /**< Textura do botão de adicionar em hover. */
        sf::Texture removeButtonTexture;     /**< Textura do botão de remover jogador. */
        sf::Texture hoverRemoveButtonTexture;/**< Textura do botão de remover em hover. */

        sf::Sprite pushDataButton;           /**< Botão para confirmar os dados inseridos. */

        sf::Texture backButtonTexture;       /**< Textura do botão de voltar. */
        sf::Texture hoverBackButtonTexture;  /**< Textura do botão de voltar em hover. */
        sf::Sprite backButton;               /**< Sprite do botão de voltar. */
        sf::Font textFont;                   /**< Fonte utilizada para os textos. */
        sf::Color textColor;                 /**< Cor utilizada para os textos. */
};

#endif
