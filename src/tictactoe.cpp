#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>

// human side uses noughts, comp side uses crosses
enum { NOUGHTS, CROSSES, BORDER, EMPTY };
enum { HUMANWIN, COMPWIN, DRAW };

const int gameAreaIndices[9] = {
    6, 7, 8, 
    11, 12, 13, 
    16, 17, 18
};

void initializeBoard(int *board) {
    int i = 0;
    for (i = 0; i < 25; i++) {
        board[i] = BORDER;
    }
    for (i = 0; i < 9; i++) {
        board[gameAreaIndices[i]] = EMPTY;
    }
}

void drawBoard(const int *board) {
    char boardSymbols[] = "OX|-"; // noughts, crosses, board limit, empty

    printf("\n\nBoard:\n\n");

    for (int i = 0; i < 9; i++) {
        if (i != 0 && i % 3 == 0) {
            printf("\n\n");
        }
        printf("%4c", boardSymbols[board[gameAreaIndices[i]]]);
    }
    printf("\n");
}

void run() {
    int gameOver = 0;
    int currentPlayer = NOUGHTS;
    int lastMoveMade = 0;
    int board[25];

    initializeBoard(&board[0]);
    drawBoard(&board[0]);

    while (!gameOver) {
        if (currentPlayer == NOUGHTS) {
            // get move from human, make move on board, change side
        } else {
            drawBoard(&board[0]);
        }

        // if three in a row exists, it's game over

        // if there are no more moves, there's a draw

        gameOver = 1; // TODO: remove
    }
}

void makeMove(int *board, const int square, const int currentPlayer) {
    board[square] = currentPlayer;
}

int hasEmptySquare(const int *board) {
    for (int i = 0; i < 9; i++) {
        if (board[gameAreaIndices[i]] == EMPTY) return 1;
    }
    return 0;
}

int main() {
    srand(time(NULL));
    run();
}
