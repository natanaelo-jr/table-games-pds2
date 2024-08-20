#ifndef MINEFIELD_HPP
#define MINEFIELD_HPP

#include "Game.hpp"

/**
 * @class MineField
 * @brief Classe que representa o jogo Campo Minado.
 * 
 * A classe MineField gerencia a lógica do jogo Campo Minado, incluindo o estado do campo,
 * as jogadas, e o controle dos jogadores.
 */
class MineField : public Game {
    private:
        std::vector<std::vector<int>> referenceField; ///< Campo de referência contendo a distribuição de bombas.
        int fieldSize; ///< Tamanho do campo de jogo.
        int numberOfBombs; ///< Número de bombas no campo.
        bool versusGame; ///< Indica se o jogo é no modo versus (dois jogadores).

    public:
        /**
         * @brief Construtor para um único jogador com configuração padrão.
         * 
         * @param player Ponteiro para o jogador.
         */
        MineField(Player* player);

        /**
         * @brief Construtor para um único jogador com configuração personalizada.
         * 
         * @param player Ponteiro para o jogador.
         * @param fieldSize Tamanho do campo de jogo.
         * @param bombs Número de bombas no campo.
         */
        MineField(Player* player, int fieldSize, int bombs);

        /**
         * @brief Construtor para o modo versus com dois jogadores e configuração padrão.
         * 
         * @param player1 Ponteiro para o primeiro jogador.
         * @param player2 Ponteiro para o segundo jogador.
         */
        MineField(Player* player1, Player* player2);

        /**
         * @brief Construtor para o modo versus com dois jogadores e configuração personalizada.
         * 
         * @param player1 Ponteiro para o primeiro jogador.
         * @param player2 Ponteiro para o segundo jogador.
         * @param fieldSize Tamanho do campo de jogo.
         * @param bombs Número de bombas no campo.
         */
        MineField(Player* player1, Player* player2, int fieldSize, int bombs);

        /**
         * @brief Obtém o tamanho do campo de jogo.
         * 
         * @return Tamanho do campo.
         */
        int getFieldSize();

        /**
         * @brief Obtém o valor de referência para uma coordenada específica no campo.
         * 
         * @param reference Coordenada no campo.
         * @return Valor de referência na coordenada especificada.
         */
        int getReference(Coordinates reference);

        /**
         * @brief Obtém o número de bombas no campo.
         * 
         * @return Número de bombas.
         */
        int getNumberOfBombs();

        /**
         * @brief Executa a jogada do jogador.
         */
        virtual void play() override;

        /**
         * @brief Realiza uma jogada no campo de jogo.
         * 
         * @param move Coordenada da jogada.
         * @return Verdadeiro se a jogada foi bem-sucedida, falso se acertou uma bomba.
         */
        bool makePlay(Coordinates move);

        /**
         * @brief Revela todo o campo de jogo.
         */
        void revealBoard();

        /**
         * @brief Define o campo de referência após a primeira jogada.
         * 
         * @param firstPlay Coordenada da primeira jogada.
         */
        void setReferenceField(Coordinates firstPlay);

        /**
         * @brief Abre recursivamente as células ao redor de uma coordenada segura.
         * 
         * @param reference Coordenada inicial para a abertura recursiva.
         */
        void recursiveOpen(Coordinates reference);

        /**
         * @brief Obtém as jogadas possíveis no campo de jogo.
         * 
         * @return Vetor de coordenadas das jogadas possíveis.
         */
        std::vector<Coordinates> getPossiblePlays();

        /**
         * @brief Verifica se o jogo está no modo versus.
         * 
         * @return Verdadeiro se o jogo é no modo versus, falso caso contrário.
         */
        bool isVersusGame();

        /**
         * @brief Verifica se o jogo terminou.
         * 
         * @return Verdadeiro se o jogo acabou, falso caso contrário.
         */
        bool isGameOver();

        /**
         * @brief Reinicia o jogo para uma nova partida.
         */
        void resetGame();

        /**
         * @brief Adiciona as estatísticas do jogo aos jogadores.
         * 
         * @param player Ponteiro para o jogador vencedor.
         * @param loser Ponteiro para o jogador perdedor (em modo versus).
         */
        void addStats(Player* player, Player* loser) override;
};

#endif // MINEFIELD_HPP
