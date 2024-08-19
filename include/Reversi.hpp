#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "Game.hpp"
#include "Coordinates.hpp"

/**
 * @class Reversi
 * @brief Implementa o jogo Reversi, derivado da classe base Game.
 * 
 * A classe Reversi gerencia as regras e a lógica específicas do jogo Reversi, como
 * a manipulação de peças, verificação de jogadas válidas e contagem de símbolos.
 */
class Reversi : public Game {
    public:
        /**
        * @brief Construtor da classe Reversi.
        * 
        * Inicializa o jogo com dois jogadores.
        * @param player1 Ponteiro para o jogador 1.
        * @param player2 Ponteiro para o jogador 2.
        */
    Reversi(Player* player1, Player* player2);

        /**
        * @brief Inicia o jogo de Reversi.
        * 
        * Implementa a lógica do jogo, sobrepondo o método `play` da classe base.
        */
        virtual void play() override;

        /**
        * @brief Realiza uma jogada nas coordenadas especificadas.
        * 
        * @param row Linha onde a jogada será realizada.
        * @param col Coluna onde a jogada será realizada.
        * @return true se a jogada foi bem-sucedida, false caso contrário.
        */
        bool makePlay(int row, int col);

        /**
        * @brief Verifica se há um vencedor ao final do jogo.
        * 
        * @return Ponteiro para o jogador vencedor ou nullptr em caso de empate.
        */
        Player* checkWinner();

        /**
        * @brief Adiciona estatísticas ao final da partida.
        * 
        * @param winner Ponteiro para o jogador vencedor.
        * @param loser Ponteiro para o jogador perdedor.
        */
        void addStats(Player* winner, Player* loser);

        /**
        * @brief Conta o número de peças de um determinado símbolo no tabuleiro.
        * 
        * @param symbol Símbolo cuja contagem será realizada.
        * @return O número de peças do símbolo fornecido no tabuleiro.
        */
        int countSymbols(char symbol);

        /**
        * @brief Reverte as peças de acordo com as regras do jogo Reversi após uma jogada.
        * 
        * @param row Linha da jogada.
        * @param col Coluna da jogada.
        */
        void reverseSymbols(int row, int col);

        /**
        * @brief Inicializa o tabuleiro com a configuração inicial do jogo Reversi.
        */
        void initializeBoard();

        /**
        * @brief Busca uma jogada válida a partir de uma coordenada específica e em uma direção dada.
        * 
        * @param row Linha inicial da busca.
        * @param col Coluna inicial da busca.
        * @param dRow Incremento para a direção da linha.
        * @param dCol Incremento para a direção da coluna.
        * @param symbol Símbolo do jogador atual.
        * @param opposite Símbolo do jogador adversário.
        * @param passedOpponent Indica se uma peça do adversário foi encontrada na busca.
        * @param board Estado atual do tabuleiro.
        * @return Coordenadas da jogada válida encontrada ou (-1, -1) se nenhuma jogada válida foi encontrada.
        */
        Coordinates searcherForPlay(int row, int col, int dRow, int dCol, char symbol, char opposite, bool passedOpponent, const BoardType &board);

        /**
        * @brief Obtém uma lista de todas as jogadas possíveis para um símbolo específico no tabuleiro.
        * 
        * @param symbol Símbolo do jogador atual.
        * @param board Estado atual do tabuleiro.
        * @return Vetor de coordenadas representando as jogadas possíveis.
        */
        std::vector<Coordinates> getPossiblePlays(char symbol, const BoardType& board);

        /**
        * @brief Verifica se uma jogada em uma posição específica é válida.
        * 
        * @param row Linha da jogada.
        * @param col Coluna da jogada.
        * @param symbol Símbolo do jogador atual.
        * @return true se a jogada é válida, false caso contrário.
        */
        bool verifyPlay(int row, int col, char symbol);

        /**
        * @brief Realiza a inversão de peças a partir de uma jogada em uma direção específica.
        * 
        * @param row Linha inicial da jogada.
        * @param dRow Incremento para a direção da linha.
        * @param col Coluna inicial da jogada.
        * @param dCol Incremento para a direção da coluna.
        * @param symbol Símbolo do jogador atual.
        * @param isOriginalTile Indica se a célula atual é a célula original da jogada.
        * @param board Estado atual do tabuleiro.
        * @return true se as peças foram invertidas, false caso contrário.
        */
        bool turnPieces(int row, int dRow, int col, int dCol, char symbol, bool isOriginalTile, const BoardType &board);

        /**
        * @brief Verifica se o jogo chegou a um estado terminal (sem jogadas possíveis).
        * 
        * @param board Estado atual do tabuleiro.
        * @return true se o jogo está em estado terminal, false caso contrário.
        */
        bool terminalState(const BoardType& board);
};

#endif // REVERSI_HPP
