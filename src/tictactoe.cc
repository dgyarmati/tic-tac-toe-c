#include <stdio.h>

const int NOUGHTS = 1;
const int CROSSES = 2;
const int BORDER = 3;
const int EMPTY = 0;

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
    int i = 0;

    printf("\nBoard:\n");

    for (i = 0; i < 25; i++) {
        if (i != 0 && i % 5 == 0) {
            printf("\n");
        }
        printf("%4d", board[i]);
    }

    printf("\n");
}

int main() {
    int board[25];
    initializeBoard(&board[0]);
    drawBoard(&board[0]);
}
