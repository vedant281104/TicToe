# TicToe

#include <stdio.h>
#include <stdlib.h>

char board[3][3] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
char currentPlayer = 'X';
int moves = 0;
int maxMoves = 9; // Maximum moves before declaring a draw

// Structure to store player moves
struct Move {
    char player;
    int row;
    int col;
    struct Move* next;
};

struct Move* head = NULL; // Head of the linked list

void displayBoard() {
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
}

int makeMove(int row, int col) {
    if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ')
        return 0;
    board[row - 1][col - 1] = currentPlayer;
    moves++;

    struct Move* newMove = (struct Move*)malloc(sizeof(struct Move));
    newMove->player = currentPlayer;
    newMove->row = row;
    newMove->col = col;
    newMove->next = NULL;

    if (head == NULL) {
        head = newMove;
    } else {
        struct Move* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newMove;
    }

    return 1;
}

int checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer)
            return 1;  // Row win
        if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)
            return 1;  // Column win
    }
    if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer)
        return 1;  // Diagonal win
    if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)
        return 1;  // Diagonal win
    return 0;  // No win
}

int checkDraw() {
    return (moves == maxMoves);
}

int isMoveValid(int row, int col) {
    return (row >= 1 && row <= 3 && col >= 1 && col <= 3 && board[row - 1][col - 1] == ' ');
}

int switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void resetGame() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
    currentPlayer = 'X';
    moves = 0;

    // Free the linked list
    while (head != NULL) {
        struct Move* temp = head;
        head = head->next;
        free(temp);
    }
}

void displayMoves() {
    printf("Game Analysis:\n");
    struct Move* current = head;
    while (current) {
        printf("Player %c: Row %d, Column %d\n", current->player, current->row, current->col);
        current = current->next;
    }
}

int main() {
    printf("Welcome to Tic-Tac-Toe!\n");

    int row, col;
    int validMove;
    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y') {
        resetGame();

        while (1) {
            displayBoard();
            printf("Player %c, enter your move (row and column): ", currentPlayer);
            scanf("%d %d", &row, &col);

            validMove = isMoveValid(row, col);

            if (validMove) {
                makeMove(row, col);
                if (checkWin()) {
                    displayBoard();
                    printf("Player %c wins!\n", currentPlayer);
                    break;
                } else if (checkDraw()) {
                    displayBoard();
                    printf("It's a draw!\n");
                    break;
                }
                switchPlayer();
            } else {
                printf("Invalid move. Try again.\n");
            }
        }

        displayMoves();

        printf("Play again? (y/n): ");
        scanf(" %c", &playAgain); // Leading space to consume the newline character

        if (playAgain == 'y' || playAgain == 'Y') {
            printf("Starting a new game...\n");
        } else {
            printf("Thanks for playing! Exiting the game.\n");
            exit(0);
        }
    }

    return 0;
}
