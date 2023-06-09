#include <stdio.h>

#define MAX_WIDTH 40
#define MAX_HEIGHT 20

char board[MAX_HEIGHT][MAX_WIDTH];
int width, height;

void initBoard() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }
}

int isCollumnFull(int column){
  int currRow = 0;
  
  if(board[currRow][column] != ' '){
    return 1;
        }
  
  for(int i = 0; i < height-1; i++){
    currRow ++;
  } 

  }


void updateBoard(int column, char symbol) {
    int row = height - 1;
    while (row >= 0 && board[row][column] != ' ') {
        row--;
    }
    if (row >= 0) {
        board[row][column] = symbol;
    }
}

int checkWin(char symbol) {
  //proverka na redove
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width - 3; j++) {
            if (board[i][j] == symbol && board[i][j + 1] == symbol &&
                board[i][j + 2] == symbol && board[i][j + 3] == symbol) {
                return 1;
            }
        }
    }

    // proverka na koloni
    for (int i = 0; i < height - 3; i++) {
        for (int j = 0; j < width; j++) {
            if (board[i][j] == symbol && board[i + 1][j] == symbol &&
                board[i + 2][j] == symbol && board[i + 3][j] == symbol) {
                return 1;
            }
        }
    }

    // proverka na diagonali (gore lqvo kum dolu dqsno)
    for (int i = 0; i < height - 3; i++) {
        for (int j = 0; j < width - 3; j++) {
            if (board[i][j] == symbol && board[i + 1][j + 1] == symbol &&
                board[i + 2][j + 2] == symbol && board[i + 3][j + 3] == symbol) {
                return 1;
            }
        }
    }

    // proverka na diagonali (gore dqsno kum dolu lqvo)
    for (int i = 0; i < height - 3; i++) {
        for (int j = 3; j < width; j++) {
            if (board[i][j] == symbol && board[i + 1][j - 1] == symbol &&
                board[i + 2][j - 2] == symbol && board[i + 3][j - 3] == symbol) {
                return 1;
            }
        }
    }

    return 0;
}



int main() {
    printf("Enter the width and height of your board: ");
    scanf("%d %d", &width, &height);

    if (width < 4 || height < 4 || width > MAX_WIDTH || height > MAX_HEIGHT) {
        printf("Invalid board dimensions");
        return 0;
    }

    initBoard();
    printBoard();

    char player1 = 'X';
    char player2 = 'O';
    char currentPlayer = player1;
    int moves = 0;

    while (1) {
    int column;
    printf("Player %c, enter the column to drop your token (0-%d): ", currentPlayer, width - 1);
    scanf("%d", &column);
    if (column < 0 || column >= width) {
        puts("Invalid column number. Please try again.\n");
    } else {
        updateBoard(column, currentPlayer);
        printBoard();
        moves++;

        if (checkWin(currentPlayer)) {
            printf("Player %c wins!\n", currentPlayer);
            break;
        } else if (moves == width * height) {
            printf("It's a tie!\n");
            break;
        }

if (currentPlayer == player1) {
    currentPlayer = player2;
} else {
    currentPlayer = player1;
}
    }
}

    return 0;
}
