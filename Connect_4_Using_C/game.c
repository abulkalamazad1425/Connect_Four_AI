#include "game.h"

void initializeGame(GameState *game) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            game->board[i][j] = EMPTY;

    game->currentPlayer = PLAYER;
    game->gameOver = false;
    game->winner = EMPTY;
}

bool isValidMove(GameState *game, int col) {
    return col >= 0 && col < COLS && game->board[0][col] == EMPTY;
}

bool makeMove(GameState *game, int col) {
    if (!isValidMove(game, col)) return false;

    int row;
    for (row = ROWS - 1; row >= 0; row--)
        if (game->board[row][col] == EMPTY) break;

    game->board[row][col] = game->currentPlayer;

    if (checkWin(game, game->currentPlayer)) {
        game->gameOver = true;
        game->winner = game->currentPlayer;
    } else if (checkDraw(game)) {
        game->gameOver = true;
        game->winner = EMPTY;
    }

    game->currentPlayer = (game->currentPlayer == PLAYER) ? AI : PLAYER;
    return true;
}

bool checkDraw(GameState *game) {
    for (int col = 0; col < COLS; col++)
        if (game->board[0][col] == EMPTY) return false;
    return true;
}

bool checkWin(GameState *game, int player) {
    for (int row = 0; row < ROWS; row++)
        for (int col = 0; col <= COLS - 4; col++)
            if (game->board[row][col] == player &&
                game->board[row][col+1] == player &&
                game->board[row][col+2] == player &&
                game->board[row][col+3] == player) return true;

    for (int row = 0; row <= ROWS - 4; row++)
        for (int col = 0; col < COLS; col++)
            if (game->board[row][col] == player &&
                game->board[row+1][col] == player &&
                game->board[row+2][col] == player &&
                game->board[row+3][col] == player) return true;

    for (int row = 0; row <= ROWS - 4; row++)
        for (int col = 0; col <= COLS - 4; col++)
            if (game->board[row][col] == player &&
                game->board[row+1][col+1] == player &&
                game->board[row+2][col+2] == player &&
                game->board[row+3][col+3] == player) return true;

    for (int row = 3; row < ROWS; row++)
        for (int col = 0; col <= COLS - 4; col++)
            if (game->board[row][col] == player &&
                game->board[row-1][col+1] == player &&
                game->board[row-2][col+2] == player &&
                game->board[row-3][col+3] == player) return true;

    return false;
}
