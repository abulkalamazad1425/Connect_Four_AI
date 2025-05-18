#include "ai.h"
#include <stdlib.h>


int getValidMoves(GameState *game, int moves[]) {
    int count = 0;
    for (int col = 0; col < COLS; col++) {
        if (isValidMove(game, col)) {
            moves[count++] = col;
        }
    }
    return count;
}


int simulateRandomGame(GameState *game) {
    GameState temp = *game;
    while (!checkWin(&temp, AI) && !checkWin(&temp, PLAYER) && !checkDraw(&temp)) {
        int moves[COLS];
        int count = getValidMoves(&temp, moves);
        if (count == 0) break;

        int col = moves[rand() % count];
        makeMove(&temp, col);
        temp.currentPlayer = (temp.currentPlayer == AI) ? PLAYER : AI;
    }

    if (checkWin(&temp, AI)) return AI;
    if (checkWin(&temp, PLAYER)) return PLAYER;
    return 0; // Draw
}


int monteCarloEvaluate(GameState *game, int simulations) {
    int aiWins = 0, playerWins = 0, draws = 0;

    for (int i = 0; i < simulations; i++) {
        int result = simulateRandomGame(game);
        if (result == AI) aiWins++;
        else if (result == PLAYER) playerWins++;
        else draws++;
    }

    return (aiWins * 100) - (playerWins * 100); // weighted score
}
