#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "game.h"
#include "ai.h"
#include "ui.h"

int main() {
    GameState game;
    char input[10];
    int column;

    srand(time(NULL));
    
    while (1) {
        initializeGame(&game);
        
        while (!game.gameOver) {
            clearScreen();
            printGameHeader();
            printBoard(&game);
            
            if (game.currentPlayer == PLAYER) {
                printf("\nYour turn (0-6): ");
                if (fgets(input, sizeof(input), stdin) == NULL) continue;
                if (input[0] == 'q' || input[0] == 'Q') {
                    printf("\nThanks for playing!\n");
                    return 0;
                }
                column = atoi(input);
                if (!isValidMove(&game, column)) {
                    printf("\nInvalid move! Try again.\n");
                    sleep(1);
                    continue;
                }
                makeMove(&game, column);
            } else {
                printf("\nAI is thinking...\n");
                sleep(1);
                column = findBestMove(&game);
                makeMove(&game, column);
            }
        }

        clearScreen();
        printGameHeader();
        printBoard(&game);
        printGameResult(&game);
        
        printf("Play again? (y/n): ");
        if (fgets(input, sizeof(input), stdin) == NULL || (input[0] != 'y' && input[0] != 'Y')) break;
    }
    
    printf("\nThanks for playing!\n");
    return 0;
}
