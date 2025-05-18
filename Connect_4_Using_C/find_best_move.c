#include "ai.h"
#include <limits.h>


int minimax(GameState *game, int depth, int alpha, int beta, bool maximizingPlayer) {
    
    if (checkWin(game, AI)) {
        return 1000 + depth;
    }
    if (checkWin(game, PLAYER)) {
        return -1000 - depth;
    }
    if (checkDraw(game) || depth == 0) {
        return evaluateBoard(game);
        //return monteCarloEvaluate(game, 50);
    }
    
    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        for (int col = 0; col < COLS; col++) {
            if (isValidMove(game, col)) {
                
                GameState tempGame = *game;
                tempGame.currentPlayer = AI;
                makeMove(&tempGame, col);
                
                int eval = minimax(&tempGame, depth - 1, alpha, beta, false);
                maxEval = (eval > maxEval) ? eval : maxEval;
                alpha = (alpha > eval) ? alpha : eval;
                
                if (beta <= alpha) {
                    break;  
                }
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int col = 0; col < COLS; col++) {
            if (isValidMove(game, col)) {
                
                GameState tempGame = *game;
                tempGame.currentPlayer = PLAYER;
                makeMove(&tempGame, col);
                
                int eval = minimax(&tempGame, depth - 1, alpha, beta, true);
                minEval = (eval < minEval) ? eval : minEval;
                beta = (beta < eval) ? beta : eval;
                
                if (beta <= alpha) {
                    break;  
                }
            }
        }
        return minEval;
    }
}

int findBestMove(GameState *game) {
    int bestScore = INT_MIN;
    int bestCol = 3;  
    
    
    for (int col = 0; col < COLS; col++) {
        if (isValidMove(game, col)) {
            
            GameState tempGame = *game;
            tempGame.currentPlayer = AI;
            makeMove(&tempGame, col);
            
           
            int moveScore = minimax(&tempGame, MAX_DEPTH, INT_MIN, INT_MAX, false);
            
            
            if (moveScore > bestScore) {
                bestScore = moveScore;
                bestCol = col;
            }
        }
    }
    
    return bestCol;
}
