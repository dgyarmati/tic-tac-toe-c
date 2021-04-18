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

int getHumanPlayerMove(const int *board) {
    char userInput[4];

    int moveConfirmed = 0;
    int direction = -1;

    while (moveConfirmed == 0) {
        printf("Please enter a direction from 1 to 9: ");
        fgets(userInput, 3, stdin);
        fflush(stdin);

        if (strlen(userInput) != 2) {
            printf("Invalid input! I need a direction followed by an Enter.\n");
            continue;
        }

        if (sscanf(userInput, "%d", &direction) != 1) {
            direction = -1;
            printf("Invalid input!\n");
            continue;
        }

        if (direction < 1 || direction > 9) {
            direction = -1;
            printf("Invalid direction!\n");
            continue;
        }

        direction--; // zero indexing (the input is from 1 - 9, so we need to convert it to a valid index)

        if (board[gameAreaIndices[direction]] != EMPTY) {
            direction = -1;
            printf("Square is already taken!\n");
            continue;
        }

        moveConfirmed = 1;
    }

    printf("Moved in direction: %d\n", (direction + 1));
    return gameAreaIndices[direction];
}

int getAIPlayerMove(const int *board) {
    int freeSquareIdx = 0;
    int availableDirections[9];
    int randDirection = 0;

    for (int i = 0; i < 9; i++) {
        if (board[gameAreaIndices[i]] == EMPTY) {
            availableDirections[freeSquareIdx++] = gameAreaIndices[i];
        }
    }

    randDirection = (rand() % freeSquareIdx);
    return availableDirections[randDirection];    
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

void run() {
    int gameOver = 0;
    int currentPlayer = NOUGHTS;
    int lastMoveMade = 0;
    int board[25];

    initializeBoard(&board[0]);
    drawBoard(&board[0]);

    while (!gameOver) {
        if (currentPlayer == NOUGHTS) {
            int lastMove = getHumanPlayerMove(&board[0]);
            makeMove(&board[0], lastMove, currentPlayer);
            currentPlayer = CROSSES;
        } else {
            int lastMove = getAIPlayerMove(&board[0]);
            makeMove(&board[0], lastMove, currentPlayer);
            currentPlayer = NOUGHTS;
        }
        drawBoard(&board[0]);

        // if three in a row exists, it's game over

        // if there are no more moves, there's a draw
        if (!hasEmptySquare(board)) {
            printf("Game over!\n");
            gameOver = 1;
            printf("It's a draw.\n");
        }

    }
}

int main() {
    srand(time(NULL));
    run();
}
 