#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define ROWS 6
#define COLS 7
#define EMPTY 0
#define PLAYER 1
#define AI 2

typedef struct {
    int board[ROWS][COLS];
    int currentPlayer;
    bool gameOver;
    int winner;
} GameState;

void initializeGame(GameState *game);
bool isValidMove(GameState *game, int col);
bool makeMove(GameState *game, int col);
bool checkWin(GameState *game, int player);
bool checkDraw(GameState *game);

#endif
