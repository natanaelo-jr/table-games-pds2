#ifndef LIG4_HPP
#define LIG4_HPP

#include "Game.hpp"

/**
 * @class Lig4
 * @brief Implementa o jogo Lig4, derivado da classe base Game.
 * 
 * A classe Lig4 gerencia a lógica específica do jogo Lig4, incluindo a realização
 * de jogadas, verificação de vencedores e execução de estratégias como o algoritmo Minimax.
 */


class Lig4 : public Game{
    public:
        /**
        * @brief Construtor da classe Lig4.
        * 
        * Inicializa o jogo com dois jogadores.
        * @param player1 Ponteiro para o jogador 1.
        * @param player2 Ponteiro para o jogador 2.
        */
        Lig4(Player* player1, Player* player2);
        /**
        * @brief Inicia o jogo de Lig4.
        * 
        * Implementa a lógica do jogo, sobrepondo o método `play` da classe base.
        */
        virtual void play() override;
        /**
        * @brief Realiza uma jogada na coluna especificada.
        * 
        * @param col Coluna onde a jogada será realizada.
        * @return true se a jogada foi bem-sucedida, false caso contrário.
        */
        bool makePlay(int col);
        /**
        * @brief Verifica se há um vencedor no tabuleiro atual.
        * 
        * @param board Estado atual do tabuleiro.
        * @return Ponteiro para o jogador vencedor ou nullptr se não houver vencedor.
        */

        Player* checkWinner(const BoardType& board);
        /**
        * @brief Adiciona estatísticas ao final da partida.
        * 
        * @param winner Ponteiro para o jogador vencedor.
        * @param loser Ponteiro para o jogador perdedor.
        */

        void addStats(Player* winner, Player* loser);
        /**
        * @brief Verifica se há uma sequência vencedora no tabuleiro.
        * 
        * @param board Estado atual do tabuleiro.
        * @return true se uma sequência vencedora foi encontrada, false caso contrário.
        */
        bool verifySequence(const BoardType& board);
        /**
        * @brief Verifica uma sequência na direção direita.
        * 
        * @param c Coordenadas da posição atual.
        * @param board Estado atual do tabuleiro.
        * @param counter Contador de peças consecutivas.
        * @return true se uma sequência foi completada, false caso contrário.
        */
        bool verifyRight(Coordinates c, const BoardType& board, int counter);
        /**
        * @brief Verifica uma sequência na direção para baixo.
        * 
        * @param c Coordenadas da posição atual.
        * @param board Estado atual do tabuleiro.
        * @param counter Contador de peças consecutivas.
        * @return true se uma sequência foi completada, false caso contrário.
        */
        bool verifyDown(Coordinates c, const BoardType& board, int counter);
        /**
        * @brief Verifica uma sequência na diagonal inferior direita.
        * 
        * @param c Coordenadas da posição atual.
        * @param board Estado atual do tabuleiro.
        * @param counter Contador de peças consecutivas.
        * @return true se uma sequência foi completada, false caso contrário.
        */
        bool verifyDownRight(Coordinates c, const BoardType& board, int counter);
        /**
        * @brief Verifica uma sequência na diagonal superior direita.
        * 
        * @param c Coordenadas da posição atual.
        * @param board Estado atual do tabuleiro.
        * @param counter Contador de peças consecutivas.
        * @return true se uma sequência foi completada, false caso contrário.
        */
        bool verifyUpRight(Coordinates c, const BoardType& board, int counter);
        /**
        * @brief Retorna as jogadas possíveis no estado atual do tabuleiro.
        * 
        * @param board Estado atual do tabuleiro.
        * @return Vetor de inteiros representando as colunas onde é possível jogar.
        */
        virtual std::vector<int> possiblePlays(const BoardType& board);
        /**
        * @brief Verifica se o estado atual do tabuleiro é terminal.
         * 
        * @param board Estado atual do tabuleiro.
        * @return true se o estado é terminal (vitória ou empate), false caso contrário.
        */
        bool terminalState(const BoardType &board);
        /**
        * @brief Determina de quem é a vez de jogar.
        * 
        * @param board Estado atual do tabuleiro.
        * @return Inteiro representando o jogador cuja vez é de jogar.
        */
        int whoseTurn(const BoardType& board);
        /**
        * @brief Aplica uma jogada e retorna o novo estado do tabuleiro.
        * 
        * @param board Estado atual do tabuleiro.
        * @param play Coluna onde a jogada será realizada.
        * @return O novo estado do tabuleiro após a jogada.
        */
        BoardType result(const BoardType& board, int play);
        /**
        * @brief Implementa o algoritmo Minimax para escolher a melhor jogada.
        *   
        * @param board Estado atual do tabuleiro.
        * @param alpha Valor alfa para poda alfa-beta.
        * @param beta Valor beta para poda alfa-beta.
        * @param maximizing Booleano indicando se o algoritmo deve maximizar ou minimizar.
        * @param depth Profundidade máxima da árvore de busca.
        * @return O valor da jogada calculado pelo algoritmo Minimax.
        */
        int minimax(const BoardType& board, int alpha, int beta, bool maximizing, int depth);
        /**
        * @brief Retorna a melhor jogada calculada pelo algoritmo Minimax.
        * 
        * @param board Estado atual do tabuleiro.
        * @return Inteiro representando a coluna onde deve ser feita a melhor jogada.
        */
        int bestPlay(const BoardType& board);
};

#endif //LIG4_HPP