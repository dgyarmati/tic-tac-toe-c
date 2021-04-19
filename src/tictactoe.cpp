#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>

// TODO: direction the player can choose should be called squareNumber or similar
// TODO: bugfix - draw is displayed even if there's a win
// TODO: lastMove should be called gameAreIdxToMove or similar

// human side uses noughts, comp side uses crosses
enum { NOUGHTS, CROSSES, BORDER, EMPTY };
enum { HUMANWIN, COMPWIN, DRAW };

// directions to search for three in a rows
const int directions[4] = {1, 5, 4, 6};

const int gameAreaIndices[9] = {
    6, 7, 8, 
    11, 12, 13, 
    16, 17, 18
};

int getNoOfSameSymbolsInADirection(int startSquareIdx, const int direction, const int *board, const int currentSymbol) {
    int noOfSameSymbolsInARow = 0;

    while (board[startSquareIdx] != BORDER) {
        if (board[startSquareIdx] != currentSymbol) {
            break;
        }
        noOfSameSymbolsInARow++;
        startSquareIdx += direction;
    }

    return noOfSameSymbolsInARow;
}

int findThreeInARow(const int *board, const int currentSymbolIdx, const int currentSymbol) {
    int direction = 0;
    int threeCount = 0;

    for (int i = 0; i < 4; i++) {
        direction = directions[i];
        threeCount += getNoOfSameSymbolsInADirection(currentSymbolIdx + direction, direction, board, currentSymbol);
        threeCount += getNoOfSameSymbolsInADirection(currentSymbolIdx + direction * -1, direction * -1, board, currentSymbol);

        if (threeCount == 3) {
            break;
        }

        threeCount = 1;
    }

    return threeCount;
}

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

int attemptWinningMove(int *board, const int currentPlayer) {
    // checks if next move can win the game

    int direction = 1;
    int isWinningMoveFound = 0;

    for (int i = 0; i < 9; i++) {
        if (board[gameAreaIndices[i]] == EMPTY) {
            direction = gameAreaIndices[i];
            board[direction] = currentPlayer;

            if (findThreeInARow(board, direction, currentPlayer) == 3) {
                isWinningMoveFound = 1;
            }

            board[direction] = EMPTY;
            if (isWinningMoveFound == 1) {
                break;
            }
            direction = -1;
        }
    }
    return direction;
}

int getAIPlayerMove(int *board, const int currentPlayer) {
    int freeSquareIdx = 0;
    int availableDirections[9];
    int randDirection = 0;

    randDirection = attemptWinningMove(board, currentPlayer);
    if (randDirection != -1) {
        return randDirection;
    }

    randDirection = 0;
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
    int currentPlayerSymbol = NOUGHTS;
    int lastMove = 0;
    int board[25];

    initializeBoard(&board[0]);
    drawBoard(&board[0]);

    while (!gameOver) {
        if (currentPlayerSymbol == NOUGHTS) {
            lastMove = getHumanPlayerMove(&board[0]);
            makeMove(&board[0], lastMove, currentPlayerSymbol);
            currentPlayerSymbol = CROSSES;
        } else {
            lastMove = getAIPlayerMove(&board[0], currentPlayerSymbol);
            makeMove(&board[0], lastMove, currentPlayerSymbol);
            currentPlayerSymbol = NOUGHTS;
            drawBoard(&board[0]);
        }

        int oppositePlayerSymbol = currentPlayerSymbol ^ 1;
        if (findThreeInARow(board, lastMove, oppositePlayerSymbol) == 3) {
            printf("Game over!\n");
            gameOver = 1;
            if (currentPlayerSymbol == NOUGHTS) {
                printf("Computer wins!\n");
            } else {
                printf("Player wins!\n");
            }
        }

        if (!hasEmptySquare(board)) {
            printf("Game over!\n");
            gameOver = 1;
            printf("It's a draw.\n");
        }

    }

    drawBoard(&board[0]);
}

int main() {
    srand(time(NULL));
    run();
}
 