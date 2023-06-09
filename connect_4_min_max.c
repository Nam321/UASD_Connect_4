#include <math.h>
#include <stdio.h>
#define MAX_WIDTH 40
#define MAX_HEIGHT 20

char board[MAX_HEIGHT][MAX_WIDTH];
int width, height;
int arr_height[MAX_HEIGHT];

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

void updateBoard(int column, char symbol, int *arr_height) {
  int row = height - 1;
  while (row >= 0 && board[row][column] != ' ') {
    row--;
  }
  if (row >= 0) {
    board[row][column] = symbol;
    arr_height[column]++;
  }
}

int checkWin(char symbol) {
  // proverka na redove
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

int evaluateBoard(int height, int width) {
  int score = 0;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j <= height - 4; j++) {
      int countX = 0;
      int countO = 0;
      for (int k = 0; k < 4; k++) {
        if (board[i][j + k] == 'X')
          score += 1;
        else if (board[i][j + k] == 'O')
          score -= 1;
      }
      if (countX > 0 && countO == 'X')
        score += pow(10, countX);
      else if (countO > 0 && countX == 'O')
        score -= pow(10, countO);
    }
  }

  for (int i = 0; i <= height - 4; i++) {
    for (int j = 0; j < width; j++) {
      int countX = 0;
      int countO = 0;
      for (int k = 0; k < 4; k++) {
        if (board[i + k][j] == 'X')
          countX++;
        else if (board[i + k][j] == 'O')
          countO++;
      }
      if (countX > 0 && countO == 0)
        score += pow(10, countX);
      else if (countO > 0 && countX == 0)
        score -= pow(10, countO);
    }
  }

  for (int i = 0; i <= height - 4; i++) {
    for (int j = 0; j <= width - 4; j++) {
      int countX = 0;
      int countO = 0;
      for (int k = 0; k < 4; k++) {
        if (board[i + k][j + k] == 'X')
          countX++;
        else if (board[i + k][j + k] == 'O')
          countO++;
      }
      if (countX > 0 && countO == 0)
        score += pow(10, countX);
      else if (countO > 0 && countX)
        score -= pow(10, countO);
    }
  }

  for (int i = 0; i <= height - 4; i++) {
    for (int j = 3; j < width; j++) {
      int countX = 0;
      int countO = 0;
      for (int k = 0; k < 4; k++) {
        if (board[i + k][j - k] == 'X')
          countX++;
        else if (board[i + k][j - k] == 'O')
          countO++;
      }
      if (countX > 0 && countO == 0)
        score += pow(10, countX);
      else if (countO > 0 && countX == 0)
        score -= pow(10, countO);
    }
  }

  return score;
}
int minimax(int height, int width, int depth, char player) {
  int board_copy[height][width];
  char player_X = 'X';
  char player_O = 'O';

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      board_copy[i][j] = board[i][j];
    }
  }
  if (depth == 0) {
    return evaluateBoard(height, width);
  }

  int best_score;
  if (player == player_X) {
    best_score = -1000;

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (board_copy[i][j] == ' ') {
          board_copy[i][j] = 'X';
          int score = minimax(height, width, depth -1, player_O);
          board_copy[i][j] = ' ';
          if (score > best_score) {
            best_score = score;
          }
        }
      }
    }

  } else {
    int min_score = -1000;

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (board_copy[i][j] == ' ') {
          board_copy[i][j] = 'X';
          int score = minimax(height, width, depth -1, player_X);
          board_copy[i][j] = ' ';
          if (score < min_score) {
            min_score = score;
          }
        }
      }
    }
    return min_score;
  }
  return best_score;
};





int bot(int height, int width) {
  int board_copy[height][width];
  int best_score = -10000;
  int best_pos_y, best_pos_x;
  int score = 321443;
  int max_depth = height * width;
  char bot = 'X';

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      board_copy[i][j] = board[i][j];
    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (board_copy[i][j] == ' ') {
        board_copy[i][j] = 'X';
        score = minimax(height, width, max_depth-1, bot);
        board_copy[i][j] = ' ';
        if (score > best_score) {
          best_score = score;
          best_pos_y = i;
          best_pos_x = j;
        }
      }
    }
  }
  board[best_pos_y][best_pos_x] = bot;

  return 0;
};

int main() {
  printf("Enter the width and height of your board: ");
  scanf("%d %d", &height, &width);

  if (width < 4 || height < 4 || width > MAX_WIDTH || height > MAX_HEIGHT) {
    printf("Invalid board dimensions");
    return 0;
  }

  initBoard();
  printBoard();

  char ai = 'X';
  char player2 = 'O';
  char currentPlayer = ai;
  int moves = 0;
  int column;
  for (int i = 0; i < MAX_HEIGHT; i++) {

    arr_height[i] = -1;
  }

  while (1) {

    bot(height, width);

    printf("Player %c, enter the column to drop your token (0-%d): ",
           currentPlayer, width - 1);
    scanf("%d", &column);
    if (currentPlayer == player2) {
      if (column < 0 || column >= width) {
        puts("Invalid column number. Please try again.\n");
      } else if (arr_height[column] + 1 == height) {
        puts("Invalid coulmn is full. Please try again.\n");
      }

      else {
        // printf("\n%d\n", arr_height[column]);
        updateBoard(column, currentPlayer, &arr_height[column]);
        printBoard();
        moves++;

        if (checkWin(currentPlayer)) {
          printf("Player %c wins!\n", currentPlayer);
          break;
        } else if (moves == width * height) {
          printf("It's a tie!\n");
          break;
        }

        if (currentPlayer == ai) {
          currentPlayer = player2;
        } else {
          currentPlayer = ai;
        }
      }
    }

    return 0;
  }
}