#ifndef AI_H
#define AI_H

#include "game.h"

#define MAX_DEPTH 3

int evaluateBoard(GameState *game);
int minimax(GameState *game, int depth, int alpha, int beta, bool maximizingPlayer);
int findBestMove(GameState *game);
int monteCarloEvaluate(GameState *game, int simulations);

#endif
