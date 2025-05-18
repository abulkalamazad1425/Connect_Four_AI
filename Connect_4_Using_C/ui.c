#include <stdio.h>
#include <stdlib.h>
#include "ui.h"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printGameHeader() {
    printf("\n=== CONNECT 4 GAME ===\n");
    printf("Player: X | AI: O\n\n");
}

void printBoard(GameState *game) {
    printf("  0 1 2 3 4 5 6\n");
    printf(" ---------------\n");
    for (int row = 0; row < ROWS; row++) {
        printf("|");
        for (int col = 0; col < COLS; col++) {
            char symbol = game->board[row][col] == PLAYER ? 'X' :
                          game->board[row][col] == AI ? 'O' : '.';
            printf(" %c", symbol);
        }
        printf(" |\n");
    }
    printf(" ---------------\n");
}

void printGameResult(GameState *game) {
    if (game->winner == PLAYER)
        printf("Congratulations! You won!\n");
    else if (game->winner == AI)
        printf("Game Over! The AI won!\n");
    else
        printf("Game Over! It's a draw!\n");
}
