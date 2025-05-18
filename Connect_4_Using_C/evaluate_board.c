#include "ai.h"
#include <limits.h>

int weightMatrix[ROWS][COLS] = {
    {3, 4, 5, 7, 5, 4, 3},
    {4, 6, 8,10, 8, 6, 4},
    {5, 8,11,13,11, 8, 5},
    {5, 8,11,13,11, 8, 5},
    {4, 6, 8,10, 8, 6, 4},
    {3, 4, 5, 7, 5, 4, 3}
};

// Count how many pieces the player has in a given window
int evaluateWindow(int *window, int length, int player) {
    int aiCount = 0, playerCount = 0, empty = 0, score = 0;

    for (int i = 0; i < length; i++) {
        if (window[i] == AI) aiCount++;
        else if (window[i] == PLAYER) playerCount++;
        else empty++;
    }

    if (player == AI) {
        if (aiCount == 4) score += 1000;
        else if (aiCount == 3 && empty == 1) score += 50;
        else if (aiCount == 2 && empty == 2) score += 10;
    } else {
        if (playerCount == 4) score -= 1000;
        else if (playerCount == 3 && empty == 1) score -= 80;
        else if (playerCount == 2 && empty == 2) score -= 15;
    }

    return score;
}

int evaluateBoard(GameState *game) {
    int score = 0;
    int window[4];

    // Center column control
    int centerCol = COLS / 2;
    for (int row = 0; row < ROWS; row++) {
        if (game->board[row][centerCol] == AI) score += 6;
        else if (game->board[row][centerCol] == PLAYER) score -= 6;
    }

    // Positional weight matrix
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (game->board[row][col] == AI) score += weightMatrix[row][col];
            else if (game->board[row][col] == PLAYER) score -= weightMatrix[row][col];
        }
    }

    // Check all windows
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col <= COLS - 4; col++) {
            for (int i = 0; i < 4; i++) window[i] = game->board[row][col + i];
            score += evaluateWindow(window, 4, AI);
            score += evaluateWindow(window, 4, PLAYER);
        }
    }

    for (int row = 0; row <= ROWS - 4; row++) {
        for (int col = 0; col < COLS; col++) {
            for (int i = 0; i < 4; i++) window[i] = game->board[row + i][col];
            score += evaluateWindow(window, 4, AI);
            score += evaluateWindow(window, 4, PLAYER);
        }
    }

    for (int row = 0; row <= ROWS - 4; row++) {
        for (int col = 0; col <= COLS - 4; col++) {
            for (int i = 0; i < 4; i++) window[i] = game->board[row + i][col + i];
            score += evaluateWindow(window, 4, AI);
            score += evaluateWindow(window, 4, PLAYER);
        }
    }

    for (int row = 3; row < ROWS; row++) {
        for (int col = 0; col <= COLS - 4; col++) {
            for (int i = 0; i < 4; i++) window[i] = game->board[row - i][col + i];
            score += evaluateWindow(window, 4, AI);
            score += evaluateWindow(window, 4, PLAYER);
        }
    }

    // Legal move count (mobility)
    int mobility = 0;
    for (int col = 0; col < COLS; col++) {
        if (isValidMove(game, col)) mobility++;
    }
    score += mobility * 2;

    // Trap detection (basic): if opponent has 3 with one empty
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col <= COLS - 4; col++) {
            int oppCount = 0, empty = 0;
            for (int i = 0; i < 4; i++) {
                if (game->board[row][col + i] == PLAYER) oppCount++;
                else if (game->board[row][col + i] == EMPTY) empty++;
            }
            if (oppCount == 3 && empty == 1) score -= 40;
        }
    }

    return score;
}


// #include "ai.h"
// #include <limits.h>

// int evaluateBoard(GameState *game) {
//     if (checkWin(game, AI)) {
//         return 1000;
//     }
//     if (checkWin(game, PLAYER)) {
//         return -1000;
//     }

//     int score = 0;

//     // Horizontal scoring
//     for (int row = 0; row < ROWS; row++) {
//         for (int col = 0; col <= COLS - 4; col++) {
//             int aiCount = 0, playerCount = 0;
//             for (int i = 0; i < 4; i++) {
//                 if (game->board[row][col+i] == AI) aiCount++;
//                 else if (game->board[row][col+i] == PLAYER) playerCount++;
//             }
//             if (playerCount == 0) {
//                 if (aiCount == 3) score += 50;
//                 else if (aiCount == 2) score += 10;
//                 else if (aiCount == 1) score += 1;
//             } else if (aiCount == 0) {
//                 if (playerCount == 3) score -= 50;
//                 else if (playerCount == 2) score -= 10;
//                 else if (playerCount == 1) score -= 1;
//             }
//         }
//     }

//     // Vertical scoring
//     for (int row = 0; row <= ROWS - 4; row++) {
//         for (int col = 0; col < COLS; col++) {
//             int aiCount = 0, playerCount = 0;
//             for (int i = 0; i < 4; i++) {
//                 if (game->board[row+i][col] == AI) aiCount++;
//                 else if (game->board[row+i][col] == PLAYER) playerCount++;
//             }
//             if (playerCount == 0) {
//                 if (aiCount == 3) score += 50;
//                 else if (aiCount == 2) score += 10;
//                 else if (aiCount == 1) score += 1;
//             } else if (aiCount == 0) {
//                 if (playerCount == 3) score -= 50;
//                 else if (playerCount == 2) score -= 10;
//                 else if (playerCount == 1) score -= 1;
//             }
//         }
//     }

//     // Positive diagonal scoring
//     for (int row = 0; row <= ROWS - 4; row++) {
//         for (int col = 0; col <= COLS - 4; col++) {
//             int aiCount = 0, playerCount = 0;
//             for (int i = 0; i < 4; i++) {
//                 if (game->board[row+i][col+i] == AI) aiCount++;
//                 else if (game->board[row+i][col+i] == PLAYER) playerCount++;
//             }
//             if (playerCount == 0) {
//                 if (aiCount == 3) score += 50;
//                 else if (aiCount == 2) score += 10;
//                 else if (aiCount == 1) score += 1;
//             } else if (aiCount == 0) {
//                 if (playerCount == 3) score -= 50;
//                 else if (playerCount == 2) score -= 10;
//                 else if (playerCount == 1) score -= 1;
//             }
//         }
//     }

//     // Negative diagonal scoring
//     for (int row = 3; row < ROWS; row++) {
//         for (int col = 0; col <= COLS - 4; col++) {
//             int aiCount = 0, playerCount = 0;
//             for (int i = 0; i < 4; i++) {
//                 if (game->board[row-i][col+i] == AI) aiCount++;
//                 else if (game->board[row-i][col+i] == PLAYER) playerCount++;
//             }
//             if (playerCount == 0) {
//                 if (aiCount == 3) score += 50;
//                 else if (aiCount == 2) score += 10;
//                 else if (aiCount == 1) score += 1;
//             } else if (aiCount == 0) {
//                 if (playerCount == 3) score -= 50;
//                 else if (playerCount == 2) score -= 10;
//                 else if (playerCount == 1) score -= 1;
//             }
//         }
//     }

//     // Center column preference
//     for (int row = 0; row < ROWS; row++) {
//         if (game->board[row][COLS/2] == AI) score += 3;
//         else if (game->board[row][COLS/2] == PLAYER) score -= 3;
//     }

//     return score;
// }
