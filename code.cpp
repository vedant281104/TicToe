#include <stdio.h>
#include <stdlib.h>

// Global variables for the game
char board[3][3] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
char currentPlayer = 'X'; // Starting player
int moves = 0; // Counter for moves made
int maxMoves = 9; // Maximum moves before declaring a draw

// Structure to store player moves
struct Move {
    char player;
    int row;
    int col;
    struct Move* next; // Pointer to the next move
};

struct Move* head = NULL; // Head of the linked list to track moves

// Function to display the game board
void displayBoard() {
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
}

// Function to make a move
int makeMove(int row, int col) {
    // Check if the move is valid
    if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
        return 0; // Invalid move
    }

    // Update the board and move count
    board[row - 1][col - 1] = currentPlayer;
    moves++;

    // Create a new move node
    struct Move* newMove = (struct Move*)malloc(sizeof(struct Move));
    newMove->player = currentPlayer;
    newMove->row = row;
    newMove->col = col;
    newMove->next = NULL;

    // Add the new move to the linked list
    if (head == NULL) {
        head = newMove; // First move
    } else {
        struct Move* current = head;
        while (current->next) {
            current = current->next; // Traverse to the end of the list
        }
        current->next = newMove; // Append the new move
    }

    return 1; // Successful move
}

// Function to check for a win
int checkWin() {
    // Check rows and columns for a win
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
            (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)) {
            return 1; // Win found
        }
    }

    // Check diagonals for a win
    if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
        (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)) {
        return 1; // Win found
    }

    return 0; // No win
}

// Function to check for a draw
int checkDraw() {
    return (moves == maxMoves); // Return true if maximum moves reached
}

// Function to validate the move
int isMoveValid(int row, int col) {
    return (row >= 1 && row <= 3 && col >= 1 && col <= 3 && board[row - 1][col - 1] == ' ');
}

// Function to switch players
int switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; // Switch between X and O
}

// Function to reset the game
void resetGame() {
    // Clear the board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
    currentPlayer = 'X'; // Reset to player X
    moves = 0; // Reset move counter

    // Free the linked list of moves
    while (head != NULL) {
        struct Move* temp = head;
        head = head->next;
        free(temp); // Free each move node
    }
}

// Function to display the moves made during the game
void displayMoves() {
    printf("Game Analysis:\n");
    struct Move* current = head;
    while (current) {
        printf("Player %c: Row %d, Column %d\n", current->player, current->row, current->col);
        current = current->next; // Move to the next node
    }
}

// Main function to run the game
int main() {
    printf("Welcome to Tic-Tac-Toe!\n");

    int row, col;
    int validMove;
    char playAgain = 'y'; // Variable to control replaying the game

    // Main game loop
    while (playAgain == 'y' || playAgain == 'Y') {
        resetGame(); // Reset the game for a new round

        while (1) {
            displayBoard(); // Display the current board
            printf("Player %c, enter your move (row and column): ", currentPlayer);
            scanf("%d %d", &row, &col); // Get player's move

            validMove = isMoveValid(row, col); // Check if the move is valid

            if (validMove) {
                makeMove(row, col); // Make the move
                if (checkWin()) {
                    displayBoard();
                    printf("Player %c wins!\n", currentPlayer);
                    break; // End the game loop on win
                } else if (checkDraw()) {
                    displayBoard();
                    printf("It's a draw!\n");
                    break; // End the game loop on draw
                }
                switchPlayer(); // Switch to the next player
            } else {
                printf("Invalid move. Try again.\n");
            }
        }

        displayMoves(); // Display moves made during the game

        // Ask if players want to play again
        printf("Play again? (y/n): ");
        scanf(" %c", &playAgain); // Leading space to consume the newline character

        if (playAgain == 'y' || playAgain == 'Y') {
            printf("Starting a new game...\n");
        } else {
            printf("Thanks for playing! Exiting the game.\n");
            exit(0); // Exit the program
        }
    }

    return 0; // Program ended successfully
}
