//
//  hossam-hw5.c
//  
//
//  Created by Hossam Hammady on 4/19/12.
//  Copyright (c) 2012 Texas A&M University at Qatar. All rights reserved.
//

/* system includes */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* macro definitions */
#define  MAX_WIDTH      7
#define  MAX_HEIGHT     7

#define  PIECE_KING     0   // malek
#define  PIECE_QUEEN    1   // wazir
#define  PIECE_ROOK     2   // rukh
#define  PIECE_BISHOP   3   // fil
#define  PIECE_KNIGHT   4   // 7u6an
#define  PIECE_PAWN     5   // 3askari
#define  MAX_PIECE      5

#define  DIR_UP         0
#define  DIR_DOWN       1
#define  MAX_DIR        1

#define  SPECIAL_NEW_MOVE_X   -1
#define  SPECIAL_NEW_MOVE_Y   -1
#define  SPECIAL_STOP_X       -2
#define  SPECIAL_STOP_Y       -2

/* function prototypes */
unsigned getRandom(unsigned max);
void initializeBoard(unsigned piece, unsigned direction, 
                     unsigned x, unsigned y);
void generateKingMoves(int x, int y);
void generateRookMoves(int x, int y);
void generateBishopMoves(int x, int y);
void generateKnightMoves(int x, int y);
void generatePawnMoves(int x, int y, unsigned direction);
void markBoard(int x, int y);
void printPiece(unsigned piece, unsigned direction, 
                unsigned x, unsigned y);
void printBoard(unsigned x, unsigned y);

/* global variables */
int board[MAX_WIDTH+1][MAX_HEIGHT+1];

/* a program to train on chess game movements */
int main(void)
{
  /* declare variables */
  unsigned pieceX, pieceY;
  unsigned piece, dir;
  int moveX, moveY;
  int newPiece, stopGame;
  
  /* randomize seed */
  srand(time(NULL));
  
  do {
    /* generate random piece in random location */
    piece = getRandom(MAX_PIECE);
    if (piece == PIECE_PAWN)
      dir = getRandom(MAX_DIR);
    pieceX = getRandom(MAX_WIDTH);
    pieceY = getRandom(MAX_HEIGHT);

    /* initialize board with piece possible moves */
    initializeBoard(piece, dir, pieceX, pieceY);
    
    /* print piece name and location */
    printPiece(piece, dir, pieceX, pieceY);
    
    /* ask user to enter a valid move */
    do {
      newPiece = 0;
      stopGame = 0;
      printf("What is a valid move [x y]? ");
      scanf("%d %d", &moveX, &moveY);
      
      /* validate user input */
      if (moveX < 0 || moveX > MAX_WIDTH || moveY < 0 || moveY > MAX_HEIGHT)
      {        
        /* user wants a new move? */
        if (moveX == SPECIAL_NEW_MOVE_X && moveY == SPECIAL_NEW_MOVE_Y)
          newPiece = 1;
        else
          newPiece = 0;
        
        /* user wants to stop? */
        if (moveX == SPECIAL_STOP_X && moveY == SPECIAL_STOP_Y)
          stopGame = 1;
        else
          stopGame = 0;

        if (!newPiece && !stopGame)
        {
          printf("Invalid input, please re-enter values in the range [0..%d] and [0..%d]\n",
                MAX_WIDTH, MAX_HEIGHT);
          printf("Enter %d %d to put a new piece or %d %d to exit\n",
                 SPECIAL_NEW_MOVE_X, SPECIAL_NEW_MOVE_Y, 
                 SPECIAL_STOP_X, SPECIAL_STOP_Y);
        }

      }
      else
      {
        /* check if move is valid or invalid according to chess rules */
        if (board[moveX][moveY] == 1)
          printf("Correct move, well done :)\n");
        else
          printf("Wrong move, please try again :(\n");
      }
      
    } while (!newPiece && !stopGame);
    
    printf("These were all valid moves:\n");
    printBoard(pieceX, pieceY);
    
  } while (!stopGame);
  
  printf("Bye Bye!\n");
  return 0;
}

/* generate a random integer from 0 to max */
unsigned getRandom(unsigned max)
{
  /* the mod operator returns values from 0 to operand - 1 */
  unsigned r = rand() % (max + 1);
  return (r);
}

/* calculate all possible moves for a piece and mark board */
void initializeBoard(unsigned piece, unsigned direction, 
                     unsigned x, unsigned y)
{
  /* declare variables */
  unsigned row, col;
  
  /* initialize boards with all invalid marks */
  for (row = 0; row <= MAX_HEIGHT; row++)
    for (col = 0; col <= MAX_WIDTH; col++)
      board[col][row] = 0;
  
  /* calculate all valid moves and mark board accordingly */
  switch (piece)
  {
    case PIECE_BISHOP:
      generateBishopMoves(x, y);
      break;
    case PIECE_KING:
      generateKingMoves(x, y);
      break;
    case PIECE_KNIGHT:
      generateKnightMoves(x, y);
      break;
    case PIECE_PAWN:
      generatePawnMoves(x, y, direction);
      break;
    case PIECE_QUEEN:
      generateRookMoves(x, y);
      generateBishopMoves(x, y);
      break;
    case PIECE_ROOK:
      generateRookMoves(x, y);
      break;
    default:
      printf("Unknown piece, something wrong happened!\n");
      break;
  }
}

void generateKingMoves(int x, int y)
{
  markBoard(x, y + 1);
  markBoard(x, y - 1);
  markBoard(x + 1, y);
  markBoard(x - 1, y);
}

void generateRookMoves(int x, int y)
{
  int row, col;
  
  for (row = y + 1; row <= MAX_HEIGHT; row++)
    markBoard(x, row);
  for (row = y - 1; row >= 0; row--)
    markBoard(x, row);
  for (col = x + 1; col <= MAX_WIDTH; col++)
    markBoard(col, y);
  for (col = x - 1; col >= 0; col--)
    markBoard(col, y);
}

void generateBishopMoves(int x, int y)
{
  int row, col;
  
  row = y; col = x;
  do
  {
    row++; col++;
    markBoard(col, row);
  } while (row <= MAX_HEIGHT && col <= MAX_WIDTH);

  row = y; col = x;
  do
  {
    row--; col--;
    markBoard(col, row);
  } while (row >= 0 && col >= 0);

  row = y; col = x;
  do
  {
    row++; col--;
    markBoard(col, row);
  } while (row <= MAX_HEIGHT && col >= 0);
  
  row = y; col = x;
  do
  {
    row--; col++;
    markBoard(col, row);
  } while (row >= 0 && col <= MAX_WIDTH);

}

void generateKnightMoves(int x, int y)
{
  markBoard(x + 1, y + 2);
  markBoard(x + 1, y - 2);
  markBoard(x - 1, y + 2);
  markBoard(x - 1, y - 2);
  markBoard(x + 2, y + 1);
  markBoard(x + 2, y - 1);
  markBoard(x - 2, y + 1);
  markBoard(x - 2, y - 1);
}

void generatePawnMoves(int x, int y, unsigned direction)
{
  if (direction == DIR_UP)
    markBoard(x, y + 1);
  else
    markBoard(x, y - 1);          
}

void markBoard(int x, int y)
{
  if (x >= 0 && x <= MAX_WIDTH && y >= 0 && y <= MAX_HEIGHT)
    board[x][y] = 1;
}

void printPiece(unsigned piece, unsigned direction, 
                unsigned x, unsigned y)
{
  printf("------------------------\n");
  printf("Placed ");
  switch (piece) {
    case PIECE_BISHOP:
      printf("Bishop");
      break;
    case PIECE_KING:
      printf("King");
      break;
    case PIECE_KNIGHT:
      printf("Knight");
      break;
    case PIECE_PAWN:
      printf("Pawn");
      if (direction == DIR_UP)
        printf(" (Up)");
      else
        printf(" (Down)");
      break;
    case PIECE_QUEEN:
      printf("Queen");
      break;
    case PIECE_ROOK:
      printf("Rook");
      break;
  }
  printf(" in location (%u, %u)\n", x, y);
}

void printBoard(unsigned x, unsigned y)
{
  int row, col;
  for (row = MAX_HEIGHT; row >= 0; row--)
  {
    for (col = 0; col <= MAX_WIDTH; col++)
    {
      if (row == y && col == x)
        printf(" X");
      else
        printf("%2d", board[col][row]);
    }
    printf("\n");
  }
}
